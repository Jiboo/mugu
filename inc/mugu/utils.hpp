/*
 * utils.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <string>
#include <functional>
#include <cairo/cairo.h>

namespace mugu
{

cairo_text_extents_t get_text_extents(std::function<void(cairo_t*)> pSelect, std::string &pString);

} // namespace mugu
