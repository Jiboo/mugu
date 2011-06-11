/*
 * flexgrid.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include <algorithm>

#include "mugu/flexgrid.hpp"
#include "mugu/container.hpp"

namespace mugu
{

void flexgrid::adapt(container* pTarget)
{
	auto children = pTarget->get_children();
	unsigned w = 0, h = 0, r, c;

	for(unsigned i = 0; i < children.size(); i++)
	{
		r = i / this->cols.size();
        c = i % this->cols.size();

		children[i]->adapt();

		cols[c] = std::max(cols[c], children[i]->get_width());
		rows[r] = std::max(rows[r], children[i]->get_height());
	}

	for(unsigned col : cols)
		w += col;

	for(unsigned row : rows)
		h += row;

	pTarget->set_width(w + (this->cols.size() - 1) * this->hgap);
	pTarget->set_height(h + (this->rows.size() - 1) * this->vgap);
	
	/*if(this->parent != nullptr)
		parent->layout();
	this->layout();*/
}

void flexgrid::layout(container* pTarget)
{
	auto children = pTarget->get_children();
	unsigned w = 0, h = 0, r, c;
	unsigned offset_left = pTarget->get_left();
	unsigned offset_top = pTarget->get_top();
	
	// balance
	for(unsigned &col : cols)
		w += col;
	for(unsigned &row : rows)
		h += row;
		
	signed diff_w = ((signed)pTarget->get_width() - (this->cols.size() - 1) * this->hgap) - (signed)w;
	signed diff_h = ((signed)pTarget->get_height() - (this->rows.size() - 1) * this->vgap) - (signed)h;
	
	if(diff_w)
	{
		if(diff_w > 0)
			this->cols[0] += diff_w % this->cols.size();
		else
			this->cols[0] -= diff_w % this->cols.size();
		for(unsigned &col : this->cols)
			col += diff_w / (signed)this->cols.size();
	}
	if(diff_h)
	{
		if(diff_h > 0)
			this->rows[0] += diff_h % this->rows.size();
		else
			this->rows[0] -= diff_h % this->rows.size();
		for(unsigned &row : this->rows)
			row += diff_h / (signed)this->rows.size();
	}
	// end balance

	for(unsigned i = 0; i < children.size(); i++)
	{
		widget* child = children[i];

		r = i / this->cols.size();
		c = i % this->cols.size();

		child->set_left(offset_left);
		child->set_top(offset_top);

		if(this->hfill)
			child->set_width(cols[c]);
		if(this->vfill)
			child->set_height(rows[r]);
			
		child->layout();
			
		if(c == (this->cols.size() - 1))
		{
			offset_left = pTarget->get_left();
			offset_top += this->rows[r] + this->vgap;
		}
		else
		{
			offset_left += this->cols[c] + this->hgap;
		}
	}
}

} // namespace mugu

