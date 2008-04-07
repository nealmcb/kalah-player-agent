#include "OmerMarkAlphaBetaKalahPlayer.h"
#include "OmerMarkOutOfTimeException.h"
#include <limits>
#include <stdio.h>

using std::numeric_limits;

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
			OmerMarkAlphaBetaResults *results = alphaBetaSearch(board, depth, m_myColor);
			move.m_move = results->move.m_move;
			delete results;
			depth++;
		}
	} catch (OmerMarkOutOfTimeException* e) {
		delete e;
	}
}

OmerMarkAlphaBetaResults* OmerMarkAlphaBetaKalahPlayer::alphaBetaSearch(
	const KalahBoard &board, int depth, Definitions::PlayerColor player) 
{
	if (m_gameTimer.getRemainingMoveTime() < CRITICAL_TIME) {
		throw new OmerMarkOutOfTimeException();
	}

	if ((board.getBoardResult() != KalahBoard::NOT_FINAL) || (depth <= 0)) {
		return new OmerMarkAlphaBetaResults(0, utility(board));
	}

	int bestMove = 0;
	int bestUtility = numeric_limits<int>::min();

	for (int i = m_boardSize; i > 0; i--) {
		KalahMove move(i);
		if (board.isLegalMove(m_myColor, move)) {
			KalahBoard *newBoard = new KalahBoard(board);
			newBoard->makeMove(player, move);
			
			OmerMarkAlphaBetaResults *results;
			if (newBoard->isLastStoneSowedInPlayerStore(player)) {
				results = alphaBetaSearch(*newBoard, depth, player);
			} else {
				results = alphaBetaSearch(*newBoard, depth - 1, Definitions::getOppositePlayer(player));
			}
			
			if (player == m_myColor ? 
					results->utility > bestUtility : 
					results->utility < bestUtility) {

				bestUtility = results->utility;
				bestMove = i;
			}

			delete results;
			delete newBoard;
		}
	}

	return new OmerMarkAlphaBetaResults(bestMove, bestUtility);
}

const double OmerMarkAlphaBetaKalahPlayer::CRITICAL_TIME(0.001);
