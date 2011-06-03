/*
 * button.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <string>

#include "mugu/clickable.hpp"

namespace mugu
{

class button : public clickable
{
public:
	MUGU_PROP(, set, std::string, text);
	
	
};

} // namespace mugu
