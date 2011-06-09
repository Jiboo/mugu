/*
 * gio.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <string>
#include <vector>

namespace mugu
{

void alert(std::string pTitle, std::string pMessage);
int messagebox(std::string pTitle, std::string pMessage, std::vector<std::string> pButtons);

} // namespace mugu
