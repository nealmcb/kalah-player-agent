/* Player.h
 *
 * Abstract class for a player in a game.
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Definitions.h"
#include "Move.h"
#include "Board.h"
#include "GameTimer.h"
#include <string>

using std::string;

class Player
{
public:
	// Constructor
	// Initializes the player's copy of the game timer
	Player(const GameTimer::TimeParams &tp);
	// Destructor
	virtual ~Player() = 0;

	// Returns a move in myMove for the current player for the board 
	// given in curBoard
	virtual void makeMove(const Board& curBoard, Move &myMove) = 0;
	// Returns the player's name
	string getName() const;

protected:
	GameTimer m_gameTimer;	// Game/move timer
	string m_myName;		// Player's name
};

#endif
