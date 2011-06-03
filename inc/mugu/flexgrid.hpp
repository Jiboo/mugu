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

#include <vector>
#include <algorithm>

#include "mugu/container.hpp"
#include "mugu/defines.hpp"

namespace mugu
{

class flexgrid : public container
{
protected:
	std::vector<unsigned> rows;
	std::vector<unsigned> cols;

public:
	flexgrid(unsigned pRows, unsigned pCols)
		: rows(pRows, 0), cols(pCols, 0)
	{
	}

	flexgrid(std::initializer_list<std::initializer_list<widget*>> pChildren)
	{
		this->rows.assign(pChildren.size(), 0);
		this->cols.assign((*(pChildren.begin())).size(), 0);

		for(std::initializer_list<widget*> row : pChildren)
		{
			for(widget* col : row)
				this->add(col);
		}
	}

	virtual ~flexgrid() {}

public:
	virtual void adapt();
	virtual void layout();
};

} // namespace mugu

