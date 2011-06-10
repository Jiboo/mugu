/*
 * theme_mugu.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#include "mugu/theme_mugu.hpp"
#include "mugu/utils.hpp"

#include "mugu/dialog.hpp"
#include "mugu/button.hpp"
#include "mugu/label.hpp"

namespace mugu
{

void theme_mugu::draw(cairo_t* pContext, dialog*)
{
	utils::set_source(pContext, 62/255.);
	cairo_paint(pContext);
}

void theme_mugu::draw(cairo_t* pContext, button* pButton)
{
	double border_external, border_internal_0, border_internal_1, background_0, background_1, text, text_x, text_y, shadow;
	
	cairo_text_extents_t extents = pButton->get_text_extents();
	
	text_x = pButton->get_left() + (pButton->get_width() / 2.) - ((extents.width / 2.) + extents.x_bearing);
	text_y = pButton->get_top() + (pButton->get_height() / 2.) - ((extents.height / 2.) + extents.y_bearing);
	
	if(!pButton->is_enabled())
	{
		border_external = 48/255.;
		border_internal_0 = 82/255.;
		border_internal_1 = 67/255.;
		background_0 = 76/255.;
		background_1 = 65/255.;
		text = 118/255.;
		shadow = 51/255.;
	}
	else if(pButton->is_clicked())
	{
		border_external = 24/255.;
		border_internal_0 = 140/255.;
		border_internal_1 = 87/255.;
		background_0 = 118/255.;
		background_1 = 81/255.;
		text = 253/255.;
		shadow = 1/255.;
		text_x++;
		text_y++;
	}
	else
	{
		border_external = 24/255.;
		border_internal_0 = 108/255.;
		border_internal_1 = 68/255.;
		background_0 = 92/255.;
		background_1 = 62/255.;
		text = 253/255.;
		shadow = 1/255.;
	}

	{ //Border
		{ //External
			utils::set_source(pContext, border_external);
			cairo_rectangle(pContext, pButton->get_left(), pButton->get_top(), pButton->get_width(), pButton->get_height());
			cairo_fill(pContext);
		}
		{ //Internal
			signed t = pButton->get_top() + 1,
				l = pButton->get_left() + 1,
				w = pButton->get_width() - 2,
				h = pButton->get_height() - 2;
		
			cairo_pattern_t* gradient = cairo_pattern_create_linear(l, t, l, t + h);
			utils::add_stop(gradient, 0, border_internal_0);
			utils::add_stop(gradient, 1, border_internal_1);
			
			cairo_rectangle(pContext, l, t, w, h);
			cairo_set_source(pContext, gradient);
			cairo_fill(pContext);
			cairo_pattern_destroy(gradient);
		}
	}
	{ //Background
		signed t = pButton->get_top() + 2,
			l = pButton->get_left() + 2,
			w = pButton->get_width() - 4,
			h = pButton->get_height() - 4;
	
		cairo_pattern_t* gradient = cairo_pattern_create_linear(l, t, l, t + h);
		utils::add_stop(gradient, 0, background_0);
		utils::add_stop(gradient, 1, background_1);
		
		cairo_rectangle(pContext, l, t, w, h);
		cairo_set_source(pContext, gradient);
		cairo_fill(pContext);
		cairo_pattern_destroy(gradient);
	}
	{ //Text
		cairo_move_to(pContext, text_x, text_y + 1);
		utils::set_source(pContext, shadow);
		cairo_show_text(pContext, pButton->get_text().c_str());
	
		cairo_move_to(pContext, text_x, text_y);
		utils::set_source(pContext, text);
		cairo_show_text(pContext, pButton->get_text().c_str());
	}
}

void theme_mugu::draw(cairo_t* pContext, label* pLabel)
{
	double text, text_x, text_y, shadow;
	
	cairo_text_extents_t extents = pLabel->get_text_extents();
	
	text_x = pLabel->get_left() + (pLabel->get_width() / 2.) - ((extents.width / 2.) + extents.x_bearing);
	text_y = pLabel->get_top() + (pLabel->get_height() / 2.) - ((extents.height / 2.) + extents.y_bearing);
	
	if(!pLabel->is_enabled())
	{
		text = 118/255.;
		shadow = 51/255.;
	}
	else
	{
		text = 253/255.;
		shadow = 1/255.;
	}

	{ //Text
		cairo_move_to(pContext, text_x, text_y + 1);
		utils::set_source(pContext, shadow);
		cairo_show_text(pContext, pLabel->get_text().c_str());
	
		cairo_move_to(pContext, text_x, text_y);
		utils::set_source(pContext, text);
		cairo_show_text(pContext, pLabel->get_text().c_str());
	}
}

} // namespace mugu
