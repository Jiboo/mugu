/*
 * button.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <string>

#include "mugu/styles.hpp"
#include "mugu/clickable.hpp"

namespace mugu
{

class button : public clickable
{
protected:
	cairo_text_extents_t extents;

public:
	MUGU_PROP(, set, std::string, text);
	MUGU_STYLE_TEXT(text);
	
	MUGU_STYLE_SOURCE(background_clicked);
	MUGU_STYLE_SOURCE_DIRECTIONS(border_clicked);

public:
	button(std::string pText);
	virtual ~button();
	
public:
	
	virtual void draw(cairo_t* pContext);
};

} // namespace mugu
