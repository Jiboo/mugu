/*
 * label.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <string>

#include "mugu/widget.hpp"

namespace mugu
{

class label : public widget
{
protected:
	cairo_text_extents_t extents;

public:
	MUGU_PROP(, get, std::string, text);

public:
	label(std::string pText);
	virtual ~label();
	
public:
	
	virtual void draw(cairo_t* pContext);
	
public:
	cairo_text_extents_t &get_text_extents() { return this->extents; }
};

} // namespace mugu
