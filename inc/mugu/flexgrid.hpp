/*
 * grid.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#pragma once

#include <vector>
#include <algorithm>

#include "mugu/container.hpp"
#include "mugu/defines.hpp"

namespace mugu
{

class flexgrid : public container
{
protected:
	std::vector<unsigned> rows;
	std::vector<unsigned> cols;

public:
	flexgrid(unsigned pRows, unsigned pCols)
		: rows(pRows, 0), cols(pCols, 0)
	{
	}

	flexgrid(std::initializer_list<std::initializer_list<widget*>> pChildren)
	{
		this->rows.assign(pChildren.size(), 0);
		this->cols.assign((*(pChildren.begin())).size(), 0);

		for(std::initializer_list<widget*> row : pChildren)
		{
			for(widget* col : row)
				this->add(col);
		}
	}

	virtual ~flexgrid() {}

public:
	virtual void adapt();
	virtual void layout();
};

void flexgrid::adapt()
{
	unsigned w = 0, h = 0, r, c;

	for(unsigned i = 0; i < this->children.size(); i++)
	{
		r = i / this->cols.size();
        c = i % this->cols.size();

		children[i]->adapt();

		cols[c] = std::max(cols[c], children[i]->get_marginbox_width());
		rows[r] = std::max(rows[r], children[i]->get_marginbox_height());
	}

	for(unsigned col : cols)
		w += col;

	for(unsigned row : rows)
		h += row;

	this->set_size(w + (this->cols.size() - 1) * this->hgap, h + (this->rows.size() - 1) * this->vgap);

	if(this->parent != nullptr)
		parent->layout();
	this->layout();
}

void flexgrid::layout()
{
	unsigned w = 0, h = 0, r, c;
	unsigned offset_left = this->get_contentbox_offset_left();
	unsigned offset_top = this->get_contentbox_offset_top();
	
	// balance
	for(unsigned &col : cols)
		w += col;
	for(unsigned &row : rows)
		h += row;
		
	signed diff_w = ((signed)this->width - (this->cols.size() - 1) * this->hgap) - (signed)w;
	signed diff_h = ((signed)this->height - (this->rows.size() - 1) * this->vgap) - (signed)h;
	
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

	for(unsigned i = 0; i < this->children.size(); i++)
	{
		widget* child = this->children[i];

		r = i / this->cols.size();
		c = i % this->cols.size();

		child->set_left(offset_left);
		child->set_top(offset_top);

		if(this->hfill)
			child->set_marginbox_width(cols[c]);
		if(this->vfill)
			child->set_marginbox_height(rows[r]);
			
		child->layout();
			
		if(c == (this->cols.size() - 1))
		{
			offset_left = this->get_contentbox_offset_left();
			offset_top += this->rows[r] + this->vgap;
		}
		else
		{
			offset_left += this->cols[c] + this->hgap;
		}
	}
}

} // namespace mugu

