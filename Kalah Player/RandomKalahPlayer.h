/* RandomKalahPlayer.h
 *
 * Concrete KalahPlayer for Kalah game.
 *
 * This is a demo class and not an integral part of the game system.
 * You can use it as a basis to your implementation of the KalahPlayer.
 */

#ifndef __Random_Kalah_PLAYER_H__
#define __Random_Kalah_PLAYER_H__

#include "KalahPlayer.h"

class RandomKalahPlayer : public KalahPlayer
{
public:
	// Constructor
	// Initializes player's color and game/move timer
	RandomKalahPlayer(Definitions::PlayerColor playerColor,
		const GameTimer::TimeParams &tp);
	// Destructor
	// Does nothing
	~RandomKalahPlayer();

	// Reads the current board, requests a legal successors list,
	// places a random legal successor in myMove
	void makeMove(const Board& curBoard, Move &myMove);
	// Sets m_myName to s
	void setName(const string &s);
};

#endif
