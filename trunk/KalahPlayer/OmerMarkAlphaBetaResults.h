#ifndef __OMER_MARK_ALPHA_BETA_RESULT_H__
#define __OMER_MARK_ALPHA_BETA_RESULT_H__

class OmerMarkAlphaBetaResults
{
public:
    // Constructors/Destructors
	OmerMarkAlphaBetaResults(int _move, int _heuristicsVal) : move(_move), heuristicsVal(_heuristicsVal) {}
    ~OmerMarkAlphaBetaResults() {}


    KalahMove   move;
	int         heuristicsVal;
};

#endif
