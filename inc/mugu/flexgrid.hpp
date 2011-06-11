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

	flexgrid(unsigned pRows, unsigned pCols)
		: rows(pRows, 0), cols(pCols, 0) {}

	virtual ~flexgrid() {}

public:
	virtual void adapt(container* pTarget);
	virtual void layout(container* pTarget);
};

} // namespace mugu

