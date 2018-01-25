/*
Author: coderqiuan@163.com
Created on: 2017-01-10 16:59
*/

#pragma once

#include <string>
#include <exception>
#include <execinfo.h>

namespace qiuan
{
    class Exception : public std::exception
    {
        public:

            explicit Exception(const char* what)
                : m_what(what)
            {
                trace();            
            }

            explicit Exception(const std::string& what)
                : m_what(what)
            {
                trace();
            }

            virtual ~Exception() throw()
            {

            }

            const char* what() const throw()
            {
                return m_what.c_str();
            }

            const std::string& stack() const throw()
            {
                return m_stack;
            }

        private:

            void trace()
            {
                static const int buflen = 1024 - 1;

                void* buffer[buflen + 1];

                int nptrs = ::backtrace(buffer, buflen);

                char** sbuf = ::backtrace_symbols(buffer, nptrs);

                if(NULL != sbuf)
                {
                    for (int index = 0; index < nptrs; ++index)
                    {
                        m_stack.append(sbuf[index]);

                        m_stack.push_back('\n');
                    }

                    free(sbuf);
                }
            }

        private:

            std::string m_what;

            std::string m_stack;
    };
}

