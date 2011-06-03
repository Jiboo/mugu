/*
 * random.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#include "mugu/random.hpp"

namespace mugu
{
	
void random_widget::draw(cairo_t* pContext)
{
	//margin
	cairo_set_source_rgb(pContext, 1, 0, 0);
	cairo_rectangle(pContext, this->get_marginbox_offset_left(), this->get_marginbox_offset_top(), this->get_marginbox_width(), this->get_marginbox_height());
	cairo_fill(pContext);

	//border
	cairo_set_source_rgb(pContext, 0, 1, 0);
	cairo_rectangle(pContext, this->get_borderbox_offset_left(), this->get_borderbox_offset_top(), this->get_borderbox_width(), this->get_borderbox_height());
	cairo_fill(pContext);

	// padding
	cairo_set_source_rgb(pContext, 0, 0, 1);
	cairo_rectangle(pContext, this->get_paddingbox_offset_left(), this->get_paddingbox_offset_top(), this->get_paddingbox_width(), this->get_paddingbox_height());
	cairo_fill(pContext);

	// content
	cairo_set_source_rgb(pContext, 1, 1, 1);
	cairo_rectangle(pContext, this->get_contentbox_offset_left(), this->get_contentbox_offset_top(), this->get_contentbox_width(), this->get_contentbox_height());
	cairo_fill(pContext);
}

} // namespace mugu

