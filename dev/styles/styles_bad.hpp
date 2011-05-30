/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#include <string>
#include <cairo>

class source
{
public:
	virtual ~source() {};
	virtual void select(cairo_t* pContext) = 0;
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

	source_png(const char *pPath) { cairo_image_surface_create_from_png(pPath); }
	virtual ~source_png() { cairo_surface_destroy(this->image); }

	void select(cairo_t *pContext) { cairo_set_source_surface(pContext, this->image, 0, 0); }
};

class widget_style
{
public:
	source* background;
	bool specific;
	
	static widget_style* get_default()
	{
	}
};

class widget
{
private:
	widget_style* style;
public:
	virtual ~widget()
	{
		if(style->specific)
			delete style;
	}

	const widget_style* get_style()
	{
		return this->style;
	}
};

class button_style : public widget_style
{
public:
	source* text_color;
};

class button : public widget
{
	std::string text;
};

