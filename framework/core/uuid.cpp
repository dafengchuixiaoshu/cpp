/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-24 11:39
 **/

#include "uuid.h"
#include "systemutil.h"

#include <sys/time.h>

using namespace duoduo::core;

UUID::UUID(uint32_t tag)
{
    m_uid._tag = tag & 0x3FF;
}

UUID::~UUID()
{

}

UUID* UUID::init(uint32_t tag)
{
    uint32_t key = tag & 0x3FF;

    if(0 == key && 0 != tag)
    {
        return NULL;
    }

    tag_map::iterator it = m_tagmap.find(key);

    if(m_tagmap.end() == it)
    {
        UUID uuid(key);

        //m_tagmap[key] = uuid;
        m_tagmap.insert(std::make_pair(key, uuid));

        it = m_tagmap.find(key);
    }

    return &it->second;
}

Uid UUID::uid()
{
    uint64_t curtime = timestamp();

    if(curtime == m_uid._lastTime)
    {
        m_uid._seqno = (++m_uid._seqno) & 0xFFF;

        if(m_uid._seqno == 0)
        {
            curtime = timestamp();

            while(curtime <= m_uid._lastTime)
            {
                curtime = timestamp();
            }
        }
    }
    else
    {
        m_uid._seqno = 0;
    }

    m_uid._lastTime = curtime;

    m_uid._uuid = ((m_uid._lastTime & 0x1FFFFFFFFFF) << 22) | (m_uid._tag << 12) | m_uid._seqno;

    return m_uid;
}

uint64_t UUID::uuid()
{
    return uid()._uuid;
}

UUID* UUID::instance(uint32_t uid)
{
    static UUID uuid;

    return uuid.init(uid);
}

