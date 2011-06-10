/*
 * hbox.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include "mugu/flexgrid.hpp"

namespace mugu
{

class hbox : public flexgrid
{
public:
	hbox(container* pTarget, unsigned pCols)
		: flexgrid(pTarget, 1, pCols)
	{}

	virtual ~hbox() {}
};

} // namespace mugu
