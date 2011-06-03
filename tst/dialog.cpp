/*
 * dialog.cpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */

#include "mugu.hpp"
#include "mugu/random.hpp"

using namespace mugu;

int main(int, char**)
{
	srand(time(NULL));
	
	typedef dialog<grid> dialog_t;

	dialog<grid> *d1 = new dialog<grid>;
	d1->set_visible(true);
	d1->set_rows(4);
	d1->set_cols(1);
	d1->set_title("Coucou lol");
	
	random_widget *r1 = new random_widget();
	random_widget *r2 = new random_widget();
	random_widget *r3 = new random_widget();
	random_widget *r4 = new random_widget();
	
	d1->add(r1);
	d1->add(r2);
	d1->add(r3);
	d1->add(r4);
	
	d1->adapt();

	d1->anim(&dialog_t::set_width, d1->get_width(), (unsigned)800, std::chrono::seconds(3));
	
	//r1->anim(&random_widget::set_width, r1->get_width(), (unsigned)800, std::chrono::seconds(3));
	
	context::clean();
	
	delete d1;
	return 0;
}

