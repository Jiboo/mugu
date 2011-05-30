#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include <cairo/cairo.h>

#define IN_ALL_DIRECTIONS(pType, pName) \
	pType pName##_top; \
	pType pName##_right; \
	pType pName##_bottom; \
	pType pName##_left; \
	inline void set_##pName(unsigned pSize) \
	{ \
		pName##_top = pSize; \
		pName##_right = pSize; \
		pName##_bottom = pSize; \
		pName##_left = pSize; \
	} \
	inline void set_##pName(unsigned pSizeTB, unsigned pSizeRL) \
	{ \
		pName##_top = pSizeTB; \
		pName##_right = pSizeRL; \
		pName##_bottom = pSizeTB; \
		pName##_left = pSizeRL; \
	} \
	inline void set_##pName(unsigned pSizeT, unsigned pSizeRL, unsigned pSizeB) \
	{ \
		pName##_top = pSizeT; \
		pName##_right = pSizeRL; \
		pName##_bottom = pSizeB; \
		pName##_left = pSizeRL; \
	} \
	inline void set_##pName(unsigned pSizeT, unsigned pSizeR, unsigned pSizeB, unsigned pSizeL) \
	{ \
		pName##_top = pSizeT; \
		pName##_right = pSizeR; \
		pName##_bottom = pSizeB; \
		pName##_left = pSizeL; \
	}

enum alignment
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
	CENTER
};

class widget
{
public:
	unsigned width;
	unsigned height;
	unsigned top, left;
	IN_ALL_DIRECTIONS(unsigned, margin);
	IN_ALL_DIRECTIONS(unsigned, border);
	IN_ALL_DIRECTIONS(unsigned, padding);

	bool visible;

	widget* parent;

	widget()
	{
		this->top = 0;
		this->left = 0;
		this->width = 0;
		this->height = 0;

		this->visible = true;

		this->set_margin(0);
		this->set_border(0);
		this->set_padding(0);
	}
	virtual ~widget() {}

	inline unsigned get_marginbox_offset_left() { return this->left; }
	inline unsigned get_marginbox_offset_top() { return this->top; }
	inline unsigned get_marginbox_width() { return this->get_borderbox_width() + this->margin_top + this->margin_bottom; }
	inline unsigned get_marginbox_height() { return this->get_borderbox_height() + this->margin_top + this->margin_bottom; }

	inline void set_marginbox_width(unsigned pWidth) { this->width = pWidth - this->margin_left - this->margin_right - this->border_left - this->border_right - this->padding_left - this->padding_right; }
	inline void set_marginbox_height(unsigned pHeight) { this->height = pHeight - this->margin_top - this->margin_bottom - this->border_top - this->border_bottom - this->padding_top - this->padding_bottom; }

	inline unsigned get_borderbox_offset_left() { return get_marginbox_offset_left() + this->margin_left; }
	inline unsigned get_borderbox_offset_top() { return get_marginbox_offset_top() + this->margin_top; }
	inline unsigned get_borderbox_width() { return this->get_paddingbox_width() + this->border_top + this->border_bottom; }
	inline unsigned get_borderbox_height() { return this->get_paddingbox_height() + this->border_top + this->border_bottom; }

	inline unsigned get_paddingbox_offset_left() { return get_borderbox_offset_left() +  this->border_left; }
	inline unsigned get_paddingbox_offset_top() { return get_borderbox_offset_top() + this->border_top; }
	inline unsigned get_paddingbox_width() { return get_contentbox_width() + this->padding_top + this->padding_bottom; }
	inline unsigned get_paddingbox_height() { return get_contentbox_height() + this->padding_top + this->padding_bottom; }

	inline unsigned get_contentbox_offset_left() { return get_paddingbox_offset_left() + this->padding_left; }
	inline unsigned get_contentbox_offset_top() { return get_paddingbox_offset_top() + this->padding_top; }
	inline unsigned get_contentbox_width() { return this->width; }
	inline unsigned get_contentbox_height() { return this->height; }

	inline void set_contentbox_width(unsigned pWidth) { this->width = pWidth; }
	inline void set_contentbox_height(unsigned pHeight) { this->height = pHeight; }

	virtual void layout() {};

	virtual void draw(cairo_t* pContext)
	{
		//margin
		cairo_set_source_rgb(pContext, 1, 0, 0);
		cairo_rectangle(pContext, this->get_marginbox_offset_left(), this->get_marginbox_offset_top(), this->get_marginbox_width(), this->get_marginbox_height());
		cairo_fill(pContext);

		//border
		cairo_set_source_rgb(pContext, 0, 1, 0);
		cairo_rectangle(pContext, this->get_borderbox_offset_left(), this->get_borderbox_offset_top(), this->get_borderbox_width(), this->get_borderbox_height());
		cairo_fill(pContext);

		// padding
		cairo_set_source_rgb(pContext, 0, 0, 1);
		cairo_rectangle(pContext, this->get_paddingbox_offset_left(), this->get_paddingbox_offset_top(), this->get_paddingbox_width(), this->get_paddingbox_height());
		cairo_fill(pContext);

		// content
		cairo_set_source_rgb(pContext, 1, 1, 1);
		cairo_rectangle(pContext, this->get_contentbox_offset_left(), this->get_contentbox_offset_top(), this->get_contentbox_width(), this->get_contentbox_height());
		cairo_fill(pContext);
	}

	virtual void get_prefered_size(unsigned &pWidth, unsigned &pHeight)
	{
		pWidth = this->get_marginbox_width();
		pHeight = this->get_marginbox_height();
	}

	void debug(const char* pName)
	{
		cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, this->get_marginbox_width(), this->get_marginbox_height());
		cairo_t* ctx = cairo_create(surface);
		this->draw(ctx);
		cairo_surface_write_to_png(surface, pName);
		cairo_destroy(ctx);
		cairo_surface_destroy(surface);
	}
};

class container : public widget
{
public:
	std::vector<widget*> children;
	unsigned hgap, vgap;
	bool hfill, vfill;

	container()
	{
		this->hgap = 1;
		this->vgap = 1;
		this->hfill = true;
		this->vfill = true;
	}

	virtual ~container()
	{
		for(widget* child : children)
			delete child;
	}

	void add(widget* pChild)
	{
		pChild->parent = this;
		this->children.push_back(pChild);
	}

	virtual void draw(cairo_t* pContext)
	{
		if(this->visible)
		{
			widget::draw(pContext);

			for(widget* child : children)
			{
				if(child->visible)
					child->draw(pContext);
			}
		}
	}
};

class grid : public container
{
public:
	unsigned rows, cols;

	grid(unsigned pRows, unsigned pCols)
	{
		this->rows = pRows;
		this->cols = pCols;
	}

	grid(std::initializer_list<std::initializer_list<widget*>> pChildren)
	{
		this->rows = pChildren.size();
		this->cols = (*(pChildren.begin())).size();

		for(std::initializer_list<widget*> row : pChildren)
		{
			for(widget* col : row)
			{
				this->add(col);
			}
		}
	}

	virtual ~grid() {}

	virtual void get_prefered_size(unsigned &pWidth, unsigned &pHeight)
	{
		unsigned max_width, max_height;

		if(this->width > 0)
			max_width = (this->width - (this->cols - 1) * this->hgap) / cols;
		else
			max_width = 0;

		if(this->height > 0)
			max_height = (this->height - (this->rows - 1) * this->vgap) / rows;
		else
			max_height = 0;

		unsigned child_width, child_height;

		for(widget* child : this->children)
		{
			child->get_prefered_size(child_width, child_height);

			max_width = std::max(max_width, child_width);
			max_height = std::max(max_height, child_height);
		}

		pWidth = (max_width * cols) + (this->cols - 1) * this->hgap;
		pHeight = (max_height * rows) + (this->rows - 1) * this->vgap;
	}

	virtual void layout()
	{
		this->get_prefered_size(this->width, this->height);

		unsigned max_width = (this->width - (this->cols - 1) * this->hgap) / cols;
		unsigned max_height = (this->height - (this->rows - 1) * this->vgap) / rows;

		unsigned offset_left = this->get_contentbox_offset_left();
		unsigned offset_top = this->get_contentbox_offset_top();

		unsigned col = 0;

		for(widget* child : this->children)
		{
			child->left = offset_left;
			child->top = offset_top;

			child->layout();

			if(this->hfill)
				child->set_marginbox_width(max_width);
			if(this->vfill)
				child->set_marginbox_height(max_height);

			if(++col >= this->cols)
			{
				offset_left = this->get_contentbox_offset_left();
				offset_top += max_height + this->vgap;
				col = 0;
			}
			else
			{
				offset_left += max_width + this->hgap;
			}
		}
	}
};

class flexgrid : public container
{
public:
	std::vector<unsigned> rows;
	std::vector<unsigned> cols;

	flexgrid(unsigned pRows, unsigned pCols)
		: rows(pRows, 0), cols(pCols, 0)
	{
	}

	flexgrid(std::initializer_list<std::initializer_list<widget*>> pChildren)
	{
		this->rows.assign(pChildren.size(), 0);
		this->cols.assign((*(pChildren.begin())).size(), 0);

		for(std::initializer_list<widget*> row : pChildren)
		{
			for(widget* col : row)
				this->add(col);
		}
	}

	virtual ~flexgrid() {}

	virtual void get_prefered_size(unsigned &pWidth, unsigned &pHeight)
	{
		unsigned w = 0, h = 0, r, c;
		unsigned child_width, child_height;

		for(unsigned i = 0; i < this->children.size(); i++)
		{
			r = i / this->cols.size();
            c = i % this->cols.size();

			children[i]->get_prefered_size(child_width, child_height);

			rows[r] = std::max(rows[r], child_height);
			cols[c] = std::max(cols[c], child_width);
		}

		for(unsigned col : cols)
			w += col;

		for(unsigned row : rows)
			h += row;

		pWidth = w + (this->cols.size() - 1) * this->hgap;
		pHeight = h + (this->rows.size() - 1) * this->vgap;
	}

	virtual void layout()
	{
		this->get_prefered_size(this->width, this->height);

		unsigned offset_left = this->get_contentbox_offset_left();
		unsigned offset_top = this->get_contentbox_offset_top();

		unsigned r, c;

		for(unsigned i = 0; i < this->children.size(); i++)
		{
			widget* child = this->children[i];

			r = i / this->cols.size();
			c = i % this->cols.size();

			child->left = offset_left;
			child->top = offset_top;

			child->layout();

			if(this->hfill)
				child->set_marginbox_width(cols[c]);
			if(this->vfill)
				child->set_marginbox_height(rows[r]);

			if(c == (this->cols.size() - 1))
			{
				offset_left = this->get_contentbox_offset_left();
				offset_top += this->rows[r] + this->vgap;
			}
			else
			{
				offset_left += this->cols[c] + this->hgap;
			}
		}
	}
};

class hbox : public flexgrid
{
public:
	hbox(unsigned pCols)
		: flexgrid(1, pCols)
	{}

	hbox(std::initializer_list<widget*> pChildren)
		: flexgrid({ pChildren })
	{}

	virtual ~hbox() {}
};

class vbox : public flexgrid
{
public:
	vbox(unsigned pRows)
		: flexgrid(pRows, 1)
	{}

	vbox(std::initializer_list<widget*> pChildren)
		: flexgrid(pChildren.size(), 1)
	{
		for(widget* row : pChildren)
			this->add(row);
	}

	virtual ~vbox() {}
};

class hboxf : public grid
{
public:
	hboxf(unsigned pCols) : grid(1, pCols) {}

	hboxf(std::initializer_list<widget*> pChildren) : grid({ pChildren }) {}

	virtual ~hboxf() {}
};

class vboxf : public grid
{
public:
	vboxf(unsigned pRows) : grid(pRows, 1) {}

	vboxf(std::initializer_list<widget*> pChildren)
		: grid(0, 0)
	{
		this->rows = pChildren.size();
		this->cols = 1;

		for(widget* row : pChildren)
			this->add(row);
	}

	virtual ~vboxf() {}
};

