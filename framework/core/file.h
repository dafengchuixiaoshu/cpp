/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-30 14:39
 **/

#ifndef _DUODUO_CORE_FILE_H_
#define _DUODUO_CORE_FILE_H_

#include "nocopyable.h"

namespace duoduo
{
	namespace core
	{
		class ReadFile : public NoCopyable
		{
			public:

				ReadFile(const std::string filename = "");

				~ReadFile() { close(); }

				int read(std::string& out);

				int reset(std::string filename);

				int ferrno() { return m_errno; }

				size_t filesize() { return m_filesize; }

            private:

                void close() { if(m_file >= 0) ::close(m_file); }

			private:

				int m_file;

				int m_errno;

				size_t m_filesize;
		};

		class WriteFile : public NoCopyable
		{
				static const int k_write_buffer_size = 64 * 1024 - 1;

			public:

				explicit WriteFile(const std::string filename = "");

				~WriteFile();

				int reset(std::string filename);

				void flush(uint64_t interval = 0);

				ssize_t write(const std::string& in);

				ssize_t write(const char* inbuf, size_t inlen);

			public:

				int ferrno() { return m_errno; }

				bool isok() { return NULL != m_file; }

				size_t filesize() { return m_filesize; }

				size_t writesize() { return m_writesize; }

				const std::string& filename() { return m_filename; }

			private:

				int m_errno;

				FILE* m_file;

				size_t m_filesize;

				size_t m_writesize;

				CTime m_flushinterval;

				std::string m_filename;

				char m_buffer[k_write_buffer_size + 1];
		};
	}
}

#endif //_DUODUO_CORE_FILE_H_

