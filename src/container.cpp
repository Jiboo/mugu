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
#include "mugu/layout_algo.hpp"

namespace mugu
{

container::~container()
{
	for(widget* child : children)
		delete child;
	delete this->cur_layout; // FIXME: Containers can't share layouts because of this
}

void container::draw(cairo_t* pContext)
{
	if(this->visible)
	{
		for(widget* child : children)
		{
			if(child->visible)
				child->draw(pContext);
		}
	}
}

void container::adapt()
{
	this->cur_layout->adapt(this);
}

void container::layout()
{
	this->cur_layout->layout(this);
}

} // namespace mugu

