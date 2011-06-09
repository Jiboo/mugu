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
#include <cairo/cairo.h>
#include <fontconfig/fontconfig.h>

#include "mugu/theme.hpp"

namespace mugu
{

class base_dialog;

class context
{
protected:
	std::vector<std::thread*> garbages;
	std::map<xcb_window_t, base_dialog*> dialogs;
	
	xcb_connection_t *con;
	const xcb_screen_t *scr;
	const xcb_setup_t *set;
	
	theme* cur_theme;

public:
	context();
	~context();

public:
	void event_pump();

	static context& instance()
	{
		static context singleton;
		return singleton; 
	}
	
	static void set_theme(theme* pTheme)
	{
		delete instance().cur_theme;
		instance().cur_theme = pTheme;
	}
	
	static void clean();
	
	static void flush() { xcb_flush(instance().con); }
	
	static void recycle(std::thread* pGarbage) { instance().garbages.push_back(pGarbage); }
	static void register_dialog(base_dialog* pDialog, xcb_window_t pWindow) { instance().dialogs.insert({pWindow, pDialog}); }
	
	static xcb_connection_t *connection() { return instance().con; }
	static const xcb_screen_t *screen() { return instance().scr; }
	static const xcb_setup_t *setup() { return instance().set; }
	static xcb_visualtype_t *root_visualtype();
	
	static theme* get_theme() { return instance().cur_theme; }
};

} // namespace mugu

