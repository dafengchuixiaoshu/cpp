/*
Author: coderqiuan@163.com
Created on: 2016-12-16 14:42
*/

#pragma once

#include "util.h"
#include "time.h"

namespace qiuan
{
    class CReadFile
    {
        private:

            CReadFile(const CReadFile&);

            const CReadFile& operator=(const CReadFile&);

        public:

            explicit CReadFile(const std::string filename = "");

            ~CReadFile();

            int read(std::string& out);

            int reset(std::string filename);

            int ferrno() { return m_errno; }

            size_t filesize() { return m_filesize; }

        private:

            int m_file;

            int m_errno;

            size_t m_filesize;
    };

    class CWriteFile
    {
        private:

            CWriteFile(const CWriteFile&);

            const CWriteFile& operator=(const CWriteFile&);

            static const int k_write_buffer_size = 64 * 1024 - 1;

        public:

            explicit CWriteFile(const std::string filename = "");

            ~CWriteFile();

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

