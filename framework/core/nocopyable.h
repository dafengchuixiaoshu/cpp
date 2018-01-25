/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-23 12:20
 **/

#ifndef _DUODUO_CORE_NOCOPYABLE_H_
#define _DUODUO_CORE_NOCOPYABLE_H_

namespace duoduo
{
    namespace core
    {
        class NoCopyable
        {
            private:

                NoCopyable(const NoCopyable&);
                const NoCopyable& operator=(const NoCopyable&);

            protected:

                NoCopyable() {}
                ~NoCopyable() {}
        };
    }

    typedef core::NoCopyable NoCopyable;
}

#endif //_DUODUO_CORE_NOCOPYABLE_H_
