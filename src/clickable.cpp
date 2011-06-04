/*
 * clickable.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include "mugu/clickable.hpp"

namespace mugu
{

void clickable::__handle_button(unsigned pWidth, unsigned pHeight, bool pClicked)
{
	if(pClicked)
	{
		this->clicked = true;
		this->redraw();
	}
	else
	{
		this->event_click.fire(pWidth, pHeight);
	}
}

void clickable::__click_final()
{
	this->clicked = false;
	this->redraw();
}

} // namespace mugu

