#include "Game.h"

Game::Game(vector<Player*> players, double player_initGame_time_limit,
		   GameTimer::TimeParams timeParams) :
m_Players(players), m_board(0), m_gameTimer(timeParams),
m_allowedInitGamePlayersTime(player_initGame_time_limit)
{
};

Game::~Game()
{
	for(unsigned int i(0); i < m_Players.size(); ++i)
		delete m_Players[i];
	delete m_board;
};

void Game::playGame()
{
	m_gameRes.players_result.resize(m_Players.size());
	for(unsigned int i(0); i < m_Players.size(); ++i)
		m_gameRes.players_result[i] = GameRes::NONE;

	this->initGame();

	int numPlayersStanding(m_Players.size());
	// check for players with bad initializations
	for(unsigned int i(0); i < m_Players.size(); ++i)
		if(m_gameRes.players_result[i] != GameRes::NONE)
			--numPlayersStanding;

	while(!isFinalState() && (numPlayersStanding>1))
	{
		int curPlayer = this->getCurPlayer();
		Board * boardCopy = this->getCurBoardCopy();
		Move * playerMove(this->getEmptyMove());
		m_gameTimer.startMoveTimer();
		m_Players[curPlayer]->makeMove(*boardCopy, *playerMove);
		if(m_gameTimer.isMoveTimePassed())
		{
#ifdef __KALAH_SYSTEM_DEBUG__
			printf("TIMEOUT\n");
#endif
			m_gameRes.players_result[curPlayer] = GameRes::TIMEOUT;
		}
		else if(m_board->isLegalMove(this->getCurPlayerColor(), *playerMove))
		{
			// this-> knows which player should play next
			this->makeMove(*playerMove);
#ifdef __KALAH_SYSTEM_DEBUG__
			printf("LEGAL\n");
			this->drawBoard();
#endif
		}
		else
		{
#ifdef __KALAH_SYSTEM_DEBUG__
			printf("ILLEGAL\n");
#endif
			m_gameRes.players_result[curPlayer] = GameRes::ILLEGAL_MOVE;
		};
		delete playerMove;
		delete boardCopy;

		int lastPlayerStanding(-1);
		numPlayersStanding = 0;
		for(unsigned int i(0); i < m_Players.size(); ++i)
		{
			if(m_gameRes.players_result[i] == GameRes::NONE)
			{
				lastPlayerStanding = i;
				++numPlayersStanding;
			}
		};
		if(numPlayersStanding == 1)
			m_gameRes.players_result[lastPlayerStanding] = GameRes::WIN;
	};

#ifdef __KALAH_SYSTEM_DEBUG__
	printf("FINAL\n");
	this->drawBoard();
#endif

	for(unsigned int i(0); i < m_Players.size(); ++i)
	{
		if(m_gameRes.players_result[i] == GameRes::NONE)
			m_gameRes.players_result[i] = getPlayerResult(i);
	};
};

string Game::ResultToString() const
{
	vector<string> playersNames;
	for(unsigned int i(0); i < m_Players.size(); ++i)
		playersNames.push_back(m_Players[i]->getName());
	return ResultToString(m_gameRes, playersNames);
};

string Game::ResultToString(const GameRes &gameRes,
							const vector<string> &playersNames)
{
	string resStr = "";
	for(unsigned  int i(0); i < gameRes.players_result.size(); ++i)
	{
		resStr += playersNames[i] + " ";
		switch(gameRes.players_result[i])
		{
		case Game::GameRes::NORMAL_WIN:
			resStr += string("NORMAL_WIN") + string("\t");
			break;
		case Game::GameRes::NORMAL_LOSE:
			resStr += string("NORMAL_LOSE") + string("\t");
			break;
		case Game::GameRes::WIN:
			resStr += string("WIN") + string("\t");
			break;
		case Game::GameRes::TIMEOUT:
			resStr += string("TIMEOUT") + string("\t");
			break;
		case Game::GameRes::ILLEGAL_MOVE:
			resStr += string("ILLEGAL_MOVE") + string("\t");
			break;
		};
	};
	return resStr;
};
