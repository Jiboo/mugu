/*
 * layout_algo.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include "mugu/defines.hpp"

namespace mugu
{

class container;

class layout_algo
{
public:
	container* target;
	
	MUGU_PROP(, get, unsigned, hgap);
	MUGU_PROP(, get, unsigned, vgap);

	MUGU_PROP(, has, unsigned, hfill);
	MUGU_PROP(, has, unsigned, vfill);

	layout_algo(container* pTarget)
	{
		this->target = pTarget;
		this->hgap = 1;
		this->vgap = 1;
		this->hfill = true;
		this->vfill = true;
	}
	virtual ~layout_algo() {}

	virtual void adapt() = 0;
	virtual void layout() = 0;
};

} // namespace mugu
