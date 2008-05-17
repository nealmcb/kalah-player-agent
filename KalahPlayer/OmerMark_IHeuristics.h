/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Project Name:                                                                       */
/*     AI - HW 2                                                                       */
/*                                                                                     */
/* OmerMark_IHeuristics.h                                                              */
/*     This file contains interface of the heuristic function                          */
/*                                                                                     */
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Author(s):                                                                          */
/*      Omer Levy                                                                      */
/*      Mark Lukoyanichev                                                              */
/*-------------------------------------------------------------------------------------*/

#ifndef _OMERMARK_IHEURISTICS_H
#define _OMERMARK_IHEURISTICS_H

class OmerMark_IHeuristics
{
public:
    // Constructors/Destructors
    OmerMark_IHeuristics() {};
    virtual ~OmerMark_IHeuristics() {};

    // Board evaluation function
    virtual double getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor) = 0;
};


#endif
