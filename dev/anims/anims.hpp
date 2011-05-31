/*
Mugu by LEPESME "Jiboo" Jean-Baptiste is licensed under a Creative Commons Attribution 3.0 Unported License
http://creativecommons.org/licenses/by/3.0/
*/

#define _GLIBCXX_USE_SCHED_YIELD
#define _GLIBCXX_USE_NANOSLEEP

#include <cmath>
#include <thread>
#include <iostream>

// https://github.com/madrobby/emile

namespace transitions
{

	double none(double pPos)
	{
		return pPos;
	}

	double ease(double pPos)
	{
		return (-cos(pPos * M_PI) / 2) + 0.5;
	}
}
	
template <typename tDataType, class Rep, class Period>
std::thread * anim(
	tDataType &pData, tDataType pTarget, 
	std::chrono::duration<Rep, Period> pDuration, 
	std::function<double (double)> pTransition = &transitions::none,
	std::function<void (void)> pStep = []{},
	std::function<void (void)> pEnd = []{})
{
	return new std::thread([&pData, pTarget, pDuration, pTransition, pStep, pEnd]
	{
		tDataType origin = pData;
		
		auto start = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::now();
		
		std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(pDuration);
		
		while(time < (start + duration))
		{
			std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(time - start);		
			pData = origin + (pTarget - origin) * pTransition((double)diff.count() / (double)duration.count());
			
			pStep();

			time = std::chrono::system_clock::now();
			//std::this_thread::yield(); // Would be nice if no pStep callback
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		
		pData = pTarget;
		
		pEnd();
	});
}

