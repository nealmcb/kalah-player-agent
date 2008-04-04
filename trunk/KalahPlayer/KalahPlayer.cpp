#include "KalahPlayer.h"
#include "KalahGame.h"

KalahPlayer::KalahPlayer(Definitions::PlayerColor playerColor,
						 const GameTimer::TimeParams &tp)
: Player(tp), m_myColor(playerColor)
{
};

KalahPlayer::~KalahPlayer()
{
};

void KalahPlayer::initGame(int board_size, int stonesInHouse)
{
	m_boardSize = board_size;
	m_stonesInHouse = stonesInHouse;
};
