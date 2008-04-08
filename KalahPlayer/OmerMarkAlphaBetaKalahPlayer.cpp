#include "OmerMarkAlphaBetaKalahPlayer.h"
#include "OmerMarkOutOfTimeException.h"
#include <limits>
#include <iostream>

using std::cout;
using std::endl;
using std::numeric_limits;

#define __OMER_MARK_DEBUG__

/*
 * Performs iterative deepening AlphaBeta.
 */
void OmerMarkAlphaBetaKalahPlayer::makeMove(const Board &curBoard, Move &myMove)
{
	m_gameTimer.startMoveTimer();
	const KalahBoard& board = dynamic_cast<const KalahBoard&>(curBoard);
	KalahMove &move(dynamic_cast<KalahMove&>(myMove));
	try 
    {
        for (int depth = 1; depth < MAX_DEPTH_THRESHOLD; depth++)		
        {
			OmerMarkAlphaBetaResults results;
            alphaBetaSearch(board, depth, m_myColor, numeric_limits<int>::min(), 
                            numeric_limits<int>::max(),results);
			move.m_move = results.move.m_move;            
#ifdef __OMER_MARK_DEBUG__
            cout <<"depth: " << depth-1 << ", move: " << move.m_move << endl;
#endif
		}
	} 
    catch (OmerMarkOutOfTimeException* e) 
    {
#ifdef __OMER_MARK_DEBUG__
		cout << "Finito." << endl;
		cout << "Selected move is: " << move.m_move << endl << endl;
#endif
		delete e;
	}
}

void OmerMarkAlphaBetaKalahPlayer::alphaBetaSearch(
	    const KalahBoard&           board, 
        int                         depth, 
        Definitions::PlayerColor    player, 
        int                         _alpha, 
        int                         _beta, 
        OmerMarkAlphaBetaResults&   results) 
{
	if (m_gameTimer.getRemainingMoveTime() < CRITICAL_TIME) {
		throw new OmerMarkOutOfTimeException();
	}

	if ((board.getBoardResult() != KalahBoard::NOT_FINAL) || (depth <= 0)) {
        results = OmerMarkAlphaBetaResults(0, heuristics->getHeuristics(board, player));
        return;
	}

	int alpha = _alpha;
	int beta = _beta;
    results.move = 0;
    results.heuristicsVal = (player == m_myColor) ? numeric_limits<int>::min() : numeric_limits<int>::max();
	

	for (int i = m_boardSize; i > 0; i--) 
    {
		const KalahMove move(i);
		if (board.isLegalMove(m_myColor, move)) 
        {
			KalahBoard newBoard(board);
			newBoard.makeMove(player, move);
			
			OmerMarkAlphaBetaResults currentResults;
			if (newBoard.isLastStoneSowedInPlayerStore(player)) 
            {
                // even though we moving again, the depth search should be the same for both cases
				alphaBetaSearch(newBoard, depth , player, alpha, beta, currentResults);
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
}

const double OmerMarkAlphaBetaKalahPlayer::CRITICAL_TIME(0.0001);
const int    OmerMarkAlphaBetaKalahPlayer::MAX_DEPTH_THRESHOLD(100);
