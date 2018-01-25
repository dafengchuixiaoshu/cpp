/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-30 14:28
 **/

#ifndef _DUODUO_CORE_ATOMIC_H_
#define _DUODUO_CORE_ATOMIC_H_

#include "nocopyable.h"

#if __cplusplus < 201103L

namespace duoduo
{
	namespace core
	{
		template<typename T> class Atomic : public NoCopyable
		{
			public:

				explicit Atomic(T v = 0)
				{
					__sync_lock_test_and_set(&m_value, v);
				}

				T increment()
				{
					return add(1);
				}

				T decrement()
				{
					return add(-1);
				}

				T add(T v)
				{
					return __sync_add_and_fetch(&m_value, v);
				}

				T get()
				{
					return __sync_val_compare_and_swap(&m_value, 0, 0);
				}

			private:

				volatile T m_value;
		};
	}
}

#else //__cplusplus < 201103L

#include <atomic>

namespace duoduo
{
	namespace core
	{
		template<typename T> class Atomic : public NoCopyable
		{
			public:

				explicit Atomic(T v = 0)
					: m_value(v)
				{

				}

				T increment()
				{
					return add(1);
				}

				T decrement()
				{
					return add(-1);
				}

				T add(T v)
				{
					return m_value += v;
				}

				T get()
				{
					return m_value.load();
				}

			private:

				std::atomic<T> m_value;
		};
	}
}
#endif

#endif //_DUODUO_CORE_ATOMIC_H_

