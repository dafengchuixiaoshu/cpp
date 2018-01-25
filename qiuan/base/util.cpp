/*
Author: coderqiuan@163.com
Created on: 2016-12-15 17:48
*/

#include "util.h"

namespace qiuan
{
    pid_t pid()
    {
        return ::getpid();
    }

    void sleep_s(uint32_t sec)
    {
        sleep(sec);
    }

    void sleep_ms(uint32_t millisec)
    {
        usleep(millisec * 1000); 
    }

    static std::string get_proc()
    {
        char cmd[32] = { 0 };

        snprintf(cmd, 31, "ls -l /proc/%u/exe", pid());

        std::string name;

        if(exe_cmd(cmd, name) > 0)
        {
            std::string::size_type pos = name.rfind(" ");

            if(std::string::npos != pos)
            {
                return sys_trim(name.substr(pos + 1));
            }
        }

        return "";
    }

    std::string get_proc_path()
    {
        std::string proc = get_proc();

        std::string::size_type pos = proc.rfind("/");

        if(std::string::npos != pos)
        {
            return proc.substr(0, pos);
        }

        return "";
    }

    std::string get_proc_name()
    {
        std::string proc = get_proc();

        std::string::size_type pos = proc.rfind("/");

        if(std::string::npos != pos)
        {
            return proc.substr(pos + 1);
        }

        return "";
    }

    int exe_cmd(const char* cmd)
    {
        std::string out;

        return exe_cmd(cmd, out);
    }

    static const int k_cmd_buf_len = 1024 - 1;

    int exe_cmd(const char* cmd, std::string& out)
    {
        FILE* fp = popen(cmd, "r");

        if(NULL == fp)
        {
            return -1;
        }

        char buf[k_cmd_buf_len + 1] = { 0 };

        while(NULL != fgets(buf, k_cmd_buf_len, fp))
        {
            out += buf;    
        }

        if(-1 == pclose(fp))
        {
            return -2;
        }

        return out.size();
    }

    std::string to_string(const char* fmt, ...)
    {
        va_list args;

        va_start(args, fmt);

        char inbuf[1024] = { 0 };

        if(0 <= to_string(inbuf, 1023, fmt, args))
        {
            inbuf[0] = '\0';
        }

        va_end(args);

        return inbuf;
    }

    int to_string(char* inbuf, int inlen, const char* fmt, ...)
    {
        va_list args;

        va_start(args, fmt);

        int v = vsnprintf(inbuf, inlen, fmt, args);

        va_end(args);

        return v;
    }

    int to_string(char* inbuf, int inlen, const char* fmt, va_list& args)
    {
        return vsnprintf(inbuf, inlen, fmt, args);
    }

    std::string sys_trim(std::string in)
    {
        while((uint8_t)in[0] <= 0x20)
        {
            in = in.substr(1);
        }

        while((uint8_t)in[in.size() - 1] <= 0x20)
        {
            in.erase(in.size() - 1);
        }

        return in;
    }

    int sys_trim(const char* &start, const char* inbuf, int inlen)
    {
        if(NULL == inbuf || inlen <= 0)
        {
            return -1;
        }

        start = inbuf;

        const char* end = inbuf + inlen;

        while(start < end)
        {
            if(0 == *start)
            {
                return 0;
            }
            else if((uint8_t)*start > 0x20)
            {
                break;
            }
            else
            {
                ++start;
            }
        }

        while(start < end)
        {
            --end;

            if((uint8_t)*end > 0x20)
            {
                ++end;

                break;
            }
        }

        return end - start;
    }
}

