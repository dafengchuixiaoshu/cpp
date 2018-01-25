/*
Author: coderqiuan@163.com
Created on: 2016-12-27 17:03
*/

#pragma once

#include <deque>

#include "condition.h"

namespace qiuan
{
    template<typename Type, uint32_t queuesize = 0> class CQueue
    {
        private:

            CQueue(const CQueue&);

            const CQueue& operator=(const CQueue&);

        public:

            explicit CQueue()
                : m_queuesize(queuesize)
                  , m_condition(m_mutex)
        {

        }

            ~CQueue()
            {

            }

            int size()
            {
                CMutexGuard g(m_mutex);

                return m_queue.size();
            }

            bool push(const Type& x, bool isback = true)
            {
                CMutexGuard g(m_mutex);

                if(m_queuesize > 0)
                {
                    if(m_queue.size() >= m_queuesize)
                    {
                        m_condition.signal();

                        return false;
                    }
                }

                if(isback)
                {
                    m_queue.push_back(x);
                }
                else
                {
                    m_queue.push_front(x);
                }

                m_condition.signal();

                return true;
            }

            bool pop(Type& x, int millisec = 0, bool ispop = true)
            {
                CMutexGuard g(m_mutex);

                if(m_queue.empty())
                {
                    m_condition.wait(millisec);
                }

                if(m_queue.empty())
                {
                    return false;
                }
                else
                {
                    x = m_queue.front();

                    if(ispop)
                    {
                        m_queue.pop_front();
                    }

                    return true;
                }
            }

        private:

            CMutex m_mutex;

            uint32_t m_queuesize;

            CCondition m_condition;

            std::deque<Type> m_queue;
    };
}

