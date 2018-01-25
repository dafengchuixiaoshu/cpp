/*
Author: coderqiuan@163.com
Created on: 2016-11-10 17:02
*/

#include "time.h"
#include "logger.h"

using namespace qiuan;

static const int k_filename_size = 1024 - 1;

static const size_t k_log_file_size = 10 * 1024 * 1024;

static const int k_microsecond_per_day = 24 * 3600 * 1000 * 1000;

static const char g_log_level[log_level_count][32] = {"info", "warning", "error", "notice" };

static const std::string k_log_file_start = "\n============================== START ==============================\n\n";

void default_log_redict_func(const char* inbuf, int inlen)
{
    fwrite(inbuf, inlen, 1, stdout);
}

    CLogFile::CLogFile(const std::string logname)
    : m_loglevel(log_info)
    , m_maxfilesize(k_log_file_size)
    , m_flushinterval(3 * 1000 * 1000)
      , m_redictfunc(default_log_redict_func)
{
    set_log_name(logname);
}

CLogFile::~CLogFile()
{

}

void CLogFile::redict(const char* inbuf, int inlen)
{
    if(NULL != m_redictfunc)
    {
        m_redictfunc(inbuf, inlen);
    }
}

void CLogFile::set_log_name(const std::string logname)
{
    std::string procpath = get_proc_path();

    if(procpath.empty())
    {
        m_logname = logname.empty() ? "./unknown" : ('/' == logname[0] ? logname : "./unknown");
    }
    else
    {
        m_logname = logname.empty() ? (procpath + "/../logs/" + get_proc_name()) : ('/' == logname[0] ? logname : (procpath + "/" + logname));
    }

    std::string::size_type pos = m_logname.rfind("/");

    if(std::string::npos != pos && pos > 0)
    {
        std::string out;

        char filepath[k_filename_size + 1] = { 0 };

        snprintf(filepath, k_filename_size, "mkdir -p %s", m_logname.substr(0, pos).c_str());

        exe_cmd(filepath, out);
    }
}

std::string CLogFile::filename(CTime& curtime, log_level loglevel)
{
    char filename[k_filename_size + 1] = { 0 };

    snprintf(filename, k_filename_size, "%s_%s_%s_%u.log", m_logname.c_str(), g_log_level[loglevel], curtime.stime(CTime::TIME_NAME).c_str(), pid());

    m_filetime[loglevel] = curtime.usec() / k_microsecond_per_day * k_microsecond_per_day;

    return filename;
}

bool CLogFile::logger(CTime& curtime, const char* inbuf, int inlen, log_level loglevel)
{
    CMutexGuard g(m_mutex[loglevel]);

    CWriteFile& writefile = m_writefile[loglevel];

    if(!writefile.isok()
            || m_maxfilesize <= writefile.filesize()
            || curtime.usec() / k_microsecond_per_day * k_microsecond_per_day != m_filetime[loglevel])
    {
        writefile.reset(filename(curtime, loglevel));

        if(writefile.isok())
        {
            writefile.write(k_log_file_start);
        }
        else
        {
            return false;
        }
    }

    bool r = writefile.write(inbuf, inlen) > 0;

    writefile.flush(m_flushinterval);

    return r;
}

    CLogger::CLogger(log_level loglevel, const char* file, int line, const char* func)
: m_loglevel(loglevel)
{
    const char* p;

    m_logstream << g_log_level[loglevel] << "-" << m_curtime.stime()
        << " " << ((NULL == (p = strrchr(file, '/'))) ? file : p + 1)
        << ":" << line
        << " " << func
        << ":[";
}

CLogger::~CLogger()
{
    m_logstream << "]\n";

    slogredict(m_logstream.c_str(), m_logstream.size());

    slogger(m_curtime, m_logstream.c_str(), m_logstream.size(), m_loglevel);
}


