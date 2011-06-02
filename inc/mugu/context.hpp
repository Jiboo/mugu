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
#include <thread>
#include <xcb/xcb.h>

namespace mugu
{

class context
{
protected:
	std::vector<std::thread*> garbages;
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
	}
	
	~context()
	{
		xcb_disconnect(this->con);
	}

public:
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
	static xcb_connection_t *connection() { return instance().con; }
	static const xcb_screen_t *screen() { return instance().scr; }
	static const xcb_setup_t *setup() { return instance().set; }
};

} // namespace mugu

