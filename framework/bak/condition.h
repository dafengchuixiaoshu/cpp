/*
Author: coderqiuan@163.com
Created on: 2016-12-27 16:39
*/

#pragma once

#include <errno.h>
#include <sys/time.h>

#include "mutex.h"

namespace qiuan
{
    class CCondition
    {
        private:

            CCondition(const CCondition&);

            const CCondition& operator=(const CCondition&);

        public:

            explicit CCondition(CMutex& mutex)
                : m_mutex(mutex)
            {
                if(0 != pthread_cond_init(&m_condition, NULL))
                {
                    _assert();
                }
            }

            ~CCondition()
            {
                if(0 != pthread_cond_destroy(&m_condition))
                {
                    _assert();
                }
            }

            void signal()
            {
                if(0 != pthread_cond_signal(&m_condition))
                {
                    _assert();
                }
            }

            bool wait(uint32_t millisec)
            {
                if(0 == millisec)
                {
                    pthread_cond_wait(&m_condition, &m_mutex.mutex());

                    return false;
                }
                else
                {
                    struct timeval tv;
                    gettimeofday(&tv, 0);
                    
                    struct timespec ts;
                    ts.tv_sec = millisec / 1000 + tv.tv_sec;
                    ts.tv_nsec = (millisec % 1000) * 1000 * 1000 + tv.tv_usec * 1000;

                    ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
                    ts.tv_nsec = ts.tv_nsec % (1000 * 1000 * 1000);

                    return ETIMEDOUT == pthread_cond_timedwait(&m_condition, &m_mutex.mutex(), &ts);
                }
            }

        private:

            CMutex& m_mutex;

            pthread_cond_t m_condition;
    };
}

