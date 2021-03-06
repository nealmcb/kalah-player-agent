/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Project Name:                                                                       */
/*     AI - HW 2                                                                       */
/*                                                                                     */
/* OmerMark_Heuristics_Enhanced2.h                                                     */
/*     This file contains implementation of enhanced heuristic function 2nd generation */
/*                                                                                     */
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Author(s):                                                                          */
/*      Omer Levy                                                                      */
/*      Mark Lukoyanichev                                                              */
/*-------------------------------------------------------------------------------------*/

#ifndef _OMERMARK_HEURISTICS_ENHANCED2_H
#define _OMERMARK_HEURISTICS_ENHANCED2_H

#include <math.h>
#include "OmerMark_IHeuristics.h"

class OmerMark_Heuristics_Enhanced2 :
    public OmerMark_IHeuristics
{
public:
    OmerMark_Heuristics_Enhanced2(double _StoreStonesWeight = 1, double _DistanceWeight = 0):
                     StoreStonesWeight(_StoreStonesWeight),DistanceWeight(_DistanceWeight){}
    virtual ~OmerMark_Heuristics_Enhanced2() {};
    
    // The Heuristic function
    double getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor)
    {
	    double Store = 0;
        double Distances = 0;

        Store += board.getStoreContents(playerColor);
	    Store -= board.getStoreContents(Definitions::getOppositePlayer(playerColor));

        Distances += countDistances(board.getHousesContents(playerColor));      
	    Distances -= countDistances(board.getHousesContents(Definitions::getOppositePlayer(playerColor)));

        return Store*StoreStonesWeight + Distances*DistanceWeight;
    }
protected:
    double StoreStonesWeight;
    double DistanceWeight;

    double countDistances(const vector<int>& houses)
    {
        int distances = 0;
        
        for (unsigned int i = 0; i < houses.size(); ++i)
            distances += houses[i]*(i + 1);

        return (double)distances;
    }

};

#endif
