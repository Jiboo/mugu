/*
 * container.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#include <iostream>
 
#include "mugu/container.hpp"

namespace mugu
{

void container::draw(cairo_t* pContext)
{
	this->background_source->select(pContext);
	cairo_rectangle(pContext, this->get_paddingbox_offset_left(), this->get_paddingbox_offset_top(), this->get_paddingbox_width(), this->get_paddingbox_height());
	cairo_fill(pContext);

	if(this->visible)
	{
		for(widget* child : children)
		{
			if(child->visible)
				child->draw(pContext);
		}
	}
}

} // namespace mugu

