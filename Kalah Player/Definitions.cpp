#include "Definitions.h"

Definitions::PlayerColor Definitions::getOppositePlayer(Definitions::PlayerColor p)
{
	if(p == Definitions::NONE)
		return Definitions::NONE;

	return p == Definitions::WHITE ? Definitions::BLACK : Definitions::WHITE;
};
