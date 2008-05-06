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
        bool capture = willWeCapture(newBoard, move);
		newBoard.makeMove(player, move);
		
		OmerMarkAlphaBetaResults currentResults;

        // this is last move and our move. we should check if this is interesting positions we
        // want to explore
        if ((depth == 1) && (player == m_myColor))
        {
            if (capture)    // if capture occured we want to explore 2 more moves
                alphaBetaSearch(newBoard, depth + 1, Definitions::getOppositePlayer(player), alpha, beta, currentResults);
        }
        else
        {
            if (newBoard.isLastStoneSowedInPlayerStore(player))
			    alphaBetaSearch(newBoard, depth - 1, player, alpha, beta, currentResults);
            else 
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

bool OmerMarkAlphaBetaKalahPlayer::willWeCapture(const KalahBoard& board, const KalahMove& move)
{
    vector<int> myHouse = board.getHousesContents(m_myColor);
    vector<int> opHouse = board.getHousesContents(Definitions::getOppositePlayer(m_myColor));

    if (myHouse[move.m_move -1] == 0)
        return false;

    // if we finish not in our house return
    if (myHouse[move.m_move - 1] > ((int)myHouse.size() - move.m_move))
        return false;
    // if we land in empty house and ops not empty - HOORAY!
    if ((myHouse[move.m_move - 1 + myHouse[move.m_move - 1]] == 0) &&
        (opHouse[move.m_move - 1 + myHouse[move.m_move - 1]] != 0))
        return true;
    
    return false;
        
}


const double OmerMarkAlphaBetaKalahPlayer::CRITICAL_TIME(0.001);
const int    OmerMarkAlphaBetaKalahPlayer::MAX_DEPTH_THRESHOLD(100);