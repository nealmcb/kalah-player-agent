#include "Definitions.h"
#include "RandomKalahPlayer.h"

RandomKalahPlayer::RandomKalahPlayer(Definitions::PlayerColor playerColor,
									 const GameTimer::TimeParams &tp)
: KalahPlayer(playerColor,tp)
{
    srand((unsigned int)time(0));
};

RandomKalahPlayer::~RandomKalahPlayer()
{
};

int RandInt(int range)
{
	return (int)((rand()/(double)RAND_MAX) * (range-1) + 1.5);
}

void RandomKalahPlayer::makeMove(const Board& curBoard, Move &myMove)
{
	KalahMove &km(dynamic_cast<KalahMove&>(myMove));
	const KalahBoard &kb(dynamic_cast<const KalahBoard&>(curBoard));

	vector<int> succ(kb.getSuccessors(m_myColor));
	km.m_move = succ[RandInt(succ.size())-1];
	
#ifdef __KALAH_SYSTEM_DEBUG__
	printf("Move: %s (%d)\n", m_myColor == Definitions::WHITE ? "WHITE" : "BLACK",
		km.m_move);
#endif
};

void RandomKalahPlayer::setName(const string &s)
{
	m_myName = s;
};
