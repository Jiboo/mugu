/*
 * theme.hpp
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

class base_dialog;
class button;

class theme
{
public:
	virtual void draw(cairo_t* pContext, base_dialog* pDialog) = 0;
	virtual void draw(cairo_t* pContext, button* pButton) = 0;
};

} // namespace mugu
