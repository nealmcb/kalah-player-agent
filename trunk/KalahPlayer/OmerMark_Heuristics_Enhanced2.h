#ifndef _HEURISTICS_ENHANCED2_H
#define _HEURISTICS_ENHANCED2_H

#include <math.h>
#include "OmerMark_IHeuristics.h"

class Heuristics_Enhanced2 :
    public IHeuristics
{
public:
    Heuristics_Enhanced2(double _StoreStonesWeight = 1, double _DistanceWeight = 0):
                     StoreStonesWeight(_StoreStonesWeight),DistanceWeight(_DistanceWeight){}
    virtual ~Heuristics_Enhanced2() {};
    
    int getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor)
    {
	    int Store = 0;
        int Distances = 0;

        Store += board.getStoreContents(playerColor);
	    Store -= board.getStoreContents(Definitions::getOppositePlayer(playerColor));

        Distances += countDistances(board.getHousesContents(playerColor), playerColor);

// Not sure we should care about distances of opponent. Maybe we insert it normalized to some small value
// so it won't take much "weight" in the desicion.       
//	    Distances -= countDistances(board.getHousesContents(Definitions::getOppositePlayer(playerColor)));

        return (int)(Store*StoreStonesWeight + Distances*DistanceWeight);
    }
protected:
    double StoreStonesWeight;
    double DistanceWeight;

    int countDistances(const vector<int>& houses, const Definitions::PlayerColor& color)
    {
        int distances = 0;
        
        if (color == Definitions::WHITE)
        {
            for (unsigned int i = 0; i < houses.size(); ++i)
            {
                distances += houses[i]*(i + 1);
            }
        }
        else
        {
            for (unsigned int i = 0; i < houses.size(); ++i)
            {
                distances += houses[i]*(houses.size()- i);
            }
        }
        return distances;
    }

};

#endif
