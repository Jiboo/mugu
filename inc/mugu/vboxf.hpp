/*
 * vboxf.hpp
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

class vboxf : public grid
{
public:
	vboxf(unsigned pRows) : grid(pRows, 1) {}

	vboxf(std::initializer_list<widget*> pChildren)
		: grid(0, 0)
	{
		this->rows = pChildren.size();
		this->cols = 1;

		for(widget* row : pChildren)
			this->add(row);
	}

	virtual ~vboxf() {}
};

} // namespace mugu
