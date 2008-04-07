/*
 * An abstract class that implements an iterative deepening version of the AlphaBeta algorithm.
 * Any inheriting class should implement the utility method.
 */

#ifndef __OMER_MARK_ALPHA_BETA_KALAH_PLAYER_H__
#define __OMER_MARK_ALPHA_BETA_KALAH_PLAYER_H__

#include "KalahPlayer.h"
#include "OmerMarkAlphaBetaResults.h"

class OmerMarkAlphaBetaKalahPlayer : public KalahPlayer
{
public:

	/* Constructor. */
	OmerMarkAlphaBetaKalahPlayer(Definitions::PlayerColor player, GameTimer::TimeParams& timeParams) 
		: KalahPlayer(player, timeParams) 
	{
			m_myName = "OmerMark"; 
			m_gameTimer = GameTimer(timeParams);
	}

	void initGame(int board_size, int stonesInHouse) {
		KalahPlayer::initGame(board_size, stonesInHouse);
		m_gameTimer.startGameTimer();
	}

	/* See KalahPlayer.h */
	void makeMove(const Board& curBoard, Move &myMove);

protected:
	
	/*
	 * Returns the value of the given board.
	 */
	virtual int utility(const KalahBoard& board) = 0;

private:

	/*
	 * Performs AlphaBeta search until the given depth. 
	 * The search continues until quiescence.
	 */
	OmerMarkAlphaBetaResults* alphaBetaSearch(
		const KalahBoard& board, int depth, Definitions::PlayerColor player);

	/* The critical amount of time: just enough to clean up and return the result. */
	static const double CRITICAL_TIME;

};

#endif