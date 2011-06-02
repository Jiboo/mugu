/*
 * hboxf.hpp
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

class hboxf : public grid
{
public:
	hboxf(unsigned pCols) : grid(1, pCols) {}

	hboxf(std::initializer_list<widget*> pChildren) : grid({ pChildren }) {}

	virtual ~hboxf() {}
};

} // namespace mugu
