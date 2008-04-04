/* Game.h
 *
 * An abstract game class.
 * Provides methods to play a board game between several players.
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>
#include <vector>
#include <string>
#include "Definitions.h"
#include "Board.h"
#include "Move.h"
#include "Player.h"
#include "GameTimer.h"

using std::vector;
using std::string;

class Game
{
public:
	// Game result
	typedef struct
	{
		// Possible results for players
		// NONE - no game result
		// DRAW, NORMAL_WIN, NORMAL_LOSE - normal end game result
		// WIN - player won because because of a technical lose of another player
		// TIMEOUT - technical lose, player timeout in game/move
		// ILLEGAL_MOVE - technical lose, player made an illegal move
		typedef enum{NONE, DRAW, NORMAL_WIN, NORMAL_LOSE, 
			WIN, TIMEOUT, ILLEGAL_MOVE} ResType;
		// Result vector of all players
		vector<ResType> players_result;
	} GameRes;

	// Constructor
	// Inserts the players in their order in the vector players to m_Players
	// Stores the allowed initGame time (in seconds) for each player
	// Initializes the internal game timer
	Game(vector<Player*> players, double player_initGame_time_limit,
		GameTimer::TimeParams timeParams);
	// Virtual destructor
	// Releases the internal players vector and their memory, releases the game board
	virtual ~Game();

	// Initializes the players with game parameters, 
	// initializes the game board using the derived game class
	virtual void initGame() = 0;
	// Plays the game between all players.
	// Records game result in m_gameRes
	virtual void playGame();
	// Get an empty initialized move from the derived game class
	virtual Move *getEmptyMove() const = 0;
	// Get a copy of the current board state from the derived game class
	virtual Board *getCurBoardCopy() const = 0;
	// Uses the derived game class to update the game board with move m
	// Not guarranteed to check if the move is legal
	virtual void makeMove(const Move &m) = 0;
	// Gets the current player from the derived game class
	virtual int getCurPlayer() const = 0;
	// Gets the current player's color from the derived game class
	virtual Definitions::PlayerColor getCurPlayerColor() const = 0;
	// Gets player_num's game result from the derived game class
	virtual GameRes::ResType getPlayerResult(int player_num) const = 0;
	// Outputs the current game board to the console
	virtual void drawBoard() const = 0;
	// Converts the current players' game result vector to printable form
	// Format is: playerName gameResult
	// gameResult uses the notation from the GameRes struct
	string ResultToString() const;
	// Converts the players' game result (as indicated by playersName[i]/gameRes[i]
	// pairs) to printable form
	// Format is: playerName gameResult
	// gameResult uses the notation from the GameRes struct
	static string ResultToString(const GameRes &gameRes,
		const vector<string> &playersNames);

protected:
	// Returns true iff the current game is in a final state
	virtual bool isFinalState() const = 0;

	Board *m_board;				// game board
	vector<Player*> m_Players;	// players classes
	GameRes m_gameRes;			// game result
	GameTimer m_gameTimer;		// game and move timer
	double m_allowedInitGamePlayersTime; // initGame player's time limit (in seconds)
};

#endif
