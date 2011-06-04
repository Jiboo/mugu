/*
 * utils.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#include <cstring>

#include "mugu/utils.hpp"

namespace mugu
{

cairo_text_extents_t get_text_extents(std::function<void(cairo_t*)> pSelect, std::string &pString)
{
	cairo_text_extents_t extents;
	
	cairo_surface_t* tmp = cairo_image_surface_create(CAIRO_FORMAT_A1, 1, 1);
	cairo_t* ctx = cairo_create(tmp);
	
	pSelect(ctx);

	cairo_text_extents(ctx, pString.c_str(), &extents);

	cairo_destroy(ctx);
	cairo_surface_destroy(tmp);
	
	return extents;
}

} // namespace mugu
