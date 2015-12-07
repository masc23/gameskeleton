#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
#ifdef _WIN32
	Timer();
#endif
    float Elapsed();

private:
#ifdef _WIN32
	__int64 Frequency;
	__int64 StartTime;
#endif
};

#endif
