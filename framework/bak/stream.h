/*
Author: coderqiuan@163.com
Created on: 2016-12-21 22:09
*/

#pragma once

#include "util.h"

namespace qiuan
{
    template<uint32_t streamsize = 1024> class Stream
    {
        private:

            Stream(const Stream& r);

            const Stream& operator=(const Stream& r);

            bool less(int inlen)
            {
                return inlen > 0 && inlen < m_data + streamsize - m_current;
            }

        public:

            explicit Stream()
                : m_current(m_data)
            {
                *m_current = '\0';
            }

            const char* c_str() { return m_data; }

            uint32_t size() { return m_current - m_data; }

            std::string to_string() { return std::string(c_str(), size()); }

        public:

            bool append(const std::string in)
            {
                return append(in.c_str(), in.size());
            }

            bool append(const char* inbuf, int inlen)
            {
                if(less(inlen))
                {
                    memcpy(m_current, inbuf, inlen);

                    m_current += inlen;

                    return true;
                }

                return false;
            }

            template<typename Type> Stream& operator<<(Type value)
            {
                append(qiuan::to_string<Type>(value));

                return *this;
            }

            Stream& operator<<(Stream& value)
            {
                if(this != &value)
                {
                    append(value.c_str(), value.size());
                }

                return *this;
            }

            Stream& operator<<(const std::string& value)
            {
                append(value.c_str(), value.size());

                return *this;
            }

        private:

            char* m_current;

            char m_data[streamsize];
    };

    typedef Stream<1024>     CStream;
    typedef Stream<2 * 1024> CLogStream;
    typedef Stream<4 * 1024> CBigStream;
}

