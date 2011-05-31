/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#include "anims.hpp"
#include <xcb/xcb.h>

void set_dialog_width(xcb_connection_t *connection, xcb_window_t window, uint32_t width)
{
	xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_WIDTH, &width);
	xcb_flush(connection);
}

int main(int,char**)
{
	xcb_connection_t *connection   = xcb_connect(NULL, NULL);
	const xcb_setup_t *setup       = xcb_get_setup(connection);
	xcb_screen_iterator_t iter     = xcb_setup_roots_iterator(setup);
	xcb_screen_t *screen           = iter.data;
	xcb_window_t window            = xcb_generate_id(connection);
	
	xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0, 0, 150, 150, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, 0, NULL );
    xcb_map_window(connection, window);
    xcb_flush(connection);

	uint32_t values = 300;
	xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_WIDTH, &values);
	xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_HEIGHT, &values);
	
	std::thread* th = anim(values, 800, std::chrono::seconds(3), &transitions::ease, [&values, connection, window]
	{
		xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_WIDTH, &values);
		xcb_flush(connection);
	});
	th->join();
	delete th;

	th = anim(std::bind(set_dialog_width, connection, window, std::placeholders::_1), 800, 300, std::chrono::seconds(3), &transitions::ease);
	th->join();
	delete th;

	xcb_disconnect(connection);
}
