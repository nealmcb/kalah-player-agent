#include "OmerMarkAlphaBetaKalahPlayer.h"
#include "OmerMarkOutOfTimeException.h"
#include <limits>
#include <stdio.h>

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
			printf("depth: %d move: %d \n", depth-1, move.m_move);
#endif
		}
	} catch (OmerMarkOutOfTimeException* e) {
#ifdef __OMER_MARK_DEBUG__
		printf("finito.\n");
		printf("move: %d \n", move.m_move);
#endif
		delete e;
	}
}

OmerMarkAlphaBetaResults* OmerMarkAlphaBetaKalahPlayer::alphaBetaSearch(
	const KalahBoard &board, int depth, Definitions::PlayerColor player, int _alpha, int _beta) 
{
	if (m_gameTimer.getRemainingMoveTime() < CRITICAL_TIME) {
		throw new OmerMarkOutOfTimeException();
	}

	if ((board.getBoardResult() != KalahBoard::NOT_FINAL) || (depth <= 0)) {
		return new OmerMarkAlphaBetaResults(0, utility(board));
	}

	int alpha = _alpha;
	int beta = _beta;
	int bestMove = 0;
	int bestUtility;
	if (player == m_myColor) {
		bestUtility = numeric_limits<int>::min();
	} else {
		bestUtility = numeric_limits<int>::max();
	}

	for (int i = m_boardSize; i > 0; i--) {
		const KalahMove move(i);
		if (board.isLegalMove(m_myColor, move)) {
			KalahBoard *newBoard = new KalahBoard(board);
			newBoard->makeMove(player, move);
			
			OmerMarkAlphaBetaResults *results;
			if (newBoard->isLastStoneSowedInPlayerStore(player)) {
				results = alphaBetaSearch(*newBoard, depth, player, alpha, beta);
			} else {
				results = alphaBetaSearch(*newBoard, depth - 1, Definitions::getOppositePlayer(player), alpha, beta);
			}

			if ((player == m_myColor) && (results->utility > bestUtility)) {
				bestUtility = results->utility;
				bestMove = i;
				if (alpha < bestUtility) {
					alpha = bestUtility;
				}
				if (beta <= bestUtility) {
					break;
				}
			} else if ((player != m_myColor) && (results->utility < bestUtility)) {
				bestUtility = results->utility;
				bestMove = i;
				if (beta > bestUtility) {
					beta = bestUtility;
				}
				if (alpha >= bestUtility) {
					break;
				}
			}

			delete results;
			delete newBoard;
		}
	}

	return new OmerMarkAlphaBetaResults(bestMove, bestUtility);
}

const double OmerMarkAlphaBetaKalahPlayer::CRITICAL_TIME(0.0016);
