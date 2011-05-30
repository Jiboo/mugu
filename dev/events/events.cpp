/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#include <unistd.h>

#include "event.hpp"

int main(int,char**)
{
	event<> e111([]
	{
		std::cout << "e111 final" << std::endl;
	});

	e111.connect([]
	{
		std::cout << "e111 callback" << std::endl;
	});

	e111.connect([]
	{
		std::cout << "e111 callback" << std::endl;
	});

	event<> e11([&e111]
	{
		std::cout << "e11 final" << std::endl;
		e111.fire();
	});

	e11.connect([]
	{
		std::cout << "e11 callback" << std::endl;
	});

	e11.connect([]
	{
		std::cout << "e11 callback" << std::endl;
	});

	event<> e1([&e11]
	{
		std::cout << "e1 final" << std::endl;
		e11.fire();
	});

	e1.connect([]
	{
		std::cout << "e1 callback, sleeping" << std::endl;
		sleep(5);
	});

	e1.connect([]
	{
		std::cout << "e1 callback" << std::endl;
	});

	e1.async = true;
	e1.fire();

	e11.fire();

	return 0;
}

