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

public:
	clickable()
		: clicked(false)
	{
		this->event_click.connect(std::bind(&clickable::on_click, this, std::placeholders::_1, std::placeholders::_2));
	}
	
	virtual ~clickable()
	{
	}

public:
	virtual void on_click(unsigned, unsigned) {}

	virtual void __handle_button(unsigned pWidth, unsigned pHeight, bool pClicked);
	virtual void __click_final();
};

} // namespace mugu

