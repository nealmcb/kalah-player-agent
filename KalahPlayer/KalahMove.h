/* KalahMove.h
 *
 * Concrete Move class for Kalah game.
 */
#ifndef __KALAH_MOVE_H__
#define __KALAH_MOVE_H__

class KalahMove : public Move
{
public:
	// Constructor
	// Empty constructor, assign invalid move for m_move
	KalahMove() : m_move(0) {};
	// Constructor
	// Assign move m to m_move, no checks
	KalahMove(int m) : m_move(m) {};
	// Destructor
	~KalahMove() {};

	int m_move;		// Player's move in player's row coordinates
};

#endif
