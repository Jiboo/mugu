/*
 * debug.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <execinfo.h>
#include <cxxabi.h>
#include <iostream>

namespace mugu
{

#ifndef NDEBUG
	// https://idlebox.net/2008/0901-stacktrace-demangled/
	static inline void __print_stacktrace()
	{
		void* addrlist[32];
		int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));
		if(addrlen == 0)
		{
		    std::cerr << "<empty, possibly corrupt>" << std::endl;
		    return;
		}
		char** symbollist = backtrace_symbols(addrlist, addrlen);
		size_t funcnamesize = 512;
		char* funcname = (char*)malloc(funcnamesize);
		for(int i = 1; i < addrlen; i++)
		{
		    char *begin_name = 0, *begin_offset = 0, *end_offset = 0;
		    for(char *p = symbollist[i]; *p; ++p)
		    {
		        if (*p == '(')
		            begin_name = p;
		        else if (*p == '+')
		            begin_offset = p;
		        else if (*p == ')' && begin_offset) {
		            end_offset = p;
		            break;
		        }
		    }
		    if (begin_name && begin_offset && end_offset && begin_name < begin_offset)
		    {
		        *begin_name++ = '\0';
		        *begin_offset++ = '\0';
		        *end_offset = '\0';

		        int status;
		        char* ret = abi::__cxa_demangle(begin_name, funcname, &funcnamesize, &status);
		        if (status == 0) {
		            funcname = ret;
		            std::cerr << "  " <<  funcname << std::endl;
		        }
		        else
		            std::cerr << "  " << begin_name << "()" << std::endl;
		    }
		    else
		    	std::cerr << "  " <<  symbollist[i] << std::endl;
		}
		free(funcname);
		free(symbollist);
	}

	#define MUGU_ASSERT(pCond, pError) \
		if(!pCond) \
		{ \
			std::cerr << "Fatal assertion failed in " << __PRETTY_FUNCTION__ << " (" << __FILE__ << ":" << __LINE__ << ") : " << pError << ". Stack trace:" << std::endl; \
			__print_stacktrace(); \
			exit(1); \
		}

	#define MUGU_WARNING(pCond, pError) \
		if(!pCond) \
		{ \
			std::cerr << "Assertion failed in " << __PRETTY_FUNCTION__ << " (" << __FILE__ << ":" << __LINE__ << ") : " << pError << ". Stack trace:" << std::endl; \
			__print_stacktrace(); \
		}

	#define MUGU_LOG(pMessage) std::cerr << "Log from " << __PRETTY_FUNCTION__ << " (" << __FILE__ << ":" << __LINE__ << ") : " << pMessage << std::endl;

	#define MUGU_FATAL(pError) \
		std::cerr << "Fatal error in " << __PRETTY_FUNCTION__ << " (" << __FILE__ << ":" << __LINE__ << ") : " << pError << ". Stack trace:" << std::endl; \
		__print_stacktrace(); \
		exit(1); \

#else

	#define MUGU_ASSERT(pCond, pError)
	#define MUGU_WARNING(pCond, pError)
	#define MUGU_LOG(pMessage)
	#define MUGU_FATAL(pError)

#endif

} // namespace mugu
