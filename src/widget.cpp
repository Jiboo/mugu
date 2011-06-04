/*
 * widget.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include "mugu/widget.hpp"
#include "mugu/base_dialog.hpp"

namespace mugu
{

void widget::refresh()
{
	this->root->refresh(this);
}

void widget::redraw()
{
	this->root->redraw(this);
}

} // namespace mugu

