#include "GameTimer.h"
#include <limits>

using std::numeric_limits;

// Allowed overhead for time checks.
// Do not rely on this number (i.e. set to 0 or near 0)
// when checking time limits.
const double allowedOverheadTime(0.05);

GameTimer::GameTimer(const TimeParams &timeParams) :
m_timeParams(timeParams)
{
};

GameTimer::GameTimer(const GameTimer &gameTimer)
{
	m_timeParams = gameTimer.m_timeParams;
	m_gameStartTime = gameTimer.m_gameStartTime;
	m_moveStartTime = gameTimer.m_moveStartTime;
};

GameTimer::~GameTimer()
{
};

#ifdef WIN32

void GameTimer::getCurTime(clock_t &curTime) const
{
	curTime = clock();
};

double GameTimer::timeDiffInSec(clock_t before, clock_t after) const 
{
	return (after-before)/(double)CLOCKS_PER_SEC;
};

#else

void GameTimer::getCurTime(struct timeval &tv) const
{
	struct timezone tz;
	gettimeofday(&tv, &tz);
};

double GameTimer::timeDiffInSec(const struct timeval &before, 
								const struct timeval &after) const
{
	return (after.tv_sec - before.tv_sec) + 
		((after.tv_usec - before.tv_usec)/1000000.0);
};

#endif

void GameTimer::startGameTimer()
{
	getCurTime(m_gameStartTime);
};

bool GameTimer::isGameTimePassed() const
{
	return getRemainingGameTime() + allowedOverheadTime < 0;
};

double GameTimer::getRemainingGameTime() const
{
	if(!m_timeParams.timePerGame_limit)
		return numeric_limits<double>::max();

#ifdef WIN32
	clock_t curTime;
#else
	struct timeval curTime;
#endif
	getCurTime(curTime);
	return (m_timeParams.timePerGame - timeDiffInSec(m_gameStartTime, curTime));
};

void GameTimer::startMoveTimer()
{
	getCurTime(m_moveStartTime);
};

bool GameTimer::isMoveTimePassed() const
{
	return getRemainingMoveTime() + allowedOverheadTime < 0;
};

double GameTimer::getRemainingMoveTime() const
{
	if(!m_timeParams.timePerMove_limit)
		return numeric_limits<double>::max();

#ifdef WIN32
	clock_t curTime;
#else
	struct timeval curTime;
#endif
	getCurTime(curTime);
	return (m_timeParams.timePerMove - timeDiffInSec(m_moveStartTime, curTime));
};
