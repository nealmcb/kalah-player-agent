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

#ifndef _IHEURISTICS_H
#define _IHEURISTICS_H

class IHeuristics
{
public:
    // Constructors/Destructors
    IHeuristics() {};
    virtual ~IHeuristics() {};

    // Board evaluation function
    virtual double getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor) = 0;
};


#endif
