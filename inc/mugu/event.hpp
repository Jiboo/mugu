/*
 * event.hpp
 * This file is part of Mugu
 *
 * Copyright (C) 2011 - LEPESME "Jiboo" Jean-Baptiste
 *
 * Mugu is licensed under a Creative Commons Attribution 3.0 Unported License
 * http://creativecommons.org/licenses/by/3.0/
 */
 
#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include <thread>

#include "mugu/defines.hpp"
#include "mugu/context.hpp"

namespace mugu
{

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
protected:
	std::vector<std::function<void(tArgTypes...)>> callbacks;
	std::function<void(void)> final;
	
public:
	MUGU_PROP(, is, bool, async);

public:
	event(std::function<void()> pFinal) : final(pFinal), async(false) {}

public:
	void connect(std::function<void(tArgTypes...)> pFunc)
	{
		callbacks.push_back(pFunc);
	}

	void run(tArgTypes...pArgs);

	void fire(tArgTypes...pArgs)
	{
		if(!this->async)
			this->run(pArgs...);
		else
			context::recycle(new std::thread(std::bind(&event<tArgTypes...>::run, this, pArgs...)));
	}
};

template<typename... tArgTypes>
void event<tArgTypes...>::run(tArgTypes...pArgs)
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

} // namespace mugu
