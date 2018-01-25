/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-23 11:02
 **/

#ifndef _DUODUO_CORE_SINGLETON_H_
#define _DUODUO_CORE_SINGLETON_H_

#include <pthread.h>

#include <NoCopyable.h>

namespace duoduo
{
    namespace core
    {
        template<typename T> class Singleton
        {
            public:

                static T& instance()
                {
                    static T t;
                    return t;
                }
        };

        //C++模板除了萃取的又一个新技术，SFINAE技术，即匹配失败不是错误。
        namespace muduo
        {
            // This doesn't detect inherited member functions!
            // http://stackoverflow.com/questions/1966362/sfinae-to-check-for-inherited-member-functions
            // http://blog.csdn.net/freeelinux/article/details/53429009
            template<typename T> struct HasNoDestroy 
            {
                template <typename C> static char test(typeof(&C::NoDestroy)); // or decltype in C++11
                template <typename C> static int32_t test(...);
                static const bool value = sizeof(test<T>(0)) == 1;
            };

            template<typename T> class Singleton : NoCopyable
            {
                public:

                    static T& instance()
                    {
                        pthread_once(&ponce_, &Singleton::init);
                        assert(value_ != NULL);
                        return *value_;
                    }

                private:

                    Singleton();
                    ~Singleton();

                    static void init()
                    {
                        value_ = new T();
                        if (!HasNoDestroy<T>::value)
                        {
                            ::atexit(destroy);
                        }
                    }

                    static void destroy()
                    {
                        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
                        T_must_be_complete_type dummy; (void) dummy;

                        delete value_;
                        value_ = NULL;
                    }

                private:
                    static pthread_once_t ponce_;
                    static T*             value_;
            };

            template<typename T> T* Singleton<T>::value_ = NULL;
            template<typename T> pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;
        }
    }
}

#endif //_DUODUO_CORE_SINGLETON_H_

