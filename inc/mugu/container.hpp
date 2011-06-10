/*
 * container.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <vector>
#include <cairo/cairo.h>

#include "mugu/widget.hpp"

namespace mugu
{

class layout_algo;

class container : public widget
{
	friend class dialog;

protected:
	std::vector<widget*> children;

	layout_algo *cur_layout;

public:
	container() {}

	virtual ~container();

public:
	virtual void draw(cairo_t* pContext);
	virtual void adapt();
	virtual void layout();

public:
	void add(widget* pChild)
	{
		pChild->parent = this;
		pChild->root = this->root;
		
		this->children.push_back(pChild);
	}
	
	void set_layout(layout_algo* pLayout) { this->cur_layout = pLayout; }
	
	std::vector<widget*> &get_children() { return this->children; };
};

} // namespace mugu

