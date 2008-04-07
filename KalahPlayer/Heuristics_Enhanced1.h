#pragma once
#include "iheuristics.h"

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

private:
    int countPotentialStones(vector<int> houses) 
    {
	    int sum = 0;
	    for (int i = 0; i < houses.size(); i++) {
		    if (houses[i] < houses.size() - i) {
			    sum += houses[i];
		    }
	    }
	    return sum;
    }
};
