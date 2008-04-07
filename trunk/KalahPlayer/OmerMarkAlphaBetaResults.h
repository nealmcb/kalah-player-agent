#ifndef __OMER_MARK_ALPHA_BETA_RESULT_H__
#define __OMER_MARK_ALPHA_BETA_RESULT_H__

class OmerMarkAlphaBetaResults
{
public:
	OmerMarkAlphaBetaResults(int _move, int _utility) : move(_move), utility(_utility) {}
	KalahMove move;
	int utility;
};

#endif
