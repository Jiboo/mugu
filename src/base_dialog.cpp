/*
 * base_dialog.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include <xcb/xcb_atom.h>
#include <cairo/cairo-xcb.h>

#include "mugu/base_dialog.hpp"
#include "mugu/clickable.hpp"
#include "mugu/container.hpp"

namespace mugu
{

base_dialog::base_dialog()
	: focused(nullptr)
{
	this->parent = nullptr;
	this->root = dynamic_cast<base_dialog*>(this);

	this->window = xcb_generate_id(context::connection());
	this->width = 150;
	this->height = 150;
	
	this->cache = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, this->width, this->height);
	this->surface = cairo_xcb_surface_create(context::connection(), this->window, context::root_visualtype(), this->width, this->height);
	
	uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t values[2] =
	{
		context::screen()->white_pixel,
		XCB_EVENT_MASK_EXPOSURE
			| XCB_EVENT_MASK_STRUCTURE_NOTIFY
			| XCB_EVENT_MASK_BUTTON_PRESS
			| XCB_EVENT_MASK_BUTTON_RELEASE
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

	context::register_dialog(dynamic_cast<base_dialog*>(this), this->window);
}

base_dialog::~base_dialog()
{
	this->set_visible(false);
	xcb_destroy_window(context::connection(), this->window);
	cairo_surface_destroy(this->surface);
	cairo_surface_destroy(this->cache);
}

void base_dialog::refresh()
{
	cairo_t *ctx = cairo_create(this->surface);
	cairo_set_source_surface(ctx, this->cache, 0, 0);
	cairo_paint(ctx);
	cairo_destroy(ctx);
}

void base_dialog::redraw()
{
	cairo_t *ctx = cairo_create(this->cache);
	this->draw(ctx);
	cairo_destroy(ctx);
	this->refresh();
}

void base_dialog::redraw(widget *pWidget)
{
	cairo_t *ctx = cairo_create(this->cache);
	pWidget->draw(ctx);
	cairo_destroy(ctx);
	this->refresh(pWidget);
}

void base_dialog::refresh(widget *pWidget)
{
	cairo_t *ctx = cairo_create(this->surface);
	cairo_set_source_surface(ctx, this->cache, 0, 0);
	cairo_rectangle(ctx, pWidget->get_left(), pWidget->get_top(), pWidget->get_width(), pWidget->get_height());
	cairo_fill(ctx);
	cairo_destroy(ctx);
}

void base_dialog::invalidates(unsigned pLeft, unsigned pTop, unsigned pWidth, unsigned pHeight)
{
	cairo_t *ctx = cairo_create(this->surface);
	cairo_set_source_surface(ctx, this->cache, 0, 0);
	cairo_rectangle(ctx, pLeft, pTop, pWidth, pHeight);
	cairo_fill(ctx);
	cairo_destroy(ctx);
}

void base_dialog::set_width(unsigned pWidth)
{
	uint32_t temp = pWidth;
	xcb_configure_window(context::connection(), this->window, XCB_CONFIG_WINDOW_WIDTH, &temp);
	context::flush();
}

void base_dialog::set_height(unsigned pHeight)
{
	uint32_t temp = pHeight;
	xcb_configure_window(context::connection(), this->window, XCB_CONFIG_WINDOW_HEIGHT, &temp);
	context::flush();
}

void base_dialog::set_visible(bool pVisible)
{
	this->visible = pVisible;
	if(pVisible)
		xcb_map_window(context::connection(), this->window);
	else
		xcb_unmap_window(context::connection(), this->window);
	context::flush();
}

void base_dialog::set_title(std::string pTitle)
{
	this->title = pTitle;
	
	xcb_change_property(context::connection(), XCB_PROP_MODE_REPLACE,
		this->window, WM_NAME, STRING, 8, pTitle.size(), pTitle.c_str());
	context::flush();
}

void base_dialog::__handle_button(unsigned pLeft, unsigned pTop, bool pClicked)
{
	clickable* cli = get_widget(this, pLeft, pTop);
	
	if(!pClicked && cli != this->focused && this->focused != nullptr)
		this->focused->__click_final();
	
	if(cli != nullptr)
	{
		this->focused = cli;
		cli->__handle_button(pLeft, pTop, pClicked);
	}
}

void base_dialog::__configure_notify(unsigned pWidth, unsigned pHeight)
{
	if(pWidth != this->width || pHeight != this->height)
	{
		this->width = pWidth;
		this->height = pHeight;
		
		cairo_xcb_surface_set_size(this->surface, this->width, this->height);
		
		cairo_surface_destroy(this->cache);
		this->cache = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, this->width, this->height);
		this->layout();
	}
}

clickable* base_dialog::get_widget(container *pContainer, unsigned pLeft, unsigned pTop)
{
	for(widget* child : pContainer->children)
	{
		clickable *cli = dynamic_cast<clickable*>(child);
		if(cli)
		{
			if(cli->contains(pLeft, pTop))
				return cli;
		}
		else
		{
			container *con = dynamic_cast<container*>(child);
			if(con)
			{
				if(con->contains(pLeft, pTop))
					return this->get_widget(con, pLeft, pTop);
			}
		}
	}
	return nullptr;
}

} // namespace mugu
