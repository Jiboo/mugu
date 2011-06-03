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

#include <iostream>

namespace mugu
{

#ifndef NDEBUG

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

