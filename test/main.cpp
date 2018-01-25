/*
Author: coderqiuan@163.com
Created on: 2016-11-10 18:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base/uid.h"
#include "base/file.h"
#include "base/time.h"
#include "base/util.h"
#include "base/mutex.h"
#include "base/stream.h"
#include "base/logger.h"
#include "base/queue.h"
#include "base/atomic.h"
#include "base/thread.h"

using namespace qiuan;

int test_cmd()
{
    std::string out;

    exe_cmd("ls -l", out);

    LOG_INFO << "exe_cmd:" << out;
}

int test_uid()
{
    CUid* uid = CUid::instance(1);
    uint64_t u = uid->uid();
    LOG_INFO << "test_uid:" << u << uid->log();

    uint64_t stamp = (u >> 22) & 0x1FFFFFFFFFF;
    uint16_t mid = (u >> 12) & 0x3FF;
    uint16_t seqno = u & 0xFFF;
    LOG_INFO << "stamp:" << stamp << ",mid:" << mid << ",seqno:" << seqno;
}

int test_time()
{
    CTime curtime;

    sleep_s(1);

    LOG_INFO << "time:" << curtime.usec();
    LOG_INFO << "diff:" << curtime.diff(CTime());
    LOG_INFO << "log:" << curtime.stime(CTime::TIME_LOG);
    LOG_INFO << "base:" << curtime.stime(CTime::TIME_BASE);
    LOG_INFO << "name:" << curtime.stime(CTime::TIME_NAME);
}

int test_file()
{
    std::string filename("test.log");

    std::string in("1234567890987654321");
    CWriteFile writefile(filename);
    LOG_INFO << "filesize:" << writefile.filesize();
    bool rw = writefile.write(in) > 0;
    if(rw)
    {
        LOG_INFO << "append file:" << in;
    }
    else
    {
        LOG_ERROR << "append file failed:" << rw << ",errno:" << writefile.ferrno();
    }
    writefile.flush();
    LOG_INFO << "filesize:" << writefile.filesize() << ",appendsize:" << writefile.writesize();

    int rr = 0;
    std::string out;
    CReadFile readfile(filename);
    while((rr = readfile.read(out)) > 0 && out.size() < 64 * 1024);
    if(rr < 0)
    {
        LOG_ERROR << "read file failed:" << rr << ",errno:" << readfile.ferrno();
    }
    else
    {
        LOG_INFO << "read file:" << out;
    }

    rr = 0;
    readfile.reset(filename + "_bak");
    while((rr = readfile.read(out)) > 0 && out.size() < 64 * 1024);
    if(rr < 0)
    {
        LOG_ERROR << "read file failed:" << rr << ",errno:" << readfile.ferrno();
    }
    else
    {
        LOG_INFO << "read file:" << out;
    }

    rr = 0;
    readfile.reset("./file/");
    while((rr = readfile.read(out)) > 0 && out.size() < 64 * 1024);
    if(rr < 0)
    {
        LOG_ERROR << "read file failed:" << rr << ",errno:" << strerror(readfile.ferrno());
    }
    else
    {
        LOG_INFO << "read file:" << out;
    }
}

int main(int argc, char* argv[])
{
    test_cmd();
    test_uid();
    test_time();
    test_file();

    CThread t;

    LOG_NOTICE << "main end";

    getchar();
    return 0;
}

