/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Project Name:                                                                       */
/*     AI - HW 2                                                                       */
/*                                                                                     */
/* OmerMark_AlphaBetaResults.h                                                         */
/*     This file contains implementation of Results class that is returned by          */
/*     AlphaBeta search                                                                */
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*                                                                                     */
/* Author(s):                                                                          */
/*      Omer Levy                                                                      */
/*      Mark Lukoyanichev                                                              */
/*-------------------------------------------------------------------------------------*/

#ifndef __OMER_MARK_ALPHA_BETA_RESULT_H__
#define __OMER_MARK_ALPHA_BETA_RESULT_H__

/*
 * Holds the result of AlphaBeta search
 */
class OmerMarkAlphaBetaResults
{
public:
    // Constructors/Destructors
	OmerMarkAlphaBetaResults(int _move = 0, double _heuristicsVal = 0) : move(_move), heuristicsVal(_heuristicsVal) {}
    ~OmerMarkAlphaBetaResults() {}


    KalahMove   move;
	double      heuristicsVal;
};

#endif
