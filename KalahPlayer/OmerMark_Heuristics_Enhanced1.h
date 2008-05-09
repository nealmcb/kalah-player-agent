/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Project Name:                                                                       */
/*     AI - HW 2                                                                       */
/*                                                                                     */
/* OmerMark_Heuristics_Enhanced1.h                                                     */
/*     This file contains implementation of enhanced heuristic function 1st generation */
/*                                                                                     */
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Author(s):                                                                          */
/*      Omer Levy                                                                      */
/*      Mark Lukoyanichev                                                              */
/*-------------------------------------------------------------------------------------*/

#ifndef _HEURISTICS_ENHANCED1_H
#define _HEURISTICS_ENHANCED1_H

#include <iostream>
#include "OmerMark_IHeuristics.h"

using std::cout;

class Heuristics_Enhanced1 :
    public IHeuristics
{
public:
	Heuristics_Enhanced1(double _weight = 1) : weight(_weight) {};
    virtual ~Heuristics_Enhanced1() {}

    double getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor)
    {
	    double score = board.getStoreContents(playerColor) 
					 - board.getStoreContents(Definitions::getOppositePlayer(playerColor));

		vector<int> myHouses = board.getHousesContents(playerColor);

		double count = 0;
		int i = 1;
		for (vector<int>::reverse_iterator iterator = myHouses.rbegin(); iterator != myHouses.rend(); iterator++) {
			if (*iterator < i) {
			    count += *iterator;
				count++; // Bonus point for being under the limit.
			}
			i++;
	    }

		vector<int> opponentHouses = board.getHousesContents(Definitions::getOppositePlayer(playerColor));

		i = 1;
		for (vector<int>::iterator iterator = opponentHouses.begin(); iterator != opponentHouses.end(); iterator++) {
		    if (*iterator < i) {
			    count -= *iterator;
				count--; // Bonus point for being under the limit.
			}
			i++;
	    }

		return weight*score + (1 - weight)*count;
    }

	double weight;
};

#endif
