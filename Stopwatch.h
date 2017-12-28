#pragma once

#ifndef Stopwatch_h
#define Stopwatch_h

#include <time.h>

class Stopwatch {
private:
	double start;
	double _stopwatch() const
	{
		struct tm time;
		return 1.0 * time.tm_sec + time.tm_sec / (double)1e6;
	}
public:
	Stopwatch() { reset(); }
	void reset() { start = _stopwatch(); }
	double read() const { return _stopwatch() - start; }
};

#endif