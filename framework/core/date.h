/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-30 10:52
**/

#ifndef _DUODUO_CORE_DATE_H_
#define _DUODUO_CORE_DATE_H_

#include <string>

namespace duoduo
{
    namespace core
    {
        class Date
        {
            public:

                explicit Date(uint64_t usec = 0);

                const Date& operator=(const Date& r);

                Date(const Date& r) { m_usec = r.m_usec; }

                uint64_t usec() { return m_usec; }

                std::string date(std::string seperator = " ");

                int64_t diff(const Date date) { return m_usec - date.usec(); }

            private:

                uint64_t m_usec;
        };
    }
}

#endif //_DUODUO_CORE_DATE_H_

