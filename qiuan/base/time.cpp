/*
Author: coderqiuan@163.com
Created on: 2016-11-09 11:09
*/

#include "time.h"

using namespace qiuan;

static const int k_microsercond_pre_second = 1000 * 1000;

CTime::CTime(uint64_t usec)
{
    if(0 == usec)
    {
        refresh();
    }
    else
    {
        m_usec = usec;
    }
}

CTime::CTime(const CTime& r)
{
    m_usec = r.m_usec;
}

const CTime& CTime::operator=(const CTime& r)
{
    if(&r != this)
    {
        m_usec = r.m_usec;
    }

    return *this;
}

CTime::~CTime()
{

}

void CTime::refresh()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    m_usec = tv.tv_sec * k_microsercond_pre_second + tv.tv_usec;
}

uint64_t CTime::usec() const
{
    return m_usec;
}

int64_t CTime::diff(const CTime timestamp)
{
    return m_usec - timestamp.usec();
}

std::string CTime::stime(TimeType type)
{
    struct tm tm_time;
    time_t second = static_cast<time_t>(m_usec / k_microsercond_pre_second);

    //if(NULL == gmtime_r(&second, &tm_time))
    if(NULL == localtime_r(&second, &tm_time))
    {
        return "time_tostring_error";
    }
    else
    {
        char out_buf[32] = { 0 };

        if(TIME_LOG == type)
        {
            snprintf(out_buf, sizeof(out_buf) - 1, "%04d%02d%02d-%02d:%02d:%02d.%06d",
                    tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                    tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                    static_cast<int>(m_usec % k_microsercond_pre_second));
        }
        else if(TIME_BASE == type)
        {
            snprintf(out_buf, sizeof(out_buf) - 1, "%04d-%02d-%02d %02d:%02d:%02d",
                    tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                    tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
        }
        else if(TIME_NAME == type)
        {
            snprintf(out_buf, sizeof(out_buf) - 1, "%04d%02d%02d_%02d%02d%02d",
                    tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                    tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
        }
        else
        {
            snprintf(out_buf, sizeof(out_buf) - 1, "undefined_timetype");
        }

        return out_buf;
    }
}

