/* GameTimer.h
 *
 * Game and move timer.
 * Provides methods to start and check given time limits.
 *
 * Supports both Windows and Linux.
 */

#ifndef __GAME_TIMER_H__
#define __GAME_TIMER_H__

#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

class GameTimer
{
public:
	// Time parameters structure
	typedef struct
	{
		bool timePerMove_limit;		// Is move time limited
		double timePerMove;			// Time limit per move, in seconds
		bool timePerGame_limit;		// Is game time limited
		double timePerGame;			// Time limit per game, in seconds
	} TimeParams;

	// Constructor
	// Copies timeParams data to m_timeParams
	// Does not start timers
	GameTimer(const TimeParams &timeParams);
	// Copy Constructor
	// Copies gameTimer time parameters and state of timers
	GameTimer(const GameTimer &gameTimer);
	// Virtual Destructor
	~GameTimer();

	// Starts the game timer and records this time
	void startGameTimer();
	// Is current time minus (recorded game time start plus overhead) less than 0
	bool isGameTimePassed() const;
	// Returns allowed game time minus (current time minus recorded game time start)
	// in seconds
	double getRemainingGameTime() const;

	// Starts the move timer and records this time
	void startMoveTimer();
	// Is current time minus (recorded move time start plus overhead) less than 0
	bool isMoveTimePassed() const;
	// Returns allowed move time minus (current time minus recorded move time start)
	// in seconds
	double getRemainingMoveTime() const;

private:
#ifdef WIN32
	// Gets current time in clock_t units
	void getCurTime(clock_t &curTime) const;
	// Returns time difference in seconds of (after - before)
	double timeDiffInSec(clock_t before, clock_t after) const;
#else
	// Gets current time in clock_t units
	void getCurTime(struct timeval &tv) const;
	// Returns time difference in seconds of (after - before)
	double timeDiffInSec(const struct timeval &before, 
		const struct timeval &after) const;
#endif

	TimeParams m_timeParams;	// Timer parameters
#ifdef WIN32
	clock_t m_gameStartTime;	// Game start time in clock_t units
	clock_t m_moveStartTime;	// Move start time in clock_t units
#else
	timeval m_gameStartTime;	// Game start time in timeval units
	timeval m_moveStartTime;	// Move start time in timeval units
#endif
};

#endif
