/*
 * utils.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <string>
#include <functional>
#include <cairo/cairo.h>

namespace mugu
{

namespace utils
{

cairo_text_extents_t get_text_extents(std::string &pString);
void init_context(cairo_t* pContext);

inline void set_source(cairo_t* pContext, double pGrayscale)
{
	cairo_set_source_rgb(pContext, pGrayscale, pGrayscale, pGrayscale);
}

inline void set_source(cairo_t* pContext, double pGrayscale, double pAlpha)
{
	cairo_set_source_rgba(pContext, pGrayscale, pGrayscale, pGrayscale, pAlpha);
}

inline void add_stop(cairo_pattern_t* pPattern, double pOffset, double pGrayscale)
{
	cairo_pattern_add_color_stop_rgb(pPattern, pOffset, pGrayscale, pGrayscale, pGrayscale);
}

inline void add_stop(cairo_pattern_t* pPattern, double pOffset, double pGrayscale, double pAlpha)
{
	cairo_pattern_add_color_stop_rgba(pPattern, pOffset, pGrayscale, pGrayscale, pGrayscale, pAlpha);
}

} // namespace utils

} // namespace mugu
