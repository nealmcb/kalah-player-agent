#include "OmerMark_AlphaBetaKalahPlayer.h"
#include "OmerMark_OutOfTimeException.h"
#include <limits>
#include <iostream>
#include <set>
#include <algorithm>

using std::cout;
using std::endl;
using std::numeric_limits;
using std::set;

//#define __OMER_MARK_DEBUG__

/*
 * Performs iterative deepening AlphaBeta.
 */
void OmerMarkAlphaBetaKalahPlayer::makeMove(const Board &curBoard, Move &myMove)
{
	m_gameTimer.startMoveTimer();
	const KalahBoard& board = dynamic_cast<const KalahBoard&>(curBoard);
	KalahMove &move(dynamic_cast<KalahMove&>(myMove));
    

#ifdef __OMER_MARK_DEBUG__
    cout << this->m_myName << " making a move!" << endl;
#endif

    try 
    {
        for (int depth = 1; depth < MAX_DEPTH_THRESHOLD; depth++)		
        {
			OmerMarkAlphaBetaResults results;
            alphaBetaSearch(board, depth, m_myColor, numeric_limits<int>::min(), 
                            numeric_limits<int>::max(),results);
            move.m_move = results.move.m_move;   

#ifdef __OMER_MARK_DEBUG__
            cout <<"depth: " << depth << ", move: " << move.m_move << endl;            
#endif
		}
	} 
    catch (...) 
    {
        //move.m_move = results.move.m_move;   
#ifdef __OMER_MARK_DEBUG__
		cout << "Finito." << endl;
		cout << "Selected move is: " << move.m_move << endl << endl;
#endif
	}
}


void OmerMarkAlphaBetaKalahPlayer::alphaBetaSearch(
	    const KalahBoard&           board, 
        int                         depth, 
        Definitions::PlayerColor    player, 
        double                      _alpha, 
        double                      _beta, 
        OmerMarkAlphaBetaResults&   results) 
{
	if (m_gameTimer.getRemainingMoveTime() < CRITICAL_TIME) {
		throw OmerMarkOutOfTimeException();
	}

	if ((board.getBoardResult() != KalahBoard::NOT_FINAL) || (depth <= 0)) {
        results = OmerMarkAlphaBetaResults(0, heuristics->getHeuristics(board, m_myColor));
        return;
	}

	double alpha = _alpha;
	double beta  = _beta;
    bool firstMoveSelected  =  false;
    results.move = 0;
    results.heuristicsVal = (player == m_myColor) ? numeric_limits<int>::min() : numeric_limits<int>::max();

    // Getting all legal moves for the player who is currently playing
    vector<int> legalMoves = board.getSuccessors(player);

    for (vector<int>::iterator itr = legalMoves.begin(); itr != legalMoves.end(); ++itr)
    {
        int i = *itr;
		const KalahMove move(i);
        if (!firstMoveSelected)
        {
            // selecting first legal move to minimize the chance of returning ilegal move = 0
            results.move = i;
            firstMoveSelected = true;
        }

		KalahBoard newBoard(board);
		newBoard.makeMove(player, move);
		
		OmerMarkAlphaBetaResults currentResults;
		if (newBoard.isLastStoneSowedInPlayerStore(player)) 
        {
            // This is interesting board position - we would like to explore more deeply into this
            // direction.
			alphaBetaSearch(newBoard, depth - 1 + QuiescenceBonus, player, alpha, beta, currentResults);
		} 
        else 
        {
			alphaBetaSearch(newBoard, depth - 1, Definitions::getOppositePlayer(player), alpha, beta, currentResults);
		}

        if ((player == m_myColor) && (currentResults.heuristicsVal > results.heuristicsVal)) 
        {
			results.heuristicsVal = currentResults.heuristicsVal;
			results.move = i;
			if (alpha < results.heuristicsVal) {
				alpha = results.heuristicsVal;
			}
			if (beta <= results.heuristicsVal) {
				break;
			}
		}             
        else if ((player != m_myColor) && (currentResults.heuristicsVal < results.heuristicsVal)) 
        {
			results.heuristicsVal = currentResults.heuristicsVal;
			results.move = i;
			if (beta > results.heuristicsVal) {
				beta = results.heuristicsVal;
			}
			if (alpha >= results.heuristicsVal) {
				break;
			}
		}
	}
}

const double OmerMarkAlphaBetaKalahPlayer::CRITICAL_TIME(0.001);
const int    OmerMarkAlphaBetaKalahPlayer::MAX_DEPTH_THRESHOLD(100);
const int    OmerMarkAlphaBetaKalahPlayer::QuiescenceBonus(1);
const double OmerMarkAlphaBetaKalahPlayer::MaxTimeForSimpleHeuristics(0.1);