/*
 * widget.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <chrono>
#include <functional>

#include <cairo/cairo.h>

#include "mugu/defines.hpp"
#include "mugu/styles.hpp"
#include "mugu/context.hpp"

namespace mugu
{

class widget
{
	friend class container;

protected:
	widget* parent;

public:
	MUGU_PROP(virtual, set, unsigned, width);
	MUGU_PROP(virtual, set, unsigned, height);
	MUGU_PROP(, set, unsigned, top);
	MUGU_PROP(, set, unsigned, left);

	MUGU_STYLE_DIRECTIONS(unsigned, border_size);
	MUGU_STYLE_DIRECTIONS(border_style, border_style);
	MUGU_STYLE_SOURCE_DIRECTIONS(border);

	MUGU_STYLE_DIRECTIONS(unsigned, margin);
	MUGU_STYLE_DIRECTIONS(unsigned, padding);

	MUGU_STYLE_SOURCE(background);

	MUGU_PROP(virtual, is, bool, visible);
	MUGU_PROP(, has, bool, enabled);
	MUGU_PROP(, has, bool, focus);

public:
	widget()
	{
		this->width = 0;
		this->height = 0;
		this->top = 0;
		this->left = 0;

		this->set_border_size(0);
		this->set_border_style(BORDER_STYLE_NONE);
		
		this->set_margin(0);
		this->set_padding(0);

		this->visible = true;
		this->enabled = true;
		this->focus = false;
	}
	
	virtual ~widget() {}

public:
	virtual void layout() {}
	virtual void adapt() {}
	virtual void draw(cairo_t*) {}
	
	virtual void set_size(unsigned pWidth, unsigned pHeight)
	{
		this->width = pWidth;
		this->height = pHeight;
	}

public:
	unsigned get_marginbox_offset_left() { return this->left; }
	unsigned get_marginbox_offset_top() { return this->top; }
	unsigned get_marginbox_width() { return this->get_borderbox_width() + this->margin_top + this->margin_bottom; }
	unsigned get_marginbox_height() { return this->get_borderbox_height() + this->margin_top + this->margin_bottom; }
	void set_marginbox_width(unsigned pWidth) { this->set_width(pWidth - this->margin_left - this->margin_right - this->border_size_left - this->border_size_right - this->padding_left - this->padding_right); }
	void set_marginbox_height(unsigned pHeight) { this->set_height(pHeight - this->margin_top - this->margin_bottom - this->border_size_top - this->border_size_bottom - this->padding_top - this->padding_bottom); }

	unsigned get_borderbox_offset_left() { return get_marginbox_offset_left() + this->margin_left; }
	unsigned get_borderbox_offset_top() { return get_marginbox_offset_top() + this->margin_top; }
	unsigned get_borderbox_width() { return this->get_paddingbox_width() + this->border_size_top + this->border_size_bottom; }
	unsigned get_borderbox_height() { return this->get_paddingbox_height() + this->border_size_top + this->border_size_bottom; }

	unsigned get_paddingbox_offset_left() { return get_borderbox_offset_left() +  this->border_size_left; }
	unsigned get_paddingbox_offset_top() { return get_borderbox_offset_top() + this->border_size_top; }
	unsigned get_paddingbox_width() { return get_contentbox_width() + this->padding_top + this->padding_bottom; }
	unsigned get_paddingbox_height() { return get_contentbox_height() + this->padding_top + this->padding_bottom; }

	unsigned get_contentbox_offset_left() { return get_paddingbox_offset_left() + this->padding_left; }
	unsigned get_contentbox_offset_top() { return get_paddingbox_offset_top() + this->padding_top; }
	unsigned get_contentbox_width() { return this->width; }
	unsigned get_contentbox_height() { return this->height; }
	void set_contentbox_width(unsigned pWidth) { this->set_width(pWidth); }
	void set_contentbox_height(unsigned pHeight) { this->set_height(pHeight); }

	bool contains(unsigned short pLeft, unsigned short pTop)
	{
		return 
			pLeft > this->left
				&&
			pLeft < (this->left + this->width)
				&&
			pTop > this->top
				&&
			pTop < (this->top + this->height);
	}

	bool overlaps(unsigned short pLeft, unsigned short pTop, unsigned short pWidth, unsigned short pHeight)
	{
		return
			this->left < (pLeft + pWidth)
				&&
			(this->left + this->width) > pLeft
				&&
			this->top < (pTop + pHeight)
				&&
			(this->top + this->height) > pTop;
	}
	
	template <typename tWidgetType, typename tDataType, typename tPassedType, class Rep, class Period>
	void anim(void(tWidgetType::*pFunc)(tDataType), tPassedType pOrigin, tPassedType pTarget, std::chrono::duration<Rep, Period> pDuration, std::function<double (double)> pTransition = &transitions::ease);
};

template <typename tWidgetType, typename tDataType, typename tPassedType, class Rep, class Period>
void widget::anim(void(tWidgetType::*pFunc)(tDataType), tPassedType pOrigin, tPassedType pTarget, std::chrono::duration<Rep, Period> pDuration, std::function<double (double)> pTransition)
{
	context::recycle(new std::thread([this, pFunc, pOrigin, pTarget, pDuration, pTransition]
	{
		auto start = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::now();
	
		std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(pDuration);
	
		while(time < (start + duration))
		{
			std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(time - start);		
			(this->*(pFunc))(pOrigin + (pTarget - pOrigin) * pTransition((double)diff.count() / (double)duration.count()));
		
			time = std::chrono::system_clock::now();
			std::this_thread::sleep_for(std::chrono::milliseconds(20)); // 50 fps
		}
	
		(this->*(pFunc))(pTarget);
	}));
}

} // namespace mugu

