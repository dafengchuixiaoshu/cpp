/*
Author: coderqiuan@163.com
Created on: 2017-01-12 16:04
*/

/*
   查看进程pid
   (1) ps ux | grep prog_name
   (2) pgrep prog_name 
   查看线程tid
   (1) ps -efL | grep prog_name
   (2) ls /proc/pid/task
   */

#include "logger.h"
#include "thread.h"
#include "exception.h"

namespace qiuan
{
    struct ThreadData
    {
        void* _params;
        thread_func _func;
        std::string _name;

        ThreadData(thread_func func, void* params, const std::string& name)
            : _func(func)
              , _name(name)
              , _params(params)
        {

        }

        void run()
        {
            try
            {
                _func(_params);
            }
            catch (const Exception& ex)
            {
                LOG_NOTICE << "thread crashed - exception caught in thread:" << _name << ",reason:" << ex.what() << ",stack:" << ex.stack();
                abort();
            }
            catch (const std::exception& ex)
            {
                LOG_NOTICE << "thread crashed - exception caught in thread:" << _name <<",reason:" << ex.what();
                abort();
            }
            catch (...)
            {
                LOG_NOTICE << "thread crashed - unknown exception caught in thread:" << _name;
                throw; // rethrow
            }
        }
    };

    void* thread_start(void* obj)
    {
        ThreadData* data = static_cast<ThreadData*>(obj);

        data->run();

        delete data;

        return NULL;
    }
}

using namespace qiuan;

CAtomic<uint32_t> CThread::m_threadcount;

    CThread::CThread()
    : m_isok(false)
      , m_isjoined(false)
{
    m_threadnumber = m_threadcount.increment();
}

CThread::~CThread()
{
    if(m_isok && !m_isjoined)
    {
        pthread_detach(m_tid);
    }
}

bool CThread::join()
{
    if(!m_isjoined)
    {
        m_isjoined = 0 == pthread_join(m_tid, NULL);
    }

    return m_isjoined;
}

bool CThread::start(thread_func func, void* params, const std::string& name, int stacksize)
{
    if(!m_isok)
    {
        if(name.empty())
        {
            m_name = to_string("thread_%d", m_threadnumber);
        }
        else
        {
            m_name = name;
        }

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, stacksize);
        //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        ThreadData* data = new ThreadData(func, params, m_name);

        if(NULL != data)
        {
            m_isok = 0 == pthread_create(&m_tid, &attr, thread_start, data);
        }

        pthread_attr_destroy(&attr);
    }

    return m_isok;
}

