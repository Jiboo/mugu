/*
 * clickable.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include "mugu/event.hpp"
#include "mugu/widget.hpp"

namespace mugu
{

class clickable : public widget
{
public:
	MUGU_PROP(, is, bool, clicked);
	event<unsigned, unsigned> event_click;
	
	clickable(std::function<void(void)> pFinal)
		: event_click(pFinal)
	{
		this->event_click.connect(std::bind(&clickable::on_click, this, std::placeholders::_1, std::placeholders::_2));
	}
	
	virtual ~clickable()
	{
	}
	
	virtual void on_click(unsigned, unsigned) {}
};

} // namespace mugu
