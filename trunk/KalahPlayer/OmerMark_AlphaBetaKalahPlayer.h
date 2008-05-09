/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Project Name:                                                                       */
/*     AI - HW 2                                                                       */
/*                                                                                     */
/* OmerMark_AlphaBetaPlayer.h                                                          */
/*     This file contains interface of our agent that implements                       */
/*     an iterative deepening version of the AlphaBeta algorithm                       */
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Author(s):                                                                          */
/*      Omer Levy                                                                      */
/*      Mark Lukoyanichev                                                              */
/*-------------------------------------------------------------------------------------*/

#ifndef __OMER_MARK_ALPHA_BETA_KALAH_PLAYER_H__
#define __OMER_MARK_ALPHA_BETA_KALAH_PLAYER_H__

#include "KalahPlayer.h"
#include "OmerMark_AlphaBetaResults.h"
#include "OmerMark_IHeuristics.h"
#include "OmerMark_Heuristics_Simple.h"
#include "OmerMark_Heuristics_Enhanced1.h"
#include "OmerMark_Heuristics_Enhanced2.h"

class OmerMarkAlphaBetaKalahPlayer : public KalahPlayer
{
public:

	/* Constructor. */
    OmerMarkAlphaBetaKalahPlayer(Definitions::PlayerColor player, GameTimer::TimeParams& timeParams, IHeuristics* _heuristics = 0) 
		: KalahPlayer(player, timeParams) 
	{
		m_myName = "OmerMark"; 
		m_gameTimer = GameTimer(timeParams);

        if (_heuristics == 0)         // using default values
        {
            heuristics = new Heuristics_Enhanced2(20, 1);
        }
        else
            heuristics = _heuristics;
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
		const KalahBoard& board, int depth, Definitions::PlayerColor player, double _alpha, double _beta, OmerMarkAlphaBetaResults& results);

	/* The critical amount of time: just enough to clean up and return the result. */
	static const double CRITICAL_TIME;
    
    /* Maximum depth search. */
    static const int    MAX_DEPTH_THRESHOLD;

};

#endif

