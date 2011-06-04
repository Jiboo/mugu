/*
 * base_dialog.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include "mugu/widget.hpp"
#include "mugu/container.hpp"

namespace mugu
{

class base_dialog : public virtual container
{
public:	
	widget* focused;

public:
	virtual ~base_dialog()
	{
	}

public:
	virtual void __configure_notify(unsigned, unsigned) {}
	virtual void __handle_button(unsigned pLeft, unsigned pTop, bool pClicked);
	
	virtual void redraw(widget *) {}
	virtual void refresh(widget *) {}

protected:
	clickable* get_widget(container *pContainer, unsigned pLeft, unsigned pTop);
};

} // namespace mugu
