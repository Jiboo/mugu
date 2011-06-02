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
#include <mutex>

#include <xcb/xcb_atom.h>
#include <cairo/cairo-xcb.h>

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
	
	cairo_surface_t *surface;
	cairo_surface_t *cache;
	
	std::mutex resizing;
	
public:
	//using tContainer::tContainer;

	dialog() : tContainer()
	{
		this->parent = nullptr;
	
		this->window = xcb_generate_id(context::connection());
		this->width = 150;
		this->height = 150;

		this->cache = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, this->get_marginbox_width(), this->get_marginbox_height());
		this->surface = cairo_xcb_surface_create(context::connection(), this->window, context::root_visualtype(), this->get_marginbox_width(), this->get_marginbox_height());
		
		uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
		uint32_t values[2] =
		{
			context::screen()->white_pixel,
			XCB_EVENT_MASK_EXPOSURE
				| XCB_EVENT_MASK_STRUCTURE_NOTIFY
		};

		xcb_create_window(context::connection(),
			XCB_COPY_FROM_PARENT,
			this->window,
			context::screen()->root,
			0, 0,
			150, 150,
			10,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			context::screen()->root_visual,
			mask, values);
	
		context::register_dialog(dynamic_cast<widget*>(this), this->window);
	}

	virtual ~dialog()
	{
		this->set_visible(false);
		xcb_destroy_window(context::connection(), this->window);
		cairo_surface_destroy(this->surface);
		cairo_surface_destroy(this->cache);
	}

public:
	virtual void set_visible(bool pVisible)
	{
		this->visible = pVisible;
		if(pVisible)
			xcb_map_window(context::connection(), this->window);
		else
			xcb_unmap_window(context::connection(), this->window);
		context::flush();
	}
	
	virtual void set_width(unsigned pWidth)
	{
		uint32_t temp = pWidth;
		xcb_configure_window(context::connection(), this->window, XCB_CONFIG_WINDOW_WIDTH, &temp);
		context::flush();
	}
	
	virtual void set_height(unsigned pHeight)
	{
		uint32_t temp = pHeight;
		xcb_configure_window(context::connection(), this->window, XCB_CONFIG_WINDOW_HEIGHT, &temp);
		context::flush();
	}
	
	virtual void set_size(unsigned pWidth, unsigned pHeight)
	{	
		uint32_t temp[2] = {pWidth, pHeight};
		xcb_configure_window(context::connection(), this->window, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, temp);
		context::flush();
	}
	
	virtual void invalidates(unsigned pLeft, unsigned pTop, unsigned pWidth, unsigned pHeight)
	{
		cairo_t *ctx = cairo_create(this->surface);
		cairo_set_source_surface(ctx, this->cache, 0, 0);
		cairo_rectangle(ctx, pLeft, pTop, pWidth, pHeight);
		cairo_fill(ctx);
		cairo_destroy(ctx);
	}
	
	virtual void refresh()
	{
		cairo_t *ctx = cairo_create(this->surface);
		cairo_set_source_surface(ctx, this->cache, 0, 0);
		cairo_paint(ctx);
		cairo_destroy(ctx);
	}
	
	virtual void redraw()
	{
		cairo_t *ctx = cairo_create(this->cache);
		this->draw(ctx);
		cairo_destroy(ctx);
		this->refresh();
	}
	
	virtual void layout()
	{
		tContainer::layout();
		this->redraw();
	}
	
	virtual void __configure_notify(unsigned pWidth, unsigned pHeight)
	{
		if(pWidth != this->width || pHeight != this->height)
		{
			this->width = pWidth;
			this->height = pHeight;
			
			cairo_xcb_surface_set_size(this->surface, this->get_marginbox_width(), this->get_marginbox_height());
			
			cairo_surface_destroy(this->cache);
			this->cache = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, this->get_marginbox_width(), this->get_marginbox_height());
			this->layout();
		}
	}

public:
	std::string &get_title() { return this->title; }
	void set_title(std::string pTitle)
	{
		this->title = pTitle;
		
		xcb_change_property(context::connection(), XCB_PROP_MODE_REPLACE,
			this->window, WM_NAME, STRING, 8, pTitle.size(), pTitle.c_str());
		context::flush();
	}
	
	void debug()
	{
		cairo_surface_t* png = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, this->get_marginbox_width(), this->get_marginbox_height());
		cairo_t* ctx = cairo_create(png);
		cairo_set_source_surface(ctx, this->cache, 0, 0);
		cairo_paint(ctx);
		cairo_surface_write_to_png(png, "cache.png");
		cairo_destroy(ctx);
		cairo_surface_destroy(png);
	}
};

} // namespace mugu

