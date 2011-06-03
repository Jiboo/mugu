/*
 * context.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <vector>
#include <map>
#include <thread>
#include <xcb/xcb.h>

namespace mugu
{

class container;

class context
{
protected:
	std::vector<std::thread*> garbages;
	std::map<xcb_window_t, container*> dialogs;
	
	xcb_connection_t *con;
	const xcb_screen_t *scr;
	const xcb_setup_t *set;

public:
	context()
	{
		this->con = xcb_connect(NULL, NULL);
		this->set = xcb_get_setup(this->con);
        xcb_screen_iterator_t iter = xcb_setup_roots_iterator(this->set);
        this->scr = iter.data;
        
        this->garbages.push_back(new std::thread(&context::event_pump, this));
	}
	
	~context()
	{
		xcb_disconnect(this->con);
	}

public:
	void event_pump();

	static context& instance ()
	{
		static context singleton;
		return singleton; 
	}
	
	static void clean()
	{
		for(std::thread *garbage : instance().garbages)
		{
			if(garbage->joinable())
				garbage->join();
			delete garbage;
		}
		instance().garbages.clear();
	}
	
	static void flush() { xcb_flush(instance().con); }
	
	static void recycle(std::thread* pGarbage) { instance().garbages.push_back(pGarbage); }
	static void register_dialog(container* pDialog, xcb_window_t pWindow) { instance().dialogs.insert({pWindow, pDialog}); }
	
	static xcb_connection_t *connection() { return instance().con; }
	static const xcb_screen_t *screen() { return instance().scr; }
	static const xcb_setup_t *setup() { return instance().set; }
	static xcb_visualtype_t *root_visualtype();
};

} // namespace mugu

