/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#define _GLIBCXX_USE_SCHED_YIELD
#define _GLIBCXX_USE_NANOSLEEP

#include <cmath>
#include <vector>
#include <thread>
#include <iostream>
#include <functional>

#include <xcb/xcb.h>

// https://github.com/madrobby/emile

class context
{
public:
	static std::vector<std::thread*> garbages;
	xcb_connection_t *connection;
	
	context()
	{
		connection = xcb_connect(NULL, NULL);
	}
	
	~context()
	{
		for(std::thread* garbage : garbages)
		{
			if(garbage->joinable())
				garbage->join();
			delete garbage;
		}
		xcb_disconnect(connection);
	}
	
	static void recycle(std::thread* pGarbage)
	{
		garbages.push_back(pGarbage);
	}
};

class widget
{
public:
	unsigned width;

	virtual void set_width(unsigned pWidth)
	{
		this->width = pWidth;
	}
	
	unsigned get_width()
	{
		return this->width;
	}
};

class dialog : public widget
{
public:
	xcb_connection_t *connection;
	xcb_window_t window;

	dialog(xcb_connection_t *pConnection)
		: window(xcb_generate_id(connection)), connection(pConnection)
	{
		this->width = 500;
		
		const xcb_setup_t *setup = xcb_get_setup(connection);
		xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
		xcb_screen_t *screen = iter.data;
	
		xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0, 0, this->width, 150, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, 0, NULL);
		xcb_map_window(connection, window);
		xcb_flush(connection);
	}
	
	virtual void set_width(unsigned pWidth)
	{
		widget::set_width(pWidth);
		xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_WIDTH, &width);
		xcb_flush(connection);
	}
};

namespace transitions
{
	double linear(double pPos)
	{
		return pPos;
	}

	double ease(double pPos)
	{
		return (-cos(pPos * M_PI) / 2) + 0.5;
	}
}

template <typename tWidgetType, typename tDataType, typename tPassedType, class Rep, class Period>
void anim(
	tWidgetType* pWidget, void(tWidgetType::*pFunc)(tDataType),
	tPassedType pOrigin, tPassedType pTarget,
	std::chrono::duration<Rep, Period> pDuration,
	std::function<double (double)> pTransition = &transitions::ease)
{
	context::recycle(new std::thread([pWidget, pFunc, pOrigin, pTarget, pDuration, pTransition]
	{
		auto start = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::now();
		
		std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(pDuration);
		
		while(time < (start + duration))
		{
			std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(time - start);		
			((pWidget)->*(pFunc))(pOrigin + (pTarget - pOrigin) * pTransition((double)diff.count() / (double)duration.count()));
			
			time = std::chrono::system_clock::now();
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		
		((pWidget)->*(pFunc))(pTarget);
	}));
}

