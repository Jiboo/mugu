/*
 * dialog.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <string>

#include <xcb/xcb_atom.h>

#include "mugu/defines.hpp"
#include "mugu/context.hpp"
#include "mugu/widget.hpp"

namespace mugu
{

template<class tContainer>
class dialog : public tContainer, public virtual widget
{
protected:
	std::string title;
	xcb_window_t window;
	
public:
	dialog()
	{
		this->window = xcb_generate_id(context::connection());

		xcb_create_window(context::connection(),
			XCB_COPY_FROM_PARENT,
			this->window,
			context::screen()->root,
			0, 0,
			150, 150,
			10,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			context::screen()->root_visual,
			0, NULL);
	}

	virtual ~dialog()
	{
		this->set_visible(false);
		xcb_destroy_window(context::connection(), this->window);
	}

public:
	virtual void set_visible(bool pVisible)
	{
		this->visible = pVisible;
		if(pVisible)
			xcb_map_window(context::connection(), this->window);
		else
			xcb_unmap_window(context::connection(), this->window);
	}
	
	virtual void set_width(unsigned pWidth)
	{
		uint32_t temp = pWidth;
		xcb_configure_window(context::connection(), this->window, XCB_CONFIG_WINDOW_WIDTH, &temp);
	}
	
	virtual void set_height(unsigned pHeight)
	{
		uint32_t temp = pHeight;
		xcb_configure_window(context::connection(), this->window, XCB_CONFIG_WINDOW_HEIGHT, &temp);
	}
	
	virtual void set_size(unsigned pWidth, unsigned pHeight)
	{
		uint32_t temp[2] = {pWidth, pHeight};
		xcb_configure_window(context::connection(), this->window, XCB_CONFIG_WINDOW_HEIGHT, temp);
	}

public:
	std::string &get_title() { return this->title; }
	void set_title(std::string pTitle)
	{
		this->title = pTitle;
		
		xcb_change_property(context::connection(), XCB_PROP_MODE_REPLACE,
			this->win, WM_NAME, STRING, 8, pTitle.size(), pTitle.length());
	}
};

} // namespace mugu

