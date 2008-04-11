#ifndef _HEURISTICS_ENHANCED1_H
#define _HEURISTICS_ENHANCED1_H

#include "OmerMark_IHeuristics.h"

class Heuristics_Enhanced1 :
    public IHeuristics
{
public:
    Heuristics_Enhanced1() {};
    virtual ~Heuristics_Enhanced1() {}

    int getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor)
    {
	    int heuristics = 0;
	    heuristics += countPotentialStones(board.getHousesContents(playerColor));
	    heuristics += board.getStoreContents(playerColor);
	    heuristics -= countPotentialStones(board.getHousesContents(Definitions::getOppositePlayer(playerColor)));
	    heuristics -= board.getStoreContents(Definitions::getOppositePlayer(playerColor));
	    return heuristics;
    }

protected:
    int countPotentialStones(vector<int> houses) 
    {
	    int sum = 0;
	    for (int i = 0; i < (int)houses.size(); i++) {
		    if (houses[i] < (int)houses.size() - i) {
			    sum += houses[i];
		    }
	    }
	    return sum;
    }
};

#endif
