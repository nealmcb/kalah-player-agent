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
    
    double getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor)
    {
	    double Store = 0;
        double Distances = 0;

        Store += board.getStoreContents(playerColor);
	    Store -= board.getStoreContents(Definitions::getOppositePlayer(playerColor));

        Distances += countDistances(board.getHousesContents(playerColor));

// Not sure we should care about distances of opponent. Maybe we insert it normalized to some small value
// so it won't take much "weight" in the desicion.       
	    Distances -= countDistances(board.getHousesContents(Definitions::getOppositePlayer(playerColor)));

        return Store*StoreStonesWeight + Distances*DistanceWeight;
    }
protected:
    double StoreStonesWeight;
    double DistanceWeight;

    double countDistances(const vector<int>& houses)
    {
        int distances = 0;
        
        {
            for (unsigned int i = 0; i < houses.size(); ++i)
            {
                distances += houses[i]*(i + 1);
            }
        }

        return (double)distances;
    }

};

#endif
