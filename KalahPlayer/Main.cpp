#include "Definitions.h"
#include "KalahGame.h"
#include "RandomKalahPlayer.h"
#include "OmerMark_AlphaBetaKalahPlayer.h"
#include "GameTimer.h"

#include <iostream>
#include <cstdlib>

using namespace std;

// Game parameters defaults
const int default_board_size(6);	// Board size - number of houses per player's row
const int default_stones_in_house(3);	// Initial number of stones per house
const double default_time_per_move(1);	// Time per player's turn (in seconds)
const double default_time_for_constructing(1);	// Time for player's constructor
const double default_time_for_initialization(10);	// Time for player's initGame

// Globals for replacing default values with command line parameters
int board_size(default_board_size);
int stones_in_house(default_stones_in_house);
double time_per_move(default_time_per_move);

// Parse command line
// -size		Board size
// -stones		Initial stones in house
// -time		Time per game move
bool ProcessCommandLine(int argc, char **argv);

// Output command line parameters' description
void PrintHelpMessage(char **argv);

int main(int argc, char **argv)
{
	// Read game parameters from command line, if any
	// Game uses defaults for any command line parameter not specified
	if(!ProcessCommandLine(argc, argv))
	{
		PrintHelpMessage(argv);
		return 1;
	};

	// Game/move parameters
	GameTimer::TimeParams tp;
	tp.timePerGame_limit = false;
	tp.timePerMove_limit = true;
	tp.timePerMove = time_per_move;

	// Players construction
	// (initialization with game parameters is done as the first task
	// of KalahGame::playGame)
	bool Player1_bad_init(false), Player2_bad_init(false);
	// Time limits for construction, using timer's move limit
	GameTimer::TimeParams init_tp;
	init_tp.timePerGame_limit = false;
	init_tp.timePerMove_limit = true;
	init_tp.timePerMove = default_time_for_constructing;
	GameTimer init_timer(init_tp);


    // Constructing first player
	// It is white and will play first
	init_timer.startMoveTimer();
    Player *p1 = new OmerMarkAlphaBetaKalahPlayer(Definitions::WHITE, tp, new Heuristics_Enhanced1());
	(dynamic_cast<OmerMarkAlphaBetaKalahPlayer*>(p1))->setName("Enhanced1");
	if(init_timer.isMoveTimePassed())
		Player1_bad_init = true;

	// Constructing second player
	// It is black and will play second
	init_timer.startMoveTimer();
    Player *p2 = new OmerMarkAlphaBetaKalahPlayer(Definitions::BLACK, tp, new Heuristics_Simple());
	(dynamic_cast<OmerMarkAlphaBetaKalahPlayer*>(p2))->setName("Simple");
	if(init_timer.isMoveTimePassed())
		Player2_bad_init = true;
	
	// Check whether any player used too much time during construction
	if(Player1_bad_init || Player2_bad_init)
	{
		vector<string> playersNames;
		playersNames.push_back(p1->getName());
		playersNames.push_back(p2->getName());

		// Compute game results (premature termination - technical lose)
		Game::GameRes gameRes;
		gameRes.players_result.resize(2);

		if(Player1_bad_init)
			// Player 1 timeout
			gameRes.players_result[0] = Game::GameRes::TIMEOUT;
		else
			// Player 1 OK, player 2 timeout ==> Player 1 wins
			gameRes.players_result[0] = Game::GameRes::WIN;

		if(Player2_bad_init)
			// Player 2 timeout
			gameRes.players_result[1] = Game::GameRes::TIMEOUT;
		else
			// Player 2 OK, player 1 timeout ==> Player 2 wins
			gameRes.players_result[1] = Game::GameRes::WIN;

		delete p1;
		delete p2;

		// Output game result to the console
		cout << Game::ResultToString(gameRes, playersNames) << endl;
		// Exit program
		return 0;
	}

	// Players' construction went fine, start a game
	vector<Player*> players;
	players.push_back(p1);
	players.push_back(p2);

	// Initialize game
	KalahGame kg(players, default_time_for_initialization,
		tp, board_size, stones_in_house);

	// Play game
	kg.playGame();

	// Output game result to the console
	cout << kg.ResultToString() << endl;

	return 0;
};

bool ProcessCommandLine(int argc, char **argv)
{
	bool errorEncountered(false);

	for(int i(1); (i < argc) && !errorEncountered; ++i)
	{
		if(string(argv[i]) == "-h")
		{
			errorEncountered = true;
		}
		else if(string(argv[i]) == "-size")
		{
			errno = 0;
			board_size = atoi(argv[++i]);
			if(board_size < 1)
				errorEncountered = true;
		}
		else if (string(argv[i]) == "-stones")
		{
			errno = 0;
			stones_in_house = atoi(argv[++i]);
			if(stones_in_house < 0)
				errorEncountered = true;
		}
		else if(string(argv[i]) == "-time")
		{
			errno = 0;
			time_per_move = atof(argv[++i]);
			if(time_per_move <= 0)
				errorEncountered = true;
		}
		else
		{
			errorEncountered = true;
		};
		if(errno != 0)
			errorEncountered = true;
	};
	
	return !errorEncountered;
};

void PrintHelpMessage(char **argv)
{
	cout << "Arguments for " << argv[0] << " :" << endl;
	cout 
		<< "\t -size <board size> (default: 6)" << endl
		<< "\t -stones <initial stones in each house> (default: 3)" << endl
		<< "\t -time <time limit per move, in seconds> (default: 1.0)" << endl
		;
};
