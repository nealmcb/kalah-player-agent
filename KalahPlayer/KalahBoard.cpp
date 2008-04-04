#include "KalahBoard.h"
#include "KalahMove.h"
#include <cstdio>

KalahBoard::KalahBoard(const KalahBoard &kb)
{
	if(&kb != this)
	{
		m_size = kb.m_size;
		m_stonesInHouse = kb.m_stonesInHouse;
		m_boardState = kb.m_boardState;
		m_lastStoneSowedPlace = kb.m_lastStoneSowedPlace;
	};
};

KalahBoard::KalahBoard(int size, int stonesInHouse)
{
	m_size = size;
	m_stonesInHouse = stonesInHouse;
	m_boardState.resize(size*2+2);
	// set stores to initial value: 0
	m_boardState[getStorePlace(Definitions::WHITE)] = 
		m_boardState[getStorePlace(Definitions::BLACK)] = 0;
	for(int i(1); i <= m_size; ++i)
	{
		m_boardState[moveToBoardCoor(Definitions::BLACK, KalahMove(i))] = m_stonesInHouse;
		m_boardState[moveToBoardCoor(Definitions::WHITE, KalahMove(i))] = m_stonesInHouse;
	};
};

int KalahBoard::moveToBoardCoor(const Definitions::PlayerColor p, const KalahMove &m) const
{
	return p == Definitions::WHITE ? m.m_move - 1 : m.m_move - 1 + m_size + 1;
};

bool KalahBoard::isLegalMove(const Definitions::PlayerColor p, const Move& m) const
{
	const KalahMove &km(dynamic_cast<const KalahMove&>(m));
	if((km.m_move < 1) || (km.m_move > m_size))
		return false;

	return (m_boardState[moveToBoardCoor(p, km)] > 0);
};

void KalahBoard::makeMove(const Definitions::PlayerColor p, const Move& m)
{
	const KalahMove &km(dynamic_cast<const KalahMove&>(m));

	int startCoor(moveToBoardCoor(p, km));
	int stonesToSow = m_boardState[startCoor];
	int endCoor = (startCoor + stonesToSow) % m_boardState.size();
	int endCoorOwnHouseCoordinate = (km.m_move + stonesToSow) % m_boardState.size();
	bool landInOwnHouse((endCoorOwnHouseCoordinate >= 1) && 
		(endCoorOwnHouseCoordinate <= m_size));

	m_boardState[startCoor] = 0;
	for(int i(startCoor+1); stonesToSow > 0; 
		i = (i + 1) % m_boardState.size(), --stonesToSow)
		++m_boardState[i];

	int endCoorStones = m_boardState[endCoor];

	if((landInOwnHouse)				// last stone was put in player's house
		&& (endCoorStones == 1))	// last stone was put in an empty house
	{
		int endCoorOpposite = m_boardState.size() - endCoor - 1 - 1;
		int endCoorStonesOpposite = m_boardState[endCoorOpposite];
		if(endCoorStonesOpposite > 0)
		{
#ifdef __KALAH_SYSTEM_DEBUG__
			printf("CAPTURING STONES\n");
			vector<string> tnames;
			tnames.push_back("WHITE");
			tnames.push_back("BLACK");
			drawBoard(tnames);
			printf(" || \n || \n\\  /\n \\/\n");
#endif
			m_boardState[getStorePlace(p)] = getStoreContents(p) +
				endCoorStones + endCoorStonesOpposite;
			m_boardState[endCoor] = 0;
			m_boardState[endCoorOpposite] = 0;
		};
	};

	m_lastStoneSowedPlace = endCoor;

	applyEmptyRowRule(p);
	applyEmptyRowRule(Definitions::getOppositePlayer(p));
};

void KalahBoard::applyEmptyRowRule(Definitions::PlayerColor p)
{
	vector<int> playerStonesV(getHousesContents(p));
	bool curPlayerHasNoStones(true);
	for(int i(0); i < m_size; ++i)
	{
		if(playerStonesV[i] > 0)
		{
			curPlayerHasNoStones = false;
			break;
		};
	};

	if(curPlayerHasNoStones)
	{
		Definitions::PlayerColor opponent(Definitions::getOppositePlayer(p));
		int opponentStorePlace = getStorePlace(opponent);
		for(int i(1); i <= m_size; ++i)
		{
			int curPos(moveToBoardCoor(opponent, KalahMove(i)));
			m_boardState[opponentStorePlace] += m_boardState[curPos];
			m_boardState[curPos] = 0;
		};
	};
};

KalahBoard::BoardResult KalahBoard::getBoardResult() const
{
	BoardResult res;

	bool isFinal(false);
	int whiteOpenStones(0), blackOpenStones(0);
	vector<int> whiteStonesV(getHousesContents(Definitions::WHITE)),
		 blackStonesV(getHousesContents(Definitions::BLACK));
	for(int i(0); i < m_size; ++i)
	{
		whiteOpenStones += whiteStonesV[i];
		blackOpenStones += blackStonesV[i];
	};
	if((whiteOpenStones == 0) || (blackOpenStones == 0))
		isFinal = true;

	int whiteStore = getStoreContents(Definitions::WHITE);
	int blackStore = getStoreContents(Definitions::BLACK);
	if(isFinal)
	{
		if(whiteStore == blackStore)
			res = KalahBoard::DRAW;
		else
			res = whiteStore > blackStore ?
				KalahBoard::WIN_WHITE : 
				KalahBoard::WIN_BLACK;
	}
	else
		res = KalahBoard::NOT_FINAL;
	
	return res;
};

void KalahBoard::drawBoard(const vector<string> &playersNames) const
{
	// player 0 - white
	// player 1 - black
	vector<int> whiteStonesV(getHousesContents(Definitions::WHITE)),
		 blackStonesV(getHousesContents(Definitions::BLACK));

	printf("%8s ", playersNames[1].c_str());
	for(int i(m_size-1); i >= 0; --i)
		printf("%5d", blackStonesV[i]);
	printf("\n");
	printf("%8d", getStoreContents(Definitions::BLACK));
	for(int i(0); i < m_size; ++i)
		printf("%5s", "");
	printf("%8d", getStoreContents(Definitions::WHITE));
	printf("\n");
	printf("%8s", "");
	for(int i(0); i < m_size; ++i)
		printf("%5d", whiteStonesV[i]);
	printf("%8s ", playersNames[0].c_str());
	printf("\n");
};

int KalahBoard::getStoreContents(Definitions::PlayerColor p) const
{
	switch(p)
	{
	case Definitions::WHITE:
		return m_boardState[getStorePlace(Definitions::WHITE)];
	case Definitions::BLACK:
		return m_boardState[getStorePlace(Definitions::BLACK)];
	default:
		throw;
		return -1;
	};
};

vector<int> KalahBoard::getHousesContents(Definitions::PlayerColor p) const
{
	vector<int> v;
	int start(moveToBoardCoor(p, KalahMove(1)));
	for(int i(start); i < start+m_size; ++i)
		v.push_back(m_boardState[i]);
	return v;
};

int KalahBoard::getStorePlace(const Definitions::PlayerColor p) const
{
	switch(p)
	{
	case Definitions::WHITE:
		return m_size;
	case Definitions::BLACK:
		return 2*m_size+1;
	default:
		throw;
		return -1;
	};
};

bool KalahBoard::isLastStoneSowedInPlayerStore(Definitions::PlayerColor p) const
{
	switch(p)
	{
	case Definitions::WHITE:
		return m_lastStoneSowedPlace == getStorePlace(Definitions::WHITE);
	case Definitions::BLACK:
		return m_lastStoneSowedPlace == getStorePlace(Definitions::BLACK);
	default:
		throw;
		return false;
	};
};

vector<int> KalahBoard::getSuccessors(Definitions::PlayerColor p) const
{
	vector<int> v;
	for(int i(1); i <= m_size; ++i)
	{
		if(isLegalMove(p, KalahMove(i)))
			v.push_back(i);
	};

	return v;
};
