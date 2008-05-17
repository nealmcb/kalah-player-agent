/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Project Name:                                                                       */
/*     AI - HW 2                                                                       */
/*                                                                                     */
/* OmerMark_Heuristics_Simple.h                                                        */
/*     This file contains implementation of simple heuristic function                  */
/*                                                                                     */
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Author(s):                                                                          */
/*      Omer Levy                                                                      */
/*      Mark Lukoyanichev                                                              */
/*-------------------------------------------------------------------------------------*/

#ifndef _OMERMARK_HEURISTICS_SIMPLE_H
#define _OMERMARK_HEURISTICS_SIMPLE_H

#include "OmerMark_IHeuristics.h"

class OmerMark_Heuristics_Simple : public OmerMark_IHeuristics
{
public:
    OmerMark_Heuristics_Simple()             {}
    ~OmerMark_Heuristics_Simple()    {}

    // Implementation of simple heuristics function
    double getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor)
    {
        return board.getStoreContents(playerColor) - 
               board.getStoreContents(Definitions::getOppositePlayer(playerColor));      
    }
};


#endif
