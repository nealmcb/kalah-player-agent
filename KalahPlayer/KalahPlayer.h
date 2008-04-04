/* KalahPlayer.h
 *
 * Abstract class for the Kalah game.
 */

#ifndef __KALAH_PLAYER_H__
#define __KALAH_PLAYER_H__

#include "Player.h"
#include "KalahMove.h"
#include "KalahBoard.h"
#include "GameTimer.h"

class KalahPlayer : public Player
{
public:
	// Constructor
	// Initializes player color m_myColor and game/move time parameters
	// which can be accessed through m_gameTimer (inherited from class Player)
	KalahPlayer(Definitions::PlayerColor playerColor, 
		const GameTimer::TimeParams &tp);
	// Destructor
	virtual ~KalahPlayer();

	// Initializes the game.
	// Called at the beginning of the game session.
	// Initializes m_boardSize and m_stonesInHouse to given values.
	virtual void initGame(int board_size, int stonesInHouse);

	// Computes a move based on the given board state.
	// Should cast myMove to KalahMove and store the move value in
	// player's own house row coordinates (range [1..m_boardSize]
	virtual void makeMove(const Board& curBoard, Move &myMove) = 0;

protected:
	int m_boardSize;		// Board size - number of houses in player's row
	int m_stonesInHouse;	// Initial stones in each player's house
	Definitions::PlayerColor m_myColor;	// This player's color
};

#endif
