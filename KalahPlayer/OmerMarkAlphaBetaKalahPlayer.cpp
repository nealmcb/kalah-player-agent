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
	int depth = 1;
	try {
		while (true) {
			OmerMarkAlphaBetaResults *results = alphaBetaSearch(
				board, depth, m_myColor, numeric_limits<int>::min(), numeric_limits<int>::max());
			move.m_move = results->move.m_move;
			delete results;
			depth++;
#ifdef __OMER_MARK_DEBUG__
            cout <<"depth: " << depth-1 << ", move: " << move.m_move << endl;
#endif
		}
	} catch (OmerMarkOutOfTimeException* e) {
#ifdef __OMER_MARK_DEBUG__
		cout << "Finito." << endl;
		cout << "Selected move is: " << move.m_move << endl << endl;
#endif
		delete e;
	}
}

OmerMarkAlphaBetaResults* OmerMarkAlphaBetaKalahPlayer::alphaBetaSearch(
	const KalahBoard &board, int depth, Definitions::PlayerColor player, int _alpha, int _beta) 
{
    if (depth > 100)
    {
        cout << "Something Fishy" <<endl;
        vector<string> names;
        names.push_back("A");
        names.push_back("B");
        int x = 1000;
        board.drawBoard(names);
        cout << "Player is " << player << endl;
        cout << "Alpha = " << _alpha << endl;
        cout << "Beta  = " << _beta << endl;
    }

	if (m_gameTimer.getRemainingMoveTime() < CRITICAL_TIME) {
		throw new OmerMarkOutOfTimeException();
	}

	if ((board.getBoardResult() != KalahBoard::NOT_FINAL) || (depth <= 0)) {
        return new OmerMarkAlphaBetaResults(0, heuristics->getHeuristics(board, player));
	}

	int alpha = _alpha;
	int beta = _beta;
	int bestMove = 0;
    int bestHeuristics = (player == m_myColor) ? numeric_limits<int>::min() : numeric_limits<int>::max();
	

	for (int i = m_boardSize; i > 0; i--) 
    {
		const KalahMove move(i);
		if (board.isLegalMove(m_myColor, move)) 
        {
			KalahBoard *newBoard = new KalahBoard(board);
			newBoard->makeMove(player, move);
			
			OmerMarkAlphaBetaResults *results;
			if (newBoard->isLastStoneSowedInPlayerStore(player)) 
            {
				results = alphaBetaSearch(*newBoard, depth, player, alpha, beta);
			} 
            else 
            {
				results = alphaBetaSearch(*newBoard, depth - 1, Definitions::getOppositePlayer(player), alpha, beta);
			}

            if ((player == m_myColor) && (results->heuristicsVal > bestHeuristics)) 
            {
				bestHeuristics = results->heuristicsVal;
				bestMove = i;
				if (alpha < bestHeuristics) {
					alpha = bestHeuristics;
				}
				if (beta <= bestHeuristics) {
					break;
				}
			}             
            else if ((player != m_myColor) && (results->heuristicsVal < bestHeuristics)) 
            {
				bestHeuristics = results->heuristicsVal;
				bestMove = i;
				if (beta > bestHeuristics) {
					beta = bestHeuristics;
				}
				if (alpha >= bestHeuristics) {
					break;
				}
			}

			delete results;
			delete newBoard;
		}
	}

	return new OmerMarkAlphaBetaResults(bestMove, bestHeuristics);
}

const double OmerMarkAlphaBetaKalahPlayer::CRITICAL_TIME(0.0016);
