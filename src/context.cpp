/*
 * context.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include "mugu/context.hpp"
#include "mugu/base_dialog.hpp"

namespace mugu
{

context::context()
{
	this->con = xcb_connect(NULL, NULL);
	this->set = xcb_get_setup(this->con);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(this->set);
    this->scr = iter.data;
    
    this->garbages.push_back(new std::thread(&context::event_pump, this));
}

context::~context()
{
	xcb_disconnect(this->con);
	#ifndef NDEBUG
		cairo_debug_reset_static_data();
		FcFini();
	#endif
}

void context::event_pump()
{
	xcb_generic_event_t *gen_e;

	while((gen_e = xcb_wait_for_event(this->con)))
	{
		switch(gen_e->response_type & ~0x80)
		{
			case XCB_EXPOSE:
			{
				xcb_expose_event_t *e = (xcb_expose_event_t*)gen_e;
				this->dialogs[e->window]->invalidates(e->x, e->y, e->width, e->height);
			} break;

			case XCB_CONFIGURE_NOTIFY:
			{
				xcb_configure_notify_event_t *e = (xcb_configure_notify_event_t*)gen_e;
				this->dialogs[e->window]->__configure_notify(e->width, e->height);
			} break;
			
			case XCB_BUTTON_PRESS:
			{
				xcb_button_press_event_t *e = (xcb_button_press_event_t*)gen_e;
				this->dialogs[e->event]->__handle_button( e->event_x, e->event_y, true);
			} break;
			
			case XCB_BUTTON_RELEASE:
			{
				xcb_button_release_event_t *e = (xcb_button_release_event_t*)gen_e;
				this->dialogs[e->event]->__handle_button( e->event_x, e->event_y, false);
			} break;

			default:
			{
			} break;
		}
		free(gen_e);
	}
}

xcb_visualtype_t *context::root_visualtype()
{
	xcb_visualtype_t *visual_type = NULL;
	xcb_depth_iterator_t depth_iter;

	depth_iter = xcb_screen_allowed_depths_iterator(screen());

	for(;depth_iter.rem; xcb_depth_next(&depth_iter))
	{
		xcb_visualtype_iterator_t visual_iter;

		visual_iter = xcb_depth_visuals_iterator(depth_iter.data);
		for(;visual_iter.rem; xcb_visualtype_next(&visual_iter))
		{
			if(screen()->root_visual == visual_iter.data->visual_id)
			{
				visual_type = visual_iter.data;
				break;
			}
		}
	}

	return visual_type;
}

void context::clean()
{
	for(std::thread *garbage : instance().garbages)
	{
		if(garbage->joinable())
			garbage->join();
		delete garbage;
	}
	instance().garbages.clear();
}

} //namespace mugu

