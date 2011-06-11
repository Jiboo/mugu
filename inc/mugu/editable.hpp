/*
 * editable.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#define XK_MISCELLANY
#include <X11/keysymdef.h>

#include "mugu/defines.hpp"
#include "mugu/event.hpp"
#include "mugu/clickable.hpp"

namespace mugu
{

class editable : public clickable
{
public:
	event<wchar_t> event_key;

public:
	editable()
	{
		this->event_key.connect(std::bind(&editable::on_key, this, std::placeholders::_1));
	}
	virtual ~editable() {}

public:
	virtual void on_key(wchar_t) {}
	
	virtual void __handle_key(wchar_t pKey) { this->event_key.fire(std::bind(&editable::__key_final, this), pKey); }
	virtual void __key_final() {}
};

} // namespace mugu
