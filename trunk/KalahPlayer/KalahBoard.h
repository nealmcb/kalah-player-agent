/* KalahBoard.h
 *
 * Concrete Board class for the Kalah game.
 */

#ifndef __KALAH_BOARD_H__
#define __KALAH_BOARD_H__

#include <vector>
#include "Board.h"
#include "KalahMove.h"

using std::vector;

class KalahBoard : public Board
{
public:
	// Board result state
	// WIN_x implies opposite_player(x) has lost
	typedef enum{NOT_FINAL, DRAW, WIN_BLACK, WIN_WHITE} BoardResult;

	// Constructor
	// Initializes the board with size houses for each players,
	// and stonesInHouse stones in each house
	KalahBoard(int size, int stonesInHouse);
	// Copy Constructor
	// Copies all game parameters, stones locations and last stone sowed place from kb
	KalahBoard(const KalahBoard &kb);

	// Returns true iff move m of player p is legal in the current board state
	bool isLegalMove(const Definitions::PlayerColor p, const Move& m) const;
	// Updates the board with move m of player p.
	// Not guarranteed to check if m is a legal move.
	// Applies all rules of Kalah: Sow stones, apply empty row rule,
	// records last stone sowed place (for later next-move-stays-same-player
	// applied by KalahGame::makeMove)
	void makeMove(const Definitions::PlayerColor p, const Move& m);
	// Outputs the current board state to the console, using playersNames
	// to describe players (their order in playersNames should correspond
	// to the order in which they are saved in the game class)
	void drawBoard(const vector<string> &playersNames) const;
	// Computes the current board result:
	// NOT_FINAL: There are stones in the houses rows of both players
	// DRAW: Not NOT_FINAL and the number of stones in each player's store is equal
	// WIN_WHITE: Not NOT_FINAL and WHITE has more stones in his store than BLACK
	// WIN_BLACK: Not NOT_FINAL and BLACK has more stones in his store than WHITE
	BoardResult getBoardResult() const;

	// Returns the number of stones in the store of player p
	int getStoreContents(Definitions::PlayerColor p) const;
	// Returns the number of stones in each house in the row of player p
	vector<int> getHousesContents(Definitions::PlayerColor p) const;

	// Returns true iff the last stone sowed by player p landed in player p's store
	// Returns invalid values if player p has not made a move yet,
	// or any player has made a move since the move which is to be checked
	bool isLastStoneSowedInPlayerStore(Definitions::PlayerColor p) const;

	// Returns the houses numbers in player p's row which are valid
	// successors for the current board state (i.e. contain stones)
	vector<int> getSuccessors(Definitions::PlayerColor p) const;

private:
	// Translates the move m of player p to internal representation
	int moveToBoardCoor(const Definitions::PlayerColor p, const KalahMove &m) const;
	// Returns internal representation of p's store place
	int getStorePlace(const Definitions::PlayerColor p) const;
	// Applies the empty row rule for player p:
	// If player p's row is empty, opposite(p) captures all the stones in
	// opposite(p)'s row
	void applyEmptyRowRule(Definitions::PlayerColor p);

private:
	int m_size;					// Board size: number of houses per player's row
	int m_stonesInHouse;		// Initial stones in each house
	int m_lastStoneSowedPlace;	// Place of last stone sowed in board coordinates
	vector<int> m_boardState;	// Number of stones in each house and store
								// [0 .. m_size-1] White houses [1..m_size]
								// [m_size] White store
								// [m_size+1 .. 2*m_size-2] Black houses [1..m_size]
								// [2*m_size-1] Black store
};

#endif
