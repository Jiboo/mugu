/*
 * dialog.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include "mugu.hpp"

using namespace mugu;

int main(int, char**)
{
	srand(time(NULL));

	dialog* d1 = new dialog("tst/dialog");
	
	d1->add(new label("r1"));
	button *r1 = new button("r{g1");
	d1->add(r1);
	
	d1->add(new label("r2"));
	button *r2 = new button("r{g2");
	d1->add(r2);
	
	d1->add(new label("r3"));
	button *r3 = new button("r{g3");
	d1->add(r3);
	
	d1->add(new label("r4"));
	button *r4 = new button("r{g4");
	d1->add(r4);
	
	d1->set_layout(new flexgrid(4, 2));
	d1->set_visible(true);
	d1->adapt();
	
	d1->anim(&dialog::set_width, d1->get_width(), (unsigned)400, std::chrono::seconds(1));
	//r1->anim(&button::set_width, r1->get_width(), (unsigned)800, std::chrono::seconds(3));
	//d1->set_width(800);
	
	r1->event_click.connect([](unsigned, unsigned){ std::cout << "r1 clicked!" << std::endl; });
	
	d1->event_close.set_async(true);
	d1->event_close.connect([]()
	{
		if(messagebox("Quit", "Do you really wanna quit?", {"Yes", "No"}) == 1)
			throw event_stop();
	});
	
	d1->event_hotkey.connect([](wchar_t pKey, bool pCtrl, bool pAlt, bool pShift)
	{
		std::cout << "hotkey: " << (char)pKey << " " << pCtrl << " " << pAlt << " " << pShift << std::endl;
	});
	
	context::clean();
	return 0;
}

