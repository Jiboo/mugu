/*
 * gio.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#include <mutex>
#include <iostream>

#include "mugu/gio.hpp"

#include "mugu/flexgrid.hpp"
#include "mugu/hboxf.hpp"
#include "mugu/dialog.hpp"
#include "mugu/label.hpp"
#include "mugu/button.hpp"

namespace mugu
{

void alert(std::string pTitle, std::string pMessage)
{
	dialog *box = new dialog(pTitle);

	box->add(new label(pMessage));

	button *ok = new button("OK");
	box->add(ok);

	ok->event_click.connect([box](unsigned, unsigned) { box->close(); });

	box->set_layout(new grid(box, 2, 1));
	box->adapt();
	box->set_visible(true);
}

int messagebox(std::string pTitle, std::string pMessage, std::vector<std::string> pButtons)
{
	std::mutex mu;
	int ret = -1;

	mu.lock();

	dialog *box = new dialog(pTitle);
	
	box->event_close.connect([&mu]
	{
		mu.unlock();
	});

	box->add(new label(pMessage));
	
	container *choices = new container();
	box->add(choices);
	
	int index = 0;
	for(std::string &text : pButtons)
	{
		button* but = new button(text);
		
		but->event_click.connect([&ret, index, box](unsigned, unsigned)
		{
			ret = index;
			box->close();
		});
		
		choices->add(but);
		index++;
	}
	
	choices->set_layout(new grid(choices, 1, pButtons.size()));
	box->set_layout(new grid(box, 2, 1));
	box->adapt();
	box->set_visible(true);
	
	mu.lock();
	return ret;
}

} // namespace mugu

