/*
Author: coderqiuan@163.com
Created on: 2016-11-11 10:38
*/

#pragma once

#include <pthread.h>

#include "util.h"

namespace qiuan
{
    class CMutex
    {
        private:

            CMutex(const CMutex&);

            const CMutex& operator=(const CMutex&);

        public:

            explicit CMutex()
            {
                if(0 != pthread_mutex_init(&m_mutex, NULL))
                {
                    _assert();
                }
            }

            ~CMutex()
            {
                if( 0 != pthread_mutex_destroy(&m_mutex))
                {
                    _assert();
                }
            }

            void lock()
            {
                if(0 != pthread_mutex_lock(&m_mutex))
                {
                    _assert();
                }
            }

            void unlock()
            {
                if(0 != pthread_mutex_unlock(&m_mutex))
                {
                    _assert();
                }
            }

            pthread_mutex_t& mutex() { return m_mutex; }

        private:

            pthread_mutex_t m_mutex;
    };

    class CMutexGuard
    {
        private:

            CMutexGuard(const CMutexGuard&);

            const CMutexGuard& operator=(const CMutexGuard&);

        public:

            explicit CMutexGuard(CMutex& mutex)
                : m_mutex(mutex)
            {
                m_mutex.lock();   
            }

            ~CMutexGuard()
            {
                m_mutex.unlock();    
            }

        private:

            CMutex& m_mutex;
    };
}

