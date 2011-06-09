/*
 * label.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include <cmath>
#include <iostream> 

#include "mugu/label.hpp"
#include "mugu/utils.hpp"

namespace mugu
{

label::label(std::string pText)
	: text(pText)
{
	this->extents = utils::get_text_extents(pText);
										//margin
	this->width = this->extents.width	+ (2*2);
	this->height = this->extents.height	+ (2*2);
}

label::~label()
{
}

void label::draw(cairo_t* pContext)
{
	context::get_theme()->draw(pContext, this);
}

} // namespace mugu
