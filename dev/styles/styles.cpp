#include "styles.hpp"

int main(int,char**)
{
	sample_widget* w = new sample_widget();
	
	cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, w->width, w->height);
	cairo_t* ctx = cairo_create(surface);
	w->draw(ctx);
	cairo_surface_write_to_png(surface, "test.png");
	cairo_destroy(ctx);
	cairo_surface_destroy(surface);
	
	delete w;

	return 0;
}

