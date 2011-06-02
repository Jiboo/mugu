/*
 * styles.hpp
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

enum align
{
	ALIGN_TOP,
	ALIGN_RIGHT,
	ALIGN_BOTTOM,
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_JUSTIFY
};

enum border_style
{
	BORDER_STYLE_NONE,
	BORDER_STYLE_DOTTED,
	BORDER_STYLE_DASHED,
	BORDER_STYLE_SOLID
};

enum font_style
{
	FONT_STYLE_NORMAL = CAIRO_FONT_SLANT_NORMAL,
	FONT_STYLE_ITALIC = CAIRO_FONT_SLANT_ITALIC,
	FONT_STYLE_OBLIQUE = CAIRO_FONT_SLANT_OBLIQUE
};

enum font_weight
{
	FONT_WEIGHT_NORMAL = CAIRO_FONT_WEIGHT_NORMAL,
	FONT_WEIGHT_BOLD = CAIRO_FONT_WEIGHT_BOLD
};

enum font_decoration
{
	FONT_DECORATION_NONE,
	FONT_DECORATION_UNDERLINE,
	FONT_DECORATION_OVERLINE,
	FONT_DECORATION_THROUGH
};

#define MUGU_STYLE_DIRECTIONS(pType, pName) \
	pType pName##_top; \
	pType pName##_right; \
	pType pName##_bottom; \
	pType pName##_left; \
	void set_##pName(pType pSize) \
	{ pName##_top = pSize; pName##_right = pSize; pName##_bottom = pSize; pName##_left = pSize; } \
	void set_##pName(pType pSizeTB, pType pSizeRL) \
	{ pName##_top = pSizeTB; pName##_right = pSizeRL; pName##_bottom = pSizeTB; pName##_left = pSizeRL; } \
	void set_##pName(pType pSizeT, pType pSizeRL, pType pSizeB) \
	{ pName##_top = pSizeT; pName##_right = pSizeRL; pName##_bottom = pSizeB; pName##_left = pSizeRL; } \
	void set_##pName(pType pSizeT, pType pSizeR, pType pSizeB, pType pSizeL) \
	{ pName##_top = pSizeT; pName##_right = pSizeR; pName##_bottom = pSizeB; pName##_left = pSizeL; }
	
#define MUGU_STYLE_SOURCE(pName) \
	protected: source* pName##_source; \
	public: void set_##pName##_rgba(double pR, double pG, double pB, double pA = 1) \
	{ delete this->pName##_source; this->pName##_source = new source_rgba(pR, pG, pB, pA); } \
	void set_##pName##_png(const char* pPath) \
	{ delete this->pName##_source; this->pName##_source = new source_png(pPath); } \
	void set_##pName##_gradient(double pX0, double pY0, double pX1, double pY1, std::initializer_list<gradient_color_stop> pStops) \
	{ delete this->pName##_source; this->pName##_source = new source_gradient(pX0, pY0, pX1, pY1, pStops); }
	
#define MUGU_STYLE_SOURCE_DIRECTIONS(pName) \
	MUGU_STYLE_SOURCE(pName##_top); \
	MUGU_STYLE_SOURCE(pName##_right); \
	MUGU_STYLE_SOURCE(pName##_bottom); \
	MUGU_STYLE_SOURCE(pName##_left); \
	public:void set_##pName##_rgba(double pR, double pG, double pB, double pA = 1) \
	{ \
		delete this->pName##_top_source; this->pName##_top_source = new source_rgba(pR, pG, pB, pA); \
		delete this->pName##_right_source; this->pName##_right_source = new source_rgba(pR, pG, pB, pA); \
		delete this->pName##_bottom_source; this->pName##_bottom_source = new source_rgba(pR, pG, pB, pA); \
		delete this->pName##_left_source; this->pName##_left_source = new source_rgba(pR, pG, pB, pA); \
	} \
	void set_##pName##_png(const char* pPath) \
	{ \
		delete this->pName##_top_source; this->pName##_top_source = new source_png(pPath); \
		delete this->pName##_right_source; this->pName##_right_source = new source_png(pPath); \
		delete this->pName##_bottom_source; this->pName##_bottom_source = new source_png(pPath); \
		delete this->pName##_left_source; this->pName##_left_source = new source_png(pPath); \
	} \
	void set_##pName##_gradient(double pX0, double pY0, double pX1, double pY1, std::initializer_list<gradient_color_stop> pStops) \
	{ \
		delete this->pName##_top_source; this->pName##_top_source = new source_gradient(pX0, pY0, pX1, pY1, pStops); \
		delete this->pName##_right_source; this->pName##_right_source = new source_gradient(pX0, pY0, pX1, pY1, pStops); \
		delete this->pName##_bottom_source; this->pName##_bottom_source = new source_gradient(pX0, pY0, pX1, pY1, pStops); \
		delete this->pName##_left_source; this->pName##_left_source = new source_gradient(pX0, pY0, pX1, pY1, pStops); \
	}

#define MUGU_STYLE_TEXT(pName) \
	double pName##_size; \
	MUGU_STYLE_SOURCE(pName); \
	font_style pName##_style; \
	font_weight pName##_weight; \
	char *pName##_font; \
	align pName##_halign; \
	align pName##_valign; \
	void select_##pName##_text_style(cairo_t* pContext) \
	{ \
		cairo_select_font_face(pContext, pName##_font, (cairo_font_slant_t)pName##_style, (cairo_font_weight_t)pName##_weight); \
		cairo_set_font_size(pContext, pName##_size); \
	}

} // namespace mugu

