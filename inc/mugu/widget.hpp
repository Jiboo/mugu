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
#include "mugu/transitions.hpp"
#include "mugu/context.hpp"

namespace mugu
{

class base_dialog;

class widget
{
	friend class container;

protected:
	widget* parent;
	base_dialog* root;

public:
	MUGU_PROP(virtual, get, unsigned, width);
	MUGU_PROP(virtual, get, unsigned, height);
	MUGU_PROP(, get, unsigned, top);
	MUGU_PROP(, get, unsigned, left);

	MUGU_PROP(virtual, is, bool, visible);
	MUGU_PROP(, is, bool, enabled);
	MUGU_PROP(, has, bool, focus);

public:
	widget();
	
	virtual ~widget() {}

public:
	virtual void layout() {}
	virtual void adapt() {}

	virtual void refresh();
	virtual void redraw();
	
	virtual void draw(cairo_t*) {}
	virtual void invalidates(unsigned, unsigned, unsigned, unsigned) {}

public:
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

