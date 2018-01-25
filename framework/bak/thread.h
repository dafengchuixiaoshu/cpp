/*
Author: coderqiuan@163.com
Created on: 2017-01-10 17:31
*/

#pragma once

#include <pthread.h>

#include "util.h"
#include "atomic.h"

namespace qiuan
{
    typedef void (*thread_func)(void*);

    class CThread
    {
        private:

            CThread(const CThread&);

            const CThread& operator=(const CThread&);

        public:

            explicit CThread();

            ~CThread();

            bool join();

            bool isok() { return m_isok; }

            pthread_t tid() { return m_tid; }

            const std::string& name() { return m_name; }

            static uint32_t threadcount() { return m_threadcount.get(); }

            bool start(thread_func func, void* params, const std::string& name = "", int stacksize = 1024 * 1024);

        private:

            pthread_t m_tid;

            std::string m_name;

            volatile bool m_isok;

            volatile bool m_isjoined;

            uint32_t m_threadnumber;

            static CAtomic<uint32_t> m_threadcount;
    };
}

