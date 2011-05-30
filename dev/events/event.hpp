/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <thread>

class event_stop : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "If you can read this you did something wrong.";
	}

	virtual ~event_stop() throw() {}
};

template<typename... tArgTypes>
class event
{
public:
	std::vector<std::thread*> garbages;
	std::vector<std::function<void(tArgTypes...)>> callbacks;
	std::function<void(void)> final;
	bool async;

	event(std::function<void()> pFinal) : final(pFinal), async(false) {}

	~event()
	{
		for(std::thread* garbage: garbages)
		{
			if(garbage->joinable())
				garbage->join();
			delete garbage;
		}
	}

	void connect(std::function<void(tArgTypes...)> pFunc)
	{
		callbacks.push_back(pFunc);
	}

	void run(tArgTypes...pArgs)
	{
		try
		{
			for(std::function<void(tArgTypes...)> &callback : callbacks)
				callback(pArgs...);
			this->final();
		}
		catch(event_stop& e) {}
		catch(std::exception& e) {}
		catch(...) {}
	}

	void fire(tArgTypes...pArgs)
	{
		if(!this->async)
			this->run(pArgs...);
		else
			this->garbages.push_back(new std::thread(std::bind(&event<tArgTypes...>::run, this, pArgs...)));
	}
};

