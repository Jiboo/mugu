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
	hbox(unsigned pCols)
		: flexgrid(1, pCols)
	{}

	hbox(std::initializer_list<widget*> pChildren)
		: flexgrid({ pChildren })
	{}

	virtual ~hbox() {}
};

} // namespace mugu
