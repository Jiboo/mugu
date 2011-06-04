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
#include "mugu/clickable.hpp"

namespace mugu
{

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

void container::__handle_button(unsigned pLeft, unsigned pTop, bool pClicked)
{
	clickable* cli = get_widget(this, pLeft, pTop);
	if(cli)
		cli->__handle_button(pLeft, pTop, pClicked);
}

clickable* container::get_widget(container *pContainer, unsigned pLeft, unsigned pTop)
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

