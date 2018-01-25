/*
Author: coderqiuan@163.com
Created on: 2017-01-10 14:26
*/

#pragma once

#if __cplusplus < 201103L

namespace qiuan
{
    template<typename Type> class CAtomic
    {
        private:

            CAtomic(const CAtomic&);

            const CAtomic& operator=(const CAtomic&);

        public:

            explicit CAtomic(Type v = 0)
            {
                __sync_lock_test_and_set(&m_value, v);
            }

            Type increment()
            {
                return add(1);
            }

            Type decrement()
            {
                return add(-1);
            }

            Type add(Type v)
            {
                return __sync_add_and_fetch(&m_value, v);
            }

            Type get()
            {
                return __sync_val_compare_and_swap(&m_value, 0, 0);
            }

        private:

            volatile Type m_value;
    };
}

#else //__cplusplus < 201103L

#include <atomic>

namespace qiuan
{
    template<typename Type> class CAtomic
    {
        private:

            CAtomic(const CAtomic&);

            const CAtomic& operator=(const CAtomic&);

        public:

            explicit CAtomic(Type v = 0)
                : m_value(v)
            {
            }

            Type increment()
            {
                return add(1);
            }

            Type decrement()
            {
                return add(-1);
            }

            Type add(Type v)
            {
                return m_value += v;
            }

            Type get()
            {
                return m_value.load();
            }

        private:

            std::atomic<Type> m_value;
    };
}

#endif

