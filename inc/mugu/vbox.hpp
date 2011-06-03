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
	vbox(unsigned pRows)
		: flexgrid(pRows, 1)
	{}

	vbox(std::initializer_list<widget*> pChildren)
		: flexgrid(pChildren.size(), 1)
	{
		for(widget* row : pChildren)
			this->add(row);
	}

	virtual ~vbox() {}
};

} // namespace mugu
