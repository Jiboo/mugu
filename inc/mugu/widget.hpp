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
#include <iostream>

#include <cairo/cairo.h>

#include "mugu/defines.hpp"
#include "mugu/styles.hpp"
#include "mugu/transitions.hpp"
#include "mugu/context.hpp"

namespace mugu
{

class base_dialog;

class widget
{
	friend class container;
	friend class source_gradient;

protected:
	widget* parent;
	base_dialog* root;
	
	unsigned width;
	unsigned height;

public:
	MUGU_PROP(, get, unsigned, top);
	MUGU_PROP(, get, unsigned, left);
	MUGU_PROP(, get, align, halign);
	MUGU_PROP(, get, align, valign);

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
	widget();
	
	virtual ~widget() {}

protected:
	virtual void set_width(unsigned pWidth)
	{
		this->width = pWidth;
	}
	
	virtual void set_height(unsigned pHeight)
	{
		this->height = pHeight;
	}

public:
	virtual void layout() {}
	virtual void adapt() {}

	virtual void refresh();
	virtual void redraw();
	
	virtual void draw(cairo_t*) {}
	virtual void invalidates(unsigned, unsigned, unsigned, unsigned) {}

public:
	unsigned get_marginbox_offset_left() { return this->left; }
	unsigned get_marginbox_offset_top() { return this->top; }
	unsigned get_marginbox_width() { return this->get_borderbox_width() + this->margin_left + this->margin_right; }
	unsigned get_marginbox_height() { return this->get_borderbox_height() + this->margin_top + this->margin_bottom; }
	void set_marginbox_width(unsigned pWidth) { this->set_width(pWidth - this->margin_left - this->margin_right - this->border_size_left - this->border_size_right - this->padding_left - this->padding_right); }
	void set_marginbox_height(unsigned pHeight) { this->set_height(pHeight - this->margin_top - this->margin_bottom - this->border_size_top - this->border_size_bottom - this->padding_top - this->padding_bottom); }

	unsigned get_borderbox_offset_left() { return get_marginbox_offset_left() + this->margin_left; }
	unsigned get_borderbox_offset_top() { return get_marginbox_offset_top() + this->margin_top; }
	unsigned get_borderbox_width() { return this->get_paddingbox_width() + this->border_size_left + this->border_size_right; }
	unsigned get_borderbox_height() { return this->get_paddingbox_height() + this->border_size_top + this->border_size_bottom; }

	unsigned get_paddingbox_offset_left() { return get_borderbox_offset_left() +  this->border_size_left; }
	unsigned get_paddingbox_offset_top() { return get_borderbox_offset_top() + this->border_size_top; }
	unsigned get_paddingbox_width() { return get_contentbox_width() + this->padding_left + this->padding_right; }
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
			pLeft > this->get_borderbox_offset_left()
				&&
			pLeft < (this->get_borderbox_offset_left() + get_borderbox_width())
				&&
			pTop > this->get_borderbox_offset_top()
				&&
			pTop < (this->get_borderbox_offset_top() + get_borderbox_height());
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
	
	// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=49276
	template <typename tWidgetType, typename tDataType, class Rep, class Period>
	void anim(void(tWidgetType::*pFunc)(tDataType), tDataType pOrigin, tDataType pTarget, std::chrono::duration<Rep, Period> pDuration, std::function<double (double)> pTransition = &transitions::ease/*, std::function<void (void)> pStep = []{}, std::function<void (void)> pEnd = []{}*/);
};

template <typename tWidgetType, typename tDataType, class Rep, class Period>
void widget::anim(void(tWidgetType::*pFunc)(tDataType), tDataType pOrigin, tDataType pTarget, std::chrono::duration<Rep, Period> pDuration, std::function<double (double)> pTransition/*, std::function<void()> pStep, std::function<void()> pEnd*/)
{
	tWidgetType *pWidget = dynamic_cast<tWidgetType*>(this);
	context::recycle(new std::thread([pWidget, pFunc, pOrigin, pTarget, pDuration, pTransition/*, pStep, pEnd*/]
	{
		auto start = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::now();
	
		std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(pDuration);
	
		while(time < (start + duration))
		{
			std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(time - start);		
			(pWidget->*(pFunc))(pOrigin + (pTarget - pOrigin) * pTransition((double)diff.count() / (double)duration.count()));
			
			//pStep();
		
			time = std::chrono::system_clock::now();
			std::this_thread::sleep_for(std::chrono::milliseconds(40)); // 25 fps
		}
	
		(pWidget->*(pFunc))(pTarget);
		
		//pEnd();
	}));
}

} // namespace mugu

