#ifndef _HEURISTICS_SIMPLE_H
#define _HEURISTICS_SIMPLE_H

#include "IHeuristics.h"

class Heuristics_Simple : public IHeuristics
{
public:
    Heuristics_Simple()             {}
    ~Heuristics_Simple()    {}

    // Implementation of simple heuristics function
    int getHeuristics(const KalahBoard& board, const Definitions::PlayerColor& playerColor)
    {
        return board.getStoreContents(playerColor) - 
               board.getStoreContents(Definitions::getOppositePlayer(playerColor));      
    }
};


#endif