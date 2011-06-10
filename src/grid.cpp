/*
 * grid.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#include "mugu/grid.hpp"
#include "mugu/container.hpp"

namespace mugu
{

void grid::adapt()
{
	auto children = target->get_children();
	unsigned max_width = 0, max_height = 0;

	for(widget* child : children)
	{
		child->adapt();

		max_width = std::max(max_width, child->get_width());
		max_height = std::max(max_height, child->get_height());
	}

	target->set_width((max_width * cols) + (this->cols - 1) * this->hgap);
	target->set_height((max_height * rows) + (this->rows - 1) * this->vgap);
	
	/*if(this->parent != nullptr)
		parent->layout();
	this->layout();*/
}

void grid::layout()
{
	auto children = target->get_children();
	unsigned max_width = (target->get_width() - (this->cols - 1) * this->hgap) / cols;
	unsigned max_height = (target->get_height() - (this->rows - 1) * this->vgap) / rows;

	unsigned offset_left = target->get_left();
	unsigned offset_top = target->get_top();

	unsigned col = 0;

	for(widget* child : children)
	{
		child->set_left(offset_left);
		child->set_top(offset_top);

		if(this->hfill)
			child->set_width(max_width);
		if(this->vfill)
			child->set_height(max_height);
			
		child->layout();

		if(++col >= this->cols)
		{
			offset_left = target->get_left();
			offset_top += max_height + this->vgap;
			col = 0;
		}
		else
		{
			offset_left += max_width + this->hgap;
		}
	}
}

} // namespace mugu

