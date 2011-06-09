/*
 * defines.hpp
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

#define MUGU_PROP(pQualifier, pGetter, pType, pName) \
	protected: pType pName; \
	public: inline pType pGetter##_##pName() const { return pName; } \
	inline pQualifier void set_##pName(const pType _##pName) { pName = _##pName; }

} // namespace mugu
