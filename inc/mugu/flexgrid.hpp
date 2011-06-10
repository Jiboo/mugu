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

#include "mugu/layout_algo.hpp"
#include "mugu/defines.hpp"

namespace mugu
{

class flexgrid : public layout_algo
{
protected:
	std::vector<unsigned> rows;
	std::vector<unsigned> cols;

public:

	flexgrid(container* pTarget, unsigned pRows, unsigned pCols)
		: layout_algo(pTarget), rows(pRows, 0), cols(pCols, 0) {}

	virtual ~flexgrid() {}

public:
	virtual void adapt();
	virtual void layout();

public:
	void set_rows(unsigned pRows) { this->rows.assign(pRows, 0); }
	void set_cols(unsigned pCols) { this->cols.assign(pCols, 0); }
};

} // namespace mugu

