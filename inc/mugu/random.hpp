/*
 * random.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#pragma once

#include <iostream>
#include <cairo/cairo.h>

#include "mugu/clickable.hpp"

namespace mugu
{

class random_widget : public clickable
{
public:
	random_widget()
		: clickable(std::bind(&random_widget::__click_final, this))
	{
		this->width = rand() % 100 + 1;
		this->height = rand() % 20 + 1;

		this->set_margin(rand() % 2 + 1);
		this->set_border_size(rand() % 2 + 1);
		this->set_padding(rand() % 2 + 1);
	}

	virtual ~random_widget()
	{
	}
	
	virtual void draw(cairo_t* pContext);

protected:
	void __click_final()
	{
		std::cout << this << " clicked!" << std::endl;
	}
};

} // namespace mugu

