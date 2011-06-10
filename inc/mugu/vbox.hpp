/*
 * vbox.hpp
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

class vbox : public flexgrid
{
public:
	vbox(container* pTarget, unsigned pRows)
		: flexgrid(pTarget, pRows, 1)
	{}

	virtual ~vbox() {}
};

} // namespace mugu
