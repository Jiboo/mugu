/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#include "anims.hpp"

std::vector<std::thread*> context::garbages;

int main(int,char**)
{
	context ctx;

	dialog test(ctx.connection);
	
	anim(&test, &dialog::set_width, 500, 200, std::chrono::seconds(3));
	std::this_thread::sleep_for(std::chrono::seconds(3));
	anim(&test, &dialog::set_width, 200, 500, std::chrono::seconds(3));
}

