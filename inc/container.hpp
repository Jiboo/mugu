/*
 * container.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include <vector>

#include "widget.hpp"

namespace mugu
{

class container : public widget
{
protected:
	std::vector<widget*> children;
	
public:
	MUGU_PROP_SET(, unsigned, hgap);
	MUGU_PROP_SET(, unsigned, vgap);

	MUGU_PROP_HAS(, unsigned, hfill);
	MUGU_PROP_HAS(, unsigned, vfill);

public:
	container()
	{
		this->hgap = 1;
		this->vgap = 1;
		this->hfill = true;
		this->vfill = true;
	}

	virtual ~container()
	{
		for(widget* child : children)
			delete child;
	}

public:
	virtual void draw(cairo_t* pContext);

public:
	void add(widget* pChild)
	{
		pChild->parent = this;
		this->children.push_back(pChild);
	}
};

void container::draw(cairo_t* pContext)
{
	if(this->visible)
	{
		for(widget* child : children)
		{
			if(child->visible)
				child->draw(pContext);
		}
	}
}

} // namespace mugu

