/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-24 09:49
 **/

#include "SystemUtil.h"

using namespace duoduo::core;

static std::string get_proc()
{
    char cmd[1024] = { 0 };
    //lrwxrwxrwx 1 root root 0 Nov 24 10:21 /proc/3842/exe -> /home/qiuan/cpp/build/bin/test
    sprintf(cmd, "ls -l /proc/%u/exe", pid());

    std::string proc;
    if(exe_cmd(cmd, proc) > 0)
    {
        std::string::size_type pos = proc.rfind(" ");

        if(std::string::npos != pos)
        {
            return proc.substr(pos + 1);
        }
    }

    return proc;
}

int exe_cmd(const char* cmd)
{
	std::string out;

	return exe_cmd(cmd, out);
}

int exe_cmd(const char* cmd, std::string& out)
{
	FILE* fp = popen(cmd, "r");

	if(NULL == fp)
	{
		return -1;
	}

	char buf[512] = { 0 };

	while(NULL != fgets(buf, 511, fp))
	{
		out += buf;
	}

	if(-1 == pclose(fp))
	{
		return -2;
	}

	return out.size();
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

void get_proc_path_name(std::string& path, std::string& name)
{
	std::string proc = get_proc();

	std::string::size_type pos = proc.rfind("/");

	if(std::string::npos != pos)
	{
		path = proc.substr(0, pos);
		name = proc.substr(pos + 1);
	}
}

