#include "OmerMarkSimpleKalahPlayer.h"

int OmerMarkSimpleKalahPlayer::utility(const KalahBoard &board) {
	return board.getStoreContents(m_myColor) - board.getStoreContents(Definitions::getOppositePlayer(m_myColor));
}
