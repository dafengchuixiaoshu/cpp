/*
Author: coderqiuan@163.com
Created on: 2016-11-09 10:49
*/

#pragma once

#include "util.h"

#include <sys/time.h>

namespace qiuan
{
    class CTime
    {
        public:

            explicit CTime(uint64_t usec = 0);

            CTime(const CTime& r);

            const CTime& operator=(const CTime& r);

            ~CTime();

            void refresh();

            uint64_t usec() const;

            int64_t diff(const CTime timestamp);

            enum TimeType
            {
                TIME_LOG = 0,
                TIME_BASE, 
                TIME_NAME,
            };

            std::string stime(TimeType type = TIME_LOG);

        private:

            uint64_t m_usec;
    };
}

