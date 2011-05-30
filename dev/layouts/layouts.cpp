/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#include <chrono>
#include <cmath>

#include "layouts.hpp"

class random_widget : public widget
{
public:
	random_widget()
	{
		this->width = rand() % 10 + 1;
		this->height = rand() % 10 + 1;

		this->set_margin(rand() % 2 + 1);
		this->set_border(rand() % 2 + 1);
		this->set_padding(rand() % 2 + 1);
	}

	virtual ~random_widget()
	{
	}
};

int main(int,char**)
{
	#define COUNT 62500

	srand(time(NULL));

	grid *c1 = new grid(sqrt(COUNT), sqrt(COUNT));
		for(int i = 1; i <= COUNT; i++)
			c1->add(new random_widget());

	auto t1 = std::chrono::system_clock::now();
	c1->adapt();
	c1->layout();
	auto t2 = std::chrono::system_clock::now();

	std::chrono::duration<double> d = (t2 - t1);
	std::chrono::nanoseconds n = (t2 - t1);

	std::cout << "Layouting " << COUNT << " random size widgets on a grid took: " << d.count() << "s ("
		<< (n.count()/COUNT) << "ns/widget)" << std::endl;

	if(COUNT <= 62500)
		c1->debug("grid.png");
	delete c1;

	flexgrid *c2 = new flexgrid(sqrt(COUNT), sqrt(COUNT));
		for(int i = 1; i <= COUNT; i++)
			c2->add(new random_widget());

	t1 = std::chrono::system_clock::now();
	c2->adapt();
	c2->layout();
	t2 = std::chrono::system_clock::now();

	d = (t2 - t1);
	n = (t2 - t1);

	std::cout << "Layouting " << COUNT << " random size widgets on a flexgrid took: " << d.count() << "s ("
		<< (n.count()/COUNT) << "ns/widget)" << std::endl;

	if(COUNT <= 62500)
		c2->debug("flexgrid.png");
	delete c2;

	flexgrid *c3 = new flexgrid(
	{
		{new random_widget(), new random_widget()},
		{new random_widget(), new flexgrid(
		{
			{new random_widget(), new random_widget()},
			{new random_widget(), new random_widget()}
		})},
	});
	
	c3->adapt();
	
	c3->width = 200;
	
	c3->layout();
	c3->debug("test flexgrid.png");
	delete c3;
	
	grid *c4 = new grid(
	{
		{new random_widget(), new random_widget()},
		{new random_widget(), new grid(
		{
			{new random_widget(), new random_widget()},
			{new random_widget(), new random_widget()}
		})},
	});
	
	c4->adapt();
	
	c4->width = 200;
	
	c4->layout();
	c4->debug("test grid.png");
	delete c4;
	
	hbox *h1 = new hbox({new random_widget(), new random_widget()});
	hbox *h2 = new hbox({new random_widget(), new random_widget()});
	vbox *c5 = new vbox({h1, h2});
	c5->adapt();
	c5->layout();
	c5->debug("test box.png");
	
	delete c5;
	return 0;
}

