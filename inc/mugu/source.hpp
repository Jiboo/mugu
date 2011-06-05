/*
 * source.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <cairo/cairo.h>

namespace mugu
{

class widget;

class source
{
public:
	virtual ~source() {}
	virtual void select(cairo_t* pContext) = 0;
};

} // namespace mugu
