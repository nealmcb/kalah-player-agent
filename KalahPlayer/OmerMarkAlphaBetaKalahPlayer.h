/*
 * An abstract class that implements an iterative deepening version of the AlphaBeta algorithm.
 * Any inheriting class should implement the utility method.
 */

#ifndef __OMER_MARK_ALPHA_BETA_KALAH_PLAYER_H__
#define __OMER_MARK_ALPHA_BETA_KALAH_PLAYER_H__

#include "KalahPlayer.h"
#include "OmerMarkAlphaBetaResults.h"
#include "IHeuristics.h"
#include "Heuristics_Simple.h"
#include "Heuristics_Enhanced1.h"

class OmerMarkAlphaBetaKalahPlayer : public KalahPlayer
{
public:

	/* Constructor. */
	OmerMarkAlphaBetaKalahPlayer(Definitions::PlayerColor player, GameTimer::TimeParams& timeParams) 
		: KalahPlayer(player, timeParams) 
	{
		m_myName = "OmerMark"; 
		m_gameTimer = GameTimer(timeParams);

        // Setting out Heuristics function
        heuristics = new Heuristics_Enhanced1();
	}

    // Destructor
    ~OmerMarkAlphaBetaKalahPlayer()
    {
        delete heuristics;
    }

	void initGame(int board_size, int stonesInHouse) {
		KalahPlayer::initGame(board_size, stonesInHouse);
		m_gameTimer.startGameTimer();
	}

	/* See KalahPlayer.h */
	void makeMove(const Board& curBoard, Move &myMove);

    void setName(const string &s) {m_myName = s;}


protected:
	
	/*
	 * Returns the value of the given board.
	 */
	IHeuristics* heuristics;

private:

	/*
	 * Performs AlphaBeta search until the given depth. 
	 * The search continues until quiescence.
	 */
	void alphaBetaSearch(
		const KalahBoard& board, int depth, Definitions::PlayerColor player, int _alpha, int _beta, OmerMarkAlphaBetaResults& results);

	/* The critical amount of time: just enough to clean up and return the result. */
	static const double CRITICAL_TIME;
    static const int    MAX_DEPTH_THRESHOLD;

};

#endif