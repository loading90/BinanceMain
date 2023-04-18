#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>
#include <ctime>
#include <stack>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>    // usleep()
#endif

class SecondsTimer
{
	time_t interval;
	time_t lastTime;

public:
	SecondsTimer(time_t interval);
	SecondsTimer(const SecondsTimer& timer);

	void SetInterval(time_t interval);
	time_t GetInterval() const;

	bool IsPassedTime();
	void Reset();

	SecondsTimer& operator=(const SecondsTimer& timer);

	~SecondsTimer();
};

class MillisTimer
{
#ifdef _WIN32
	// Для Windows надо хранить системную частоту таймера.
	LARGE_INTEGER freq;
#endif

	uint64_t interval;
	uint64_t lastTime;

	uint64_t Millis();

public:
	static void Delay(uint64_t ms);

	MillisTimer(uint64_t interval);
	MillisTimer(const MillisTimer& timer);

	void SetInterval(uint64_t interval);
	uint64_t GetInterval() const;

	bool IsPassedTime();
	void Reset();

	MillisTimer& operator=(const MillisTimer& timer);

	~MillisTimer();
};

#endif /* TIMER_H_ */
