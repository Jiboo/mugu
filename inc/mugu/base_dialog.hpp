/*
 * base_dialog.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <string>
#include <xcb/xcb.h>

#include "mugu/event.hpp"
#include "mugu/clickable.hpp"
#include "mugu/container.hpp"

namespace mugu
{

class base_dialog : public virtual container
{
	friend void __close_final(base_dialog* pDialog);

public:	
	clickable* focused;
	
	std::string title;
	xcb_window_t window;
	
	cairo_surface_t *surface;
	cairo_surface_t *cache;
	
	event<> event_close;

public:
	base_dialog();

	virtual ~base_dialog();

public:
	virtual void refresh();
	virtual void redraw();
	virtual void invalidates(unsigned pLeft, unsigned pTop, unsigned pWidth, unsigned pHeight);
	
	virtual void set_width(unsigned pWidth);
	virtual void set_height(unsigned pHeight);
	virtual void set_visible(bool pVisible);
	
public:
	void redraw(widget *pWidget);
	void refresh(widget *pWidget);

	void __handle_button(unsigned pLeft, unsigned pTop, bool pClicked);
	void __configure_notify(unsigned pWidth, unsigned pHeight);
	void __handle_close_request();
	
	std::string &get_title() { return this->title; }
	void set_title(std::string pTitle);
	
protected:
	clickable* get_widget(container *pContainer, unsigned pLeft, unsigned pTop);
};

void __close_final(base_dialog* pDialog);

} // namespace mugu

