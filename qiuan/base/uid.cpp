/*
Author: coderqiuan@163.com
Created on: 2016-11-22 18:10
*/

#include "uid.h"

#include <sys/time.h>
static uint64_t get_time_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

using namespace qiuan;

    CUid::CUid(uint16_t uid)
    : m_seqno(0)
      , m_lasttime(0)
{
    m_uid = uid & 0x3FF;
}

CUid::~CUid()
{

}

CUid* CUid::init(uint16_t uid)
{
    uint16_t key = uid & 0x3FF;

    if(0 == key && 0 != uid)
    {
        return NULL;
    }

    uid_map::iterator it = m_uidmap.find(key);

    if(m_uidmap.end() == it)
    {
        CUid uid(key);

        m_uidmap.insert(std::make_pair(key, uid));

        it = m_uidmap.find(key);
    }

    return &it->second;
}

uint64_t CUid::uid()
{
    uint64_t curtime = get_time_ms();

    if(curtime == m_lasttime)
    {
        m_seqno = (m_seqno + 1) & 0xFFF;

        if(m_seqno == 0)
        {
            curtime = get_time_ms();

            while(curtime <= m_lasttime)
            {
                curtime = get_time_ms();
            }
        }
    }
    else
    {
        m_seqno = 0;
    }

    m_lasttime = curtime;

    return ((m_lasttime & 0x1FFFFFFFFFF) << 22) | (m_uid << 12) | (m_seqno & 0xFFF);
}

std::string CUid::log()
{
    char outbuf[1024] = { 0 };

    snprintf(outbuf, 1024, "time:%llu,uid:%u,m_seqno:%u", m_lasttime, m_uid, m_seqno);

    return outbuf;
}

CUid* CUid::instance(uint16_t uid)
{
    static CUid guid;

    return guid.init(uid);
}

