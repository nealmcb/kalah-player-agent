/*
 * A smart implementation of AlphaBetaKalahPlayer.
 */

#ifndef __OMER_MARK_ENHANCED_KALAH_PLAYER_H__
#define __OMER_MARK_ENHANCED_KALAH_PLAYER_H__

#include "OmerMarkAlphaBetaKalahPlayer.h"

class OmerMarkEnhancedKalahPlayer : public OmerMarkAlphaBetaKalahPlayer
{
public:

	OmerMarkEnhancedKalahPlayer(Definitions::PlayerColor player, GameTimer::TimeParams& timerParams) 
		: OmerMarkAlphaBetaKalahPlayer(player, timerParams) {}

protected:

	/* See OmerMarkAlphaBetaKalahPlayer.h */
	int utility(const KalahBoard& board);

private:

	/* Counts the stones in each house if they are less than the house's distance to the store. */
	int countPotentialStones(vector<int> houses);

};

#endif