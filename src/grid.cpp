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

namespace mugu
{

grid::grid(std::initializer_list<std::initializer_list<widget*>> pChildren)
{
	this->rows = pChildren.size();
	this->cols = (*(pChildren.begin())).size();

	for(std::initializer_list<widget*> row : pChildren)
	{
		for(widget* col : row)
			this->add(col);
	}
}

void grid::adapt()
{
	unsigned max_width = 0, max_height = 0;

	for(widget* child : this->children)
	{
		child->adapt();

		max_width = std::max(max_width, child->get_marginbox_width());
		max_height = std::max(max_height, child->get_marginbox_height());
	}

	this->set_size((max_width * cols) + (this->cols - 1) * this->hgap, (max_height * rows) + (this->rows - 1) * this->vgap);
	
	if(this->parent != nullptr)
		parent->layout();
	this->layout();
}

void grid::layout()
{
	unsigned max_width = (this->width - (this->cols - 1) * this->hgap) / cols;
	unsigned max_height = (this->height - (this->rows - 1) * this->vgap) / rows;

	unsigned offset_left = this->get_contentbox_offset_left();
	unsigned offset_top = this->get_contentbox_offset_top();

	unsigned col = 0;

	for(widget* child : this->children)
	{
		child->set_left(offset_left);
		child->set_top(offset_top);

		if(this->hfill)
			child->set_marginbox_width(max_width);
		if(this->vfill)
			child->set_marginbox_height(max_height);
			
		child->layout();

		if(++col >= this->cols)
		{
			offset_left = this->get_contentbox_offset_left();
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
