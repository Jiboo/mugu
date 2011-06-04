/*
 * grid.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#pragma once

#include "mugu/container.hpp"
#include "mugu/defines.hpp"

namespace mugu
{

class grid : public virtual container
{
public:
	MUGU_PROP(, get, unsigned, rows);
	MUGU_PROP(, get, unsigned, cols);

public:
	grid() {}

	grid(unsigned pRows, unsigned pCols)
	{
		this->rows = pRows;
		this->cols = pCols;
	}

	grid(std::initializer_list<std::initializer_list<widget*>> pChildren)
	{
		this->rows = pChildren.size();
		this->cols = (*(pChildren.begin())).size();

		for(std::initializer_list<widget*> row : pChildren)
		{
			for(widget* col : row)
				this->add(col);
		}
	}

	virtual ~grid() {}

public:
	virtual void adapt();
	virtual void layout();
};

} // namespace mugu
