/*
Author: coderqiuan@163.com
Created on: 2016-12-15 17:48
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <inttypes.h>

#include <vector>
#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>

namespace qiuan
{
#define _assert() fprintf(stderr, "func:%s assert - %s:%d\n", __func__, __FILE__, __LINE__); assert(0)
}

namespace qiuan
{
    pid_t pid();

    void sleep_s(uint32_t sec);

    void sleep_ms(uint32_t millisec);

    std::string get_proc_path();

    std::string get_proc_name();

    int exe_cmd(const char* cmd);

    int exe_cmd(const char* cmd, std::string& out);
}

namespace qiuan
{
    template<typename Type> class CSingleton
    {
        public:

            explicit CSingleton()
            {

            }

            static Type& instance()
            {
                static Type t;

                return t;
            }
    };
}

namespace qiuan
{
    template<typename Type> Type to_number(std::string in)
    {
        std::stringstream ss;
        ss << in;

        Type value;
        ss >> value;

        return value;
    }

    template<typename Type> std::string to_string(Type value)
    {
        std::stringstream ss;

        ss << value;

        return ss.str();
    }
}

namespace qiuan
{
    std::string  to_string(const char* fmt, ...);

    int to_string(char* inbuf, int inlen, const char* fmt, ...);

    int to_string(char* inbuf, int inlen, const char* fmt, va_list& args);
}

namespace qiuan
{
    std::string sys_trim(std::string in);

    int sys_trim(const char* &start, const char* inbuf, int inlen);
}

