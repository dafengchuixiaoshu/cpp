/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-30 14:43
 **/

#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "file.h"

/*
linux中文件描述符有一个属性:CLOEXEC,当调用exec成功后，文件会自动关闭。
在2.6.23以前需要调用fcntl(fd,F_SETFD, FD_CLOEXEC),来设置这个属性。在新版本中只需要在open函数中设置O_CLOEXEC这个标志就可以。
虽然新版本支持在open时设置CLOEXEC，但是在编译的时候还是会提示错误
error: ‘O_CLOEXEC’ undeclared (first use in this function)。

原来这个新功能要求我们手动去打开，需要设置一个宏(_GNU_SOURCE)。可通过以下两种方法来设置这个宏以打开新功能：
1. 在源代码中加入 #define _GNU_SOURCE
2. 在编译参数中加入 -D_GNU_SOURCE
*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

using namespace duoduo::core;

ReadFile::ReadFile(std::string filename) :
	m_file(-1),
	m_errno(0),
	m_filesize(0)
{
	if(!filename.empty())
	{
		reset(filename);
	}
}

int ReadFile::reset(std::string filename)
{
	close();

	m_file = ::open(filename.c_str(), O_RDONLY | O_CLOEXEC);

	if(m_file < 0)
	{
		m_errno = errno;
	}
}

int ReadFile::read(std::string& out)
{
	if(m_file < 0)
	{
		return -1;
	}

	if(0 == m_filesize)
	{
		struct stat statbuf;

		if(0 == ::fstat(m_file, &statbuf))
		{
			m_filesize = statbuf.st_size;
			/*
			   if(S_ISREG(statbuf.st_mode)) //是否为一般文件
			   {
			   m_filesize = statbuf.st_size;
			   m_createTime = statbuf.st_ctime;
			   m_modifyTime = statbuf.st_mtime;
			   }
			   else if(S_ISDIR(statbuf.st_mode)) //是否为目录
			   {
			   m_errno = EISDIR;

			   return -3;
			   }
			   */
		}
		else
		{
			m_errno = errno;

			return -2;
		}
	}

	static const int k_read_buffer_size = 64 * 1024 - 1;
	
	char buf[k_read_buffer_size + 1] = { 0 };

	int readsize = ::read(m_file, buf, k_read_buffer_size);

	if(readsize < 0)
	{
		m_errno = errno;

		return -4;
	}
	else if(readsize + out.size() > m_filesize)
	{
		return -5;
	}
	else if(readsize > 0)
	{
		out.append(buf, readsize);
	}

	return m_filesize - out.size();
}

//////////////////////////////////////////////////////////////////////

WriteFile::WriteFile(std::string filename)
: m_file(NULL)
, m_errno(0)
, m_filesize(0)
	, m_writesize(0)
{
	if(!filename.empty())
	{
		reset(filename);
	}
}

WriteFile::~WriteFile()
{
	if(NULL != m_file)
	{
		flush();

		::fclose(m_file);
	}
}

void WriteFile::flush(uint64_t interval)
{
	CTime curtime;

	if(NULL != m_file && curtime.diff(m_flushinterval) >= interval)
	{
		::fflush(m_file);

		m_flushinterval.refresh();
	}
}

int WriteFile::reset(std::string filename)
{
	if(NULL != m_file)
	{
		flush();

		::fclose(m_file);
	}

	m_writesize = 0;

	m_filename = filename;

	m_flushinterval.refresh();

	m_file = ::fopen(filename.c_str(), "ae");//'e' for O_CLOEXEC

	if(NULL == m_file)
	{
		m_errno = errno;

		m_filesize = 0;
	}
	else
	{
		m_errno = 0;

		fseek(m_file, 0L, 2);

		m_filesize = ftell(m_file);

		::setbuffer(m_file, m_buffer, k_write_buffer_size);
	}

	return m_errno;
}

ssize_t WriteFile::write(const std::string& in)
{
	return write(in.c_str(), in.size());
}

ssize_t WriteFile::write(const char* inbuf, size_t inlen)
{
	if(NULL == m_file || NULL == inbuf || 0 == inlen)
	{
		return -1;
	}

	size_t index = 0;

	size_t resend = 0;

	do
	{
#ifdef _FWRITE_UNLOCKED_
		size_t size = ::fwrite_unlocked(inbuf + resend, 1, inlen - resend, m_file);
#else
		size_t size = ::fwrite(inbuf + resend, 1, inlen - resend, m_file);
#endif

		if(0 == size)
		{
			m_errno = ferror(m_file);

			reset(m_filename);

			return -2;
		}

		resend += size;
		m_filesize += size;
		m_writesize += size;

		if(0 == ++index % 10)
		{
			sleep_ms(1);
		}

	}while(inlen - resend > 0);

	return resend;
}

