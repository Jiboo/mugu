/*
 * source_rgba.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include "mugu/source.hpp"

namespace mugu
{

class source_rgba : public source
{
public:
	double r, g, b, a;

	source_rgba(double pR = 0, double pG = 0, double pB = 0, double pA = 1) : r(pR), g(pG), b(pB), a(pA) {}
	virtual ~source_rgba() {};

	void select(cairo_t *pContext) { cairo_set_source_rgba(pContext, this->r, this->g, this->b, this->a); }
};

} // namespace mugu
