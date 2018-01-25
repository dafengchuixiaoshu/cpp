/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-22 12:11
 */

#ifndef _DUODUO_CORE_SYSTEM_UTIL_H_
#define _DUODUO_CORE_SYSTEM_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <inttypes.h>

#include <string>
#include <assert.h>
#include <algorithm>

namespace duoduo
{
    namespace core
    {
#define ASSERT(condition) \
        fprintf(stderr, "%s:%d %s assert\n", __FILE__, __FILE__, __func__); \
        assert(condition);

#define ASSERT(out, condition) \
        fprintf(out, "%s:%d %s assert\n", __FILE__, __FILE__, __func__); \
        assert(condition);
    }

    namespace core
    {
        /**
         *
         */
        pid_t pid() { return ::getpid(); }

        void sleepSec(uint32_t sec) { sleep(sec); }

        void sleepMSec(uint32_t msec) { usleep(msec * 1000); }

        /**
         *
         */
        int exe_cmd(const char* cmd);

        int exe_cmd(const char* cmd, std::string& out);

        /**
         *
         */
        uint64_t timestamp()
        {
            struct timeval tv;

            gettimeofday(&tv, NULL);

            return (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
        }

        /**
         *
         */
        std::string get_proc_path();

        std::string get_proc_name();

        void get_proc_path_name(std::string& path, std::string& name);
    }
}

#endif //_DUODUO_CORE_SYSTEM_UTIL_H_

