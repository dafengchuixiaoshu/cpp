/*
Author: coderqiuan@163.com
Created on: 2016-11-22 17:39
*/

#pragma once

#include <map>

#include "util.h"

/*
   0---0000000000 0000000000 0000000000 0000000000 0 --- 0000000000 ---0000000000 00
   第一位未使用
   41位为毫秒级时间(2039/9/7 23:47:35)
   10位标识位(1024)，
   12位该毫秒内的计数(4096)
   加起来刚好64位，为一个Long型。
   这样的好处是，整体上按照时间自增排序，并且整个分布式系统内不会产生ID碰撞
   */

namespace qiuan
{
#define sUid(uid) CUid::instance(uid)
}

namespace qiuan
{
    class CUid
    {
        private:

            explicit CUid(uint16_t uid = 0);

            CUid* init(uint16_t uid);

            typedef std::map<uint16_t, CUid> uid_map;

        public:

            ~CUid();

            uint64_t uid();

            std::string log();

            static CUid* instance(uint16_t uid);

        private:

            uint16_t m_uid;

            uint16_t m_seqno;

            uint64_t m_lasttime;

            uid_map m_uidmap;
    };
}

