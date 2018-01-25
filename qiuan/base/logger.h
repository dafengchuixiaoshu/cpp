/*
Author: coderqiuan@163.com
Created on: 2016-11-10 14:21
*/

#pragma once

#include "base/file.h"
#include "base/mutex.h"
#include "base/stream.h"

namespace qiuan
{
    enum log_level
    {
        log_info = 0,
        log_warning,
        log_error,
        log_notice,
        log_level_count
    };

    typedef void (*log_redict_func)(const char* inbuf, int inlen);

    class CLogFile
    {
        private:

            CLogFile(const CLogFile&);

            const CLogFile& operator=(const CLogFile&);

            std::string filename(CTime& curtime, log_level loglevel);

        public:

            explicit CLogFile(const std::string logname = "");

            ~CLogFile();

            void redict(const char* inbuf, int inlen);

            void set_log_name(const std::string logname);

            const std::string& get_log_name() { return m_logname; }

            bool logger(CTime& curtime, const char* inbuf, int inlen, log_level loglevel);

        public:

            log_level get_log_level() { return m_loglevel; }

            void set_log_level(log_level loglevel) { m_loglevel = loglevel; }

            void set_max_file_size(size_t maxfilesize) { m_maxfilesize = maxfilesize; }

            void set_redict_func(log_redict_func redictfunc) { m_redictfunc = redictfunc; }

            void set_flush_interval(size_t flushinterval) { m_flushinterval = flushinterval; }

        private:

            log_level m_loglevel;

            size_t m_maxfilesize;

            size_t m_flushinterval;

            std::string m_logname;

            log_redict_func m_redictfunc;

            CMutex m_mutex[log_level_count];

            uint64_t m_filetime[log_level_count];

            CWriteFile m_writefile[log_level_count];
    };

    class CLogger
    {
        private:

            CLogger(const CLogger&);

            const CLogger& operator=(const CLogger&);

        public:

            explicit CLogger(log_level loglevel, const char* file, int line, const char* func);

            ~CLogger();

            CLogStream& stream() { return m_logstream; }

        private:

            CTime m_curtime;

            log_level m_loglevel;

            CLogStream m_logstream;
    };
}

namespace qiuan {
#define slogfile CSingleton<CLogFile>::instance()

#define setlogname(logname) slogfile.set_log_name(logname)
#define setlogredictfunc(func) slogfile.set_redict_func(func)
#define setloglevel(loglevel) slogfile.set_log_level(loglevel)
#define setlogmaxfilesize(maxfilesize) slogfile.set_max_file_size(maxfilesize)
#define setlogflushinterval(flushinterval) slogfile.set_flush_interval(flushinterval)

#define getlogname() slogfile.get_log_name()
#define getloglevel() slogfile.get_log_level()

#define slogredict(inbuf, inlen) slogfile.redict(inbuf, inlen)
#define slogger(curtime, inbuf, inlen, loglevel) slogfile.logger(curtime, inbuf, inlen, loglevel)

#define LOG_INFO    if(getloglevel() <= log_info) CLogger(log_info, __FILE__, __LINE__, __func__).stream()
#define LOG_WARNING if(getloglevel() <= log_warning) CLogger(log_warning, __FILE__, __LINE__, __func__).stream()
#define LOG_ERROR   if(getloglevel() <= log_error) CLogger(log_error, __FILE__, __LINE__, __func__).stream()
#define LOG_NOTICE  if(getloglevel() <= log_notice) CLogger(log_notice, __FILE__, __LINE__, __func__).stream()
}

