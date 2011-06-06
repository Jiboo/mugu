/*
 * theme_mugu.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include "mugu/theme.hpp"

namespace mugu
{

class theme_mugu : public theme
{
public:
	virtual void draw(base_dialog* pDialog);
	virtual void draw(button* pButton);
};

} // namespace mugu
