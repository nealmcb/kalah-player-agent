/* KalahGame.h
 *
 * Concrete Game class for the Kalah game.
 */

#ifndef __KALAH_GAME_H__
#define __KALAH_GAME_H__

#include <time.h>
#include <vector>
#include "Definitions.h"
#include "KalahBoard.h"
#include "KalahMove.h"
#include "KalahPlayer.h"
#include "Game.h"

using std::vector;

class KalahGame : public Game
{
public:
	// Constructor
	// Inserts players into m_Players (from ::Game)
	// (player 0 is WHITE, player 1 is BLACK)
	// Records game and move parameters timeParams
	// Initializes game board with parameters size and stonesInHouse
	KalahGame(vector<Player*> players, double player_initGame_time_limit,
		GameTimer::TimeParams timeParams, int size, int stonesInHouse);
	// Destructor
	~KalahGame();

	// Initializes players (using their own initGame) and checks for
	// proper initialization time (of m_allowedPlayerInitialiationTime)
	void initGame();
	// Makes move m of current player m_curPlayer
	// Uses KalahBoard::makeMove, does not check for validity of the move
	// Checks board's last stone sowed place and grants the current player
	// an extra turn if it landed in his store.
	// Switches current player for next turn if the last stone sowed landed
	// elsewhere.
	void makeMove(const Move &m);
	// Gets the position of the current player in the players' vector
	int getCurPlayer() const;
	// Gets the current player's color
	Definitions::PlayerColor getCurPlayerColor() const;
	// Get the game result of player player_num, as reported by
	// KalahBoard::getBoardResult
	GameRes::ResType getPlayerResult(int player_num) const;
	// Returns an empty initialized KalahMove
	Move *getEmptyMove() const;
	// Returns a copy of the current board state
	Board *getCurBoardCopy() const;
	// Outputs the current board state to the console
	void drawBoard() const;

protected:
	// Returns true iff the board state is final
	// i.e. no stones in any of the players' house rows
	bool isFinalState() const;

	int m_size;								// Board size - number of houses per player
	int m_stonesInHouse;					// Initial stones in each house
	Definitions::PlayerColor m_curPlayer;	// Color of the current player

	const int m_WhiteNum;		// White player position in m_Players
	const int m_BlackNum;		// Black player position in m_Players
	const int m_allowedPlayerInitialiationTime; // seconds
};

#endif
