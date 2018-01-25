/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-30 12:17
**/

#include "date.h"
#include "systemutil.h"

using namespace duoduo::core;

Date::Date(uint64_t usec)
{
    if(0 == usec)
    {
        timestamp();
    }
    else
    {
        m_usec = usec;
    }
}

const Date& Date::operator=(const Date& r)
{
    if(&r != this)
    {
        m_usec = r.m_usec;
    }

    return *this;
}

std::string Date::date(std::string seperator);
{
    struct tm tm_time;
    static const int k_microsercond_pre_second = 1000 * 1000;
    time_t second = static_cast<time_t>(m_usec / k_microsercond_pre_second);

    char out_buf[64] = { 0 };
    //if(NULL == gmtime_r(&second, &tm_time)) UTC时间
    if(NULL != localtime_r(&second, &tm_time))//local时间
    {
        sprintf(out_buf, "%04d%02d%02d%s%02d:%02d:%02d.%06d",
                    tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                    seperator.c_str(),
                    tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                    static_cast<int>(m_usec % k_microsercond_pre_second));
    }

    return out_buf;
}

