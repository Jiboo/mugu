/*
 * dialogs.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include <iostream>

class widget
{
public:
	unsigned width;
	
	virtual void layout()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

class container : public virtual widget
{
public:
	virtual void layout()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

class grid : public container
{
public:
	virtual void layout()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

template<class tContainer>
class dialog : virtual public widget, public tContainer
{
public:
};

int main(int, const char**)
{
	dialog<grid> test;
	test.layout();
	return 0;
}

