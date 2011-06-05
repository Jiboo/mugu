/*
 * source_png.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

namespace mugu
{

class source_png : public source
{
public:
	cairo_surface_t *image;

	source_png(const char *pPath) { this->image = cairo_image_surface_create_from_png(pPath); }
	virtual ~source_png() { cairo_surface_destroy(this->image); }

	void select(cairo_t *pContext) { cairo_set_source_surface(pContext, this->image, 0, 0); }
};

} // namespace mugu
