/*
 * context.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#include <iostream>

class context
{
public:
	unsigned test;

	context()
	{
		test = 42;
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	~context()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	static context& instance ()
	{
		static context singleton;
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		return singleton; 
	}
	
	static unsigned get_test()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		return instance().test;
	}
};

int main(int, char**)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	
	context lol;

	std::cout << lol.get_test() << std::endl;

	return 0;
}
