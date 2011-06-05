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

#include "mugu/container.hpp"
#include "mugu/defines.hpp"

namespace mugu
{

class flexgrid : public virtual container
{
protected:
	std::vector<unsigned> rows;
	std::vector<unsigned> cols;

public:
	flexgrid() {}

	flexgrid(unsigned pRows, unsigned pCols)
		: rows(pRows, 0), cols(pCols, 0)
	{
	}

	flexgrid(std::initializer_list<std::initializer_list<widget*>> pChildren);

	virtual ~flexgrid() {}

public:
	virtual void adapt();
	virtual void layout();

public:
	void set_rows(unsigned pRows) { this->rows.assign(pRows, 0); }
	void set_cols(unsigned pCols) { this->cols.assign(pCols, 0); }
};

} // namespace mugu

