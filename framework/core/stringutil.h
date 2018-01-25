/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-23 12:29
 **/

#ifndef _DUODUO_CORE_STRING_UTIL_H_
#define _DUODUO_CORE_STRING_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
//#include <inttypes.h>

#include <vector>
#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>

namespace duoduo
{
    namespace core
    {
        template<typename T> T toNumber(std::string in)
        {
            std::stringstream ss;
            ss << in;

            T t;
            ss >> t;

            return t;
        }

        template<typename T> std::string toString(T t)
        {
            std::stringstream ss;

            ss << t;

            return ss.str();
        }

        std::string toString(const char* fmt, ...)
        {
            va_list args;

            va_start(args, fmt);

            char in[1024] = { 0 };

            toString(in, 1024, fmt, args);

            va_end(args);

            return in;
        }

        int toString(char* in, size_t inlen, const char* fmt, ...)
        {
            va_list args;

            va_start(args, fmt);

            int rc = vsnprintf(in, inlen, fmt, args);

            va_end(args);

            return rc;
        }

        int toString(char* in, size_t inlen, const char* fmt, va_list& args)
        {
            return vsnprintf(in, inlen, fmt, args);
        }

        std::string trim(std::string in)
        {
            std::string out;
            const char* start;

            size_t outlen = trim(start, in.c_str(), in.size());

            if(inlen > 0)
            {
                out.append(start, outlen);
            }

            return out;
        }

        size_t trim(const char* &start, const char* in, size_t inlen)
        {
            if(NULL == in || inlen <= 0)
            {
                return 0;
            }

            start = in;
            const char* end = in + inlen;

            while(start < end)
            {
                if(0 == *start)
                {
                    return 0;
                }
                else if((uint8_t)*start > 0x20)
                {
                    break;
                }
                else
                {
                    ++start;
                }
            }

            while(start < end)
            {
                --end;

                if((uint8_t)*end > 0x20)
                {
                    ++end;

                    break;
                }
            }

            return end - start;
        }
    }
}

#endif //_DUODUO_CORE_STRING_UTIL_H_

