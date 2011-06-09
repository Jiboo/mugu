/*
 * dialog.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include "mugu/context.hpp"
#include "mugu/base_dialog.hpp"

namespace mugu
{

template<class tContainer>
class dialog : public tContainer, public base_dialog
{
protected:
	
	
public:
	//using tContainer::tContainer; //FIXME Waiting compiler support

	dialog() : tContainer(), base_dialog() {}

	virtual ~dialog(){}

public:
	virtual void draw(cairo_t* pContext)
	{
		context::get_theme()->draw(pContext, this);
		tContainer::draw(pContext);
	}
	
	virtual void layout()
	{
		tContainer::layout();
		this->redraw();
	}
};

} // namespace mugu

