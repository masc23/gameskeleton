#include "Timer.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <boost/date_time/posix_time/posix_time.hpp>
#endif

#ifdef _WIN32
Timer::Timer() : StartTime(0), Frequency(0)
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER startTime;
	
	DWORD_PTR threadAffinityMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceFrequency(&frequency);
	if (frequency.QuadPart == 0)
		DWORD err = GetLastError();
	QueryPerformanceCounter(&startTime);
	SetThreadAffinityMask(GetCurrentThread(), threadAffinityMask);

	Frequency = frequency.QuadPart;
	StartTime = startTime.QuadPart;
}
#endif

float Timer::Elapsed()
{
#ifdef _WIN32
	LARGE_INTEGER currentTime;
	
	DWORD_PTR threadAffinityMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceCounter(&currentTime);
	SetThreadAffinityMask(GetCurrentThread(), threadAffinityMask);

	__int64 diff = currentTime.QuadPart - StartTime;
	StartTime = currentTime.QuadPart;

	return static_cast<float>(diff) / static_cast<float>(Frequency);

#else
    static boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::universal_time();

    boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();
    boost::posix_time::time_duration diff = now - startTime;
    startTime = now;

    return static_cast<float>(diff.total_milliseconds()) / 1000.0f;
#endif
}
