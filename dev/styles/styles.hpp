/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#include <string>
#include <vector>
#include <cairo/cairo.h>

class widget;

class source
{
public:
	widget* parent;

	virtual ~source() {};
	virtual void select(cairo_t* pContext) = 0;
};

class widget
{
public:
	source *background;
	double width, height, top, left;
	
	widget() {}

	virtual ~widget()
	{
		delete this->background;
	}

	virtual void draw(cairo_t* pContext)
	{
		this->background->select(pContext);
		cairo_rectangle(pContext, this->left, this->top, this->width, this->height);
		cairo_fill(pContext);
	}
};

class source_rgba : public source
{
public:
	double r, g, b, a;

	source_rgba(double pR = 0, double pG = 0, double pB = 0, double pA = 1) : r(pR), g(pG), b(pB), a(pA) {}
	virtual ~source_rgba() {};

	void select(cairo_t *pContext) { cairo_set_source_rgba(pContext, this->r, this->g, this->b, this->a); }
};

class source_png : public source
{
public:
	cairo_surface_t *image;

	source_png(const char *pPath) { this->image = cairo_image_surface_create_from_png(pPath); }
	virtual ~source_png() { cairo_surface_destroy(this->image); }

	void select(cairo_t *pContext) { cairo_set_source_surface(pContext, this->image, 0, 0); }
};

class gradient_color_stop
{
public:
	double r, g, b, a;
};

class source_gradient : public source
{
public:
	cairo_pattern_t *pattern;

	source_gradient(double pX0, double pY0, double pX1, double pY1, std::initializer_list<gradient_color_stop> pStops)
	{
		this->pattern = cairo_pattern_create_linear(pX0, pY0, pX1, pY1);
		unsigned offset = 0;
		for(const gradient_color_stop &stop : pStops)
			cairo_pattern_add_color_stop_rgba(this->pattern, offset++, stop.r, stop.g, stop.b, stop.a);
	}
	/*source_gradient(widget* pWidget, std::initializer_list<gradient_color_stop> pStops)
		: source_gradient(0, 0, 0, pWidget->get_marginbox_height(), pStops)
	{}*/
	source_gradient(widget* pWidget, std::initializer_list<gradient_color_stop> pStops)
	{
		this->pattern = cairo_pattern_create_linear(0, 0, 0, pWidget->height);
		unsigned offset = 0;
		for(const gradient_color_stop &stop : pStops)
			cairo_pattern_add_color_stop_rgba(this->pattern, offset++, stop.r, stop.g, stop.b, stop.a);
	}
	
	virtual ~source_gradient() { cairo_pattern_destroy(this->pattern); }

	void select(cairo_t *pContext) { cairo_set_source(pContext, this->pattern); }
};

class sample_widget : public widget
{
public:
	sample_widget()
	{
		this->left = 0;
		this->top = 0;
		
		this->width = rand() % 10 + 100;
		this->height = rand() % 10 + 20;
		
		this->background = new source_gradient(this,
		{
			{0.5, 0.5, 0.5, 0.1},
			{0, 0, 0, 1}
		});
	}
	
	virtual ~sample_widget()
	{
	}
};

