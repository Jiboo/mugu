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

#include "mugu/layout_algo.hpp"
#include "mugu/defines.hpp"

namespace mugu
{

class grid : public layout_algo
{
public:
	MUGU_PROP(, get, unsigned, rows);
	MUGU_PROP(, get, unsigned, cols);

public:
	grid(unsigned pRows, unsigned pCols)
	{
		this->rows = pRows;
		this->cols = pCols;
	}

	virtual ~grid() {}

public:
	virtual void adapt(container* pTarget);
	virtual void layout(container* pTarget);
};

} // namespace mugu
