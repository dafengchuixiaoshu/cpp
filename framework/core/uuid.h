/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-24 11:24
 **/

#ifndef _DUODUO_CORE_UUID_H_
#define _DUODUO_CORE_UUID_H_

#include <map>
#include <string>

#include "nocopyable.h"

/**
  0---0000000000 0000000000 0000000000 0000000000 0 --- 0000000000 ---0000000000 00
  第一位未使用
  41位为毫秒级时间(2039/9/7 23:47:35)
  10位标识位(1024)，
  12位该毫秒内的计数(4096)
  加起来刚好64位，为一个Long型。
  这样的好处是，整体上按照时间自增排序，并且整个分布式系统内不会产生ID碰撞
  */
namespace duoduo
{
	namespace core
	{
        struct Uid
        {
            Uid() : _tag(0), _seqno(0), _lastTime(0), _uuid(0) {}

            uint32_t _tag;
            uint32_t _seqno;
            uint64_t _lastTime;

            uint64_t _uuid;
        };

		class UUID
		{
			private:

                UUID* init(uint32_t tag);

                explicit UUID(uint32_t tag = 0);

                typedef std::map<uint32_t,UUID> tag_map;

            public:
                
                ~UUID();

                Uid uid();

                uint64_t uuid();

                static UUID* instance(uint32_t tag);

            private:

                Uid m_uid;

                tag_map m_tagmap;
		};
	}
}

#endif //_DUODUO_CORE_UUID_H_

