/*
 * button.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include <cmath>
#include <iostream> 

#include "mugu/button.hpp"
#include "mugu/utils.hpp"

namespace mugu
{

button::button(std::string pText)
	: text(pText)
{
	this->text_size = 8;
	this->text_style = FONT_STYLE_NORMAL;
	this->text_weight = FONT_WEIGHT_NORMAL;
	this->text_font = "Sans";
	this->text_source = new source_rgba(1, 1, 1, 1);
	
	this->extents = get_text_extents(std::bind(&button::select_text_style, this, std::placeholders::_1), pText);
	
	this->height = this->text_size;
	this->width = this->extents.width;
	
	this->halign = ALIGN_CENTER;
	this->valign = ALIGN_CENTER;
	
	this->set_padding(2, 6);
	this->set_border_size(2);
	
	this->background_source = new source_rgba(1, 0, 0, 1);
	this->background_clicked_source = new source_rgba(0.5, 0, 0, 1);
	
	this->border_top_source = new source_rgba(0, 1, 0, 1);
	this->border_right_source = new source_rgba(0, 1, 0, 1);
	this->border_bottom_source = new source_rgba(0, 1, 0, 1);
	this->border_left_source = new source_rgba(0, 1, 0, 1);
	
	this->border_clicked_top_source = new source_rgba(0, 0.5, 0, 1);
	this->border_clicked_right_source = new source_rgba(0, 0.5, 0, 1);
	this->border_clicked_bottom_source = new source_rgba(0, 0.5, 0, 1);
	this->border_clicked_left_source = new source_rgba(0, 0.5, 0, 1);
}

button::~button()
{
	delete this->text_source;

	delete this->background_source;
	delete this->background_clicked_source;

	delete this->border_top_source;
	delete this->border_right_source;
	delete this->border_bottom_source;
	delete this->border_left_source;

	delete this->border_clicked_top_source;
	delete this->border_clicked_right_source;
	delete this->border_clicked_bottom_source;
	delete this->border_clicked_left_source;
}

void button::draw(cairo_t* pContext)
{
	{ // Background
		if(this->clicked)
			this->background_clicked_source->select(pContext);
		else
			this->background_source->select(pContext);
		cairo_rectangle(pContext, this->get_paddingbox_offset_left(), this->get_paddingbox_offset_top(), this->get_paddingbox_width(), this->get_paddingbox_height());
		cairo_fill(pContext);
	}
	{ // Borders
		{ // Top
			if(this->clicked)
				this->border_clicked_top_source->select(pContext);
			else
				this->border_top_source->select(pContext);
			cairo_set_line_width(pContext, this->border_size_top);
			cairo_move_to(pContext,
				this->get_borderbox_offset_left(),
				this->get_borderbox_offset_top() + (this->border_size_top / 2.));
			cairo_line_to(pContext,
				this->get_borderbox_offset_left() + this->get_borderbox_width(),
				this->get_borderbox_offset_top() + (this->border_size_top / 2.));
			cairo_stroke(pContext);
		}
		{ // Right
			if(this->clicked)
				this->border_clicked_right_source->select(pContext);
			else
				this->border_right_source->select(pContext);
			cairo_set_line_width(pContext, this->border_size_right);
			cairo_move_to(pContext,
				this->get_borderbox_offset_left() + this->get_borderbox_width() - (this->border_size_right / 2.),
				this->get_borderbox_offset_top());
			cairo_line_to(pContext,
				this->get_borderbox_offset_left() + this->get_borderbox_width() - (this->border_size_right / 2.),
				this->get_borderbox_offset_top() + this->get_borderbox_height());
			cairo_stroke(pContext);
		}
		{ // Bottom
			if(this->clicked)
				this->border_clicked_bottom_source->select(pContext);
			else
				this->border_bottom_source->select(pContext);
			cairo_set_line_width(pContext, this->border_size_bottom);
			cairo_move_to(pContext,
				this->get_borderbox_offset_left() + this->get_borderbox_width(),
				this->get_borderbox_offset_top() + this->get_borderbox_height() - (this->border_size_bottom / 2.));
			cairo_line_to(pContext,
				this->get_borderbox_offset_left(),
				this->get_borderbox_offset_top() + this->get_borderbox_height() - (this->border_size_bottom / 2.));
			cairo_stroke(pContext);
		}
		{ // Left
			if(this->clicked)
				this->border_clicked_left_source->select(pContext);
			else
				this->border_left_source->select(pContext);
			cairo_set_line_width(pContext, this->border_size_left);
			cairo_move_to(pContext,
				this->get_borderbox_offset_left() + (this->border_size_bottom / 2.),
				this->get_borderbox_offset_top() + this->get_borderbox_height());
			cairo_line_to(pContext,
				this->get_borderbox_offset_left() + (this->border_size_bottom / 2.),
				this->get_borderbox_offset_top());
			cairo_stroke(pContext);
		}
	}
	{ // Text
		unsigned x, y;
		this->select_text_style(pContext);
		
		switch(this->halign)
		{
			case ALIGN_LEFT: x = this->get_contentbox_offset_left(); break;
			case ALIGN_RIGHT: x = this->get_contentbox_offset_left() + this->get_contentbox_width() - extents.width; break;
			case ALIGN_CENTER:
			default: x = this->get_contentbox_offset_left() + (this->get_contentbox_width() / 2) - (extents.width / 2); break;
		}
		
		switch(this->valign)
		{
			case ALIGN_TOP: y = this->get_contentbox_offset_top() - extents.y_bearing; break;
			case ALIGN_BOTTOM: y = this->get_contentbox_offset_top() + this->get_contentbox_height() - (this->text_size + extents.y_bearing); break;
			case ALIGN_CENTER:
			default: y = this->get_contentbox_offset_top() + (this->get_contentbox_height() / 2) - (extents.y_bearing / 2); break;
		}
		
		if(this->clicked) { x++; y++; }
		
		cairo_move_to(pContext, x, y);
		cairo_show_text(pContext, this->text.c_str());
	}
}

} // namespace mugu
