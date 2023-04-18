#ifdef __linux__
#include "Timer.hpp"
#elif _WIN32
#include "Timer.hpp"
#endif

/* SecondsTimer */
SecondsTimer::SecondsTimer(time_t interval)
{
	this->interval = interval;
	this->lastTime = time(NULL);
}
SecondsTimer::SecondsTimer(const SecondsTimer& timer)
{
	*this = timer;
}

void SecondsTimer::SetInterval(time_t interval)
{
	this->interval = interval;
	Reset();
}
time_t SecondsTimer::GetInterval() const
{
	return this->interval;
}

bool SecondsTimer::IsPassedTime()
{
	if (time(NULL) - this->lastTime >= this->interval)
	{
		return true;
	}
	return false;
}
void SecondsTimer::Reset()
{
	this->lastTime = time(NULL);
}

SecondsTimer& SecondsTimer::operator=(const SecondsTimer& timer)
{
	if (this == &timer)
		return *this;

	this->interval = timer.interval;
	this->lastTime = timer.lastTime;

	return *this;
}

SecondsTimer::~SecondsTimer() {}
/* ----------- */


/* MillisTimer */
#ifdef _WIN32
MillisTimer::MillisTimer(uint64_t interval)
{
	// ��� Windows � ������������ �������� ��������� ������� �������
	// (���������� ����� � �������).
	if (!QueryPerformanceFrequency(&this->freq))
		this->freq.QuadPart = 0;

	this->interval = interval;
	this->lastTime = Millis();
}

uint64_t MillisTimer::Millis()
{
	LARGE_INTEGER current;
	if (this->freq.QuadPart == 0 || !QueryPerformanceCounter(&current))
		return 0;

	// ������������� ���������� ��������� ����� � ������������.
	return static_cast<uint64_t>(current.QuadPart / (this->freq.QuadPart / 1000));
}

void MillisTimer::Delay(uint64_t ms)
{
	Sleep(static_cast<DWORD>(ms));
}

#else // WIN32
MillisTimer::MillisTimer(uint64_t interval)
{
	this->interval = interval;
	this->lastTime = Millis();
}

uint64_t MillisTimer::Millis()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return static_cast<uint64_t>(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void MillisTimer::Delay(uint64_t ms)
{
	usleep(static_cast<useconds_t>(ms * 1000));
}

#endif // _WIN32

MillisTimer::MillisTimer(const MillisTimer& timer)
{
	*this = timer;
}

void MillisTimer::SetInterval(uint64_t interval)
{
	this->interval = interval;
	Reset();
}
uint64_t MillisTimer::GetInterval() const
{
	return this->interval;
}

bool MillisTimer::IsPassedTime()
{
	if (Millis() - this->lastTime >= this->interval)
	{
		return true;
	}
	return false;
}
void MillisTimer::Reset()
{
	this->lastTime = Millis();
}

MillisTimer& MillisTimer::operator=(const MillisTimer& timer)
{
	if (this == &timer)
		return *this;

#ifdef _WIN32
	this->freq = timer.freq;
#endif // _WIN32

	this->interval = timer.interval;
	this->lastTime = timer.lastTime;

	return *this;
}

MillisTimer::~MillisTimer() {}
/* ----------- */
