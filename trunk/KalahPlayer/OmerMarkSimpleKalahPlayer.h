/*
 * A simple implementation of AlphaBetaKalahPlayer.
 */

#ifndef __OMER_MARK_SIMPLE_KALAH_PLAYER_H__
#define __OMER_MARK_SIMPLE_KALAH_PLAYER_H__

#include "OmerMarkAlphaBetaKalahPlayer.h"

class OmerMarkSimpleKalahPlayer : public OmerMarkAlphaBetaKalahPlayer
{
public:

	OmerMarkSimpleKalahPlayer(Definitions::PlayerColor player, GameTimer::TimeParams& timerParams) 
		: OmerMarkAlphaBetaKalahPlayer(player, timerParams) {}

protected:

	/* See OmerMarkAlphaBetaKalahPlayer.h */
	int utility(const KalahBoard& board);

};

#endif