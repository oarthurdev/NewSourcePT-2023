#include "_Timer.h"

Timer::Timer() : beg_(clock_::now()) {}

void Timer::reset()
{
	beg_ = clock_::now();
}


std::chrono::seconds Timer::elapsed() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(clock_::now() - beg_);
}