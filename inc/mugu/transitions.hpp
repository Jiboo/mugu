/*
 * transitions.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#pragma once
 
#include <cmath>

namespace mugu
{

namespace transitions
{

double linear(double pPos)
{
	return pPos;
}

double ease(double pPos)
{
	return (-cos(pPos * M_PI) / 2) + 0.5;
}

} // namespace transitions

} // namespace mugu

