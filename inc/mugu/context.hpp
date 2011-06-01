/*
 * context.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

namespace mugu
{

class context
{
protected:
	std::vector<std::thread*> garbages;
	xcb_connection_t *connection;
	
	const xcb_screen_t *screen;
	const xcb_setup_t *setup;

public:
	context()
	{
		this->connection = xcb_connect(NULL, NULL);
		this->setup = xcb_get_setup(this->connection);
        xcb_screen_iterator_t iter = xcb_setup_roots_iterator(this->setup);
        this->screen = iter.data;
	}
	
	~context()
	{
		xcb_disconnect(this->connection);
	}

protected:
	xcb_window_t create_window()
	{
		xcb_window_t window = xcb_generate_id(this->connection);

		xcb_create_window(this->connection,
			XCB_COPY_FROM_PARENT,
			window,
			this->screen->root,
			0, 0,
			150, 150,
			10,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			this->screen->root_visual,
			0, NULL);

		return window;
	}
	
public:
	static context& instance ()
	{
		std::cout << "creating context" << std::endl;
		static context singleton;
		return singleton; 
	}
	
	static void flush()
	{
		xcb_flush(this->instance().connection);
	}
	
	static void recycle(std::thread* pGarbage)
	{
		this->instance().garbages.push_back(pGarbage);
	}
};

} // namespace mugu

