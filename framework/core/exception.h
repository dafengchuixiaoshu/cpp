/**
 *Author: 丘安-刘千国
 *Created on: 2017-11-24 12:25
 **/

#ifndef _DUODUO_CORE_EXCEPTION_H_
#define _DUODUO_CORE_EXCEPTION_H_

#include <string>
#include <exception>
#include <execinfo.h>

namespace duoduo
{
	namespace core
	{
		class Exception : public std::exception
		{
			public:

				Exception(const std::string what)
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
					void* buffer[128];

					int nptrs = ::backtrace(buffer, 128);

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
}

#endif //_DUODUO_CORE_EXCEPTION_H_

