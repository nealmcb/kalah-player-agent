/* Definitions.h
 *
 * Global game definitions.
 */

#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

// The __KALAH_SYSTEM_DEBUG__ flag allows some debugging.
// It prints the board state before and after each move,
// print the current player and his move,
// and prints whether that move is legal, illegal or a timeout occurred,
// as well as capturing stones sequence and players turn sequences.

#define __KALAH_SYSTEM_DEBUG__

class Definitions
{
public:
	// Players' available colors.
	typedef enum{NONE, WHITE, BLACK} PlayerColor;

	// Get the opposite player of p.
	// p = WHITE returns BLACK
	// p = BLACK returns WHITE
	// p = NONE returns NONE
	static Definitions::PlayerColor getOppositePlayer(PlayerColor p);
};

#endif
