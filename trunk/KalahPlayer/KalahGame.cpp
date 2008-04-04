#include "KalahGame.h"
#include "KalahPlayer.h"

KalahGame::KalahGame(vector<Player*> players, double player_initGame_time_limit,
					 GameTimer::TimeParams timeParams,
					 int size, int stonesInHouse) : 
	Game(players, player_initGame_time_limit, timeParams), 
		m_size(size), m_stonesInHouse(stonesInHouse),
		m_WhiteNum(0), m_BlackNum(1), m_allowedPlayerInitialiationTime(10)
{
	m_board = new KalahBoard(m_size, m_stonesInHouse);
#ifdef __KALAH_SYSTEM_DEBUG__
	drawBoard();
#endif
};

KalahGame::~KalahGame()
{
};

void KalahGame::initGame()
{
	// Timer for initialization only. Game timer parameters are
	// set in the constructor.
	GameTimer::TimeParams tp;
	tp.timePerGame_limit = false;
	tp.timePerMove_limit = true;
	tp.timePerMove = m_allowedInitGamePlayersTime;
	GameTimer gt(tp);

	for(unsigned int i(0); i < m_Players.size(); ++i)
	{
		gt.startMoveTimer();
		(dynamic_cast<KalahPlayer*>(m_Players[i]))->initGame(m_size, m_stonesInHouse);
		if(gt.isMoveTimePassed())
			m_gameRes.players_result[i] = GameRes::TIMEOUT;
	};
	m_curPlayer = Definitions::WHITE;
};

bool KalahGame::isFinalState() const
{
	return (((dynamic_cast<KalahBoard*>(m_board))->getBoardResult()) != 
		KalahBoard::NOT_FINAL);
};

int KalahGame::getCurPlayer() const
{
	return m_curPlayer == Definitions::WHITE ? 0 : 1;
};

Definitions::PlayerColor KalahGame::getCurPlayerColor() const
{
	return m_curPlayer;
};

void KalahGame::makeMove(const Move &m)
{
	KalahBoard *kb(dynamic_cast<KalahBoard*>(m_board));
	kb->makeMove(m_curPlayer, (dynamic_cast<const KalahMove&>(m)));
	
	// current player gets another turn if last stone sowed landed in his store
	if(!(kb->isLastStoneSowedInPlayerStore(m_curPlayer)))
		m_curPlayer = Definitions::getOppositePlayer(m_curPlayer);
#ifdef __KALAH_SYSTEM_DEBUG__
	else
		printf("PLAYER GETS ANOTHER TURN\n");
#endif
};

Game::GameRes::ResType KalahGame::getPlayerResult(int player_num) const
{
	KalahBoard::BoardResult b((dynamic_cast<KalahBoard*>(m_board))->getBoardResult());

	switch(b)
	{
	case KalahBoard::NOT_FINAL:
		return Game::GameRes::NONE;
	case KalahBoard::DRAW:
		return Game::GameRes::DRAW;
	case KalahBoard::WIN_BLACK:
		if(player_num == m_WhiteNum)
			return Game::GameRes::NORMAL_LOSE;
		else
			return Game::GameRes::NORMAL_WIN;
	case KalahBoard::WIN_WHITE:
		if(player_num == m_WhiteNum)
			return Game::GameRes::NORMAL_WIN;
		else
			return Game::GameRes::NORMAL_LOSE;
	default:
		throw;
	};
};

Move *KalahGame::getEmptyMove() const
{
	return new KalahMove;
};

Board *KalahGame::getCurBoardCopy() const
{
	Board *boardCopy = new KalahBoard(*dynamic_cast<const KalahBoard*>(m_board));
	return boardCopy;
};

void KalahGame::drawBoard() const
{
	vector<string> playersNames;
	for(unsigned int i(0); i < m_Players.size(); ++i)
		playersNames.push_back(m_Players[i]->getName());

	m_board->drawBoard(playersNames);
};
