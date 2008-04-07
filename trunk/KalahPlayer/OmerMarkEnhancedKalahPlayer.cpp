#include "OmerMarkEnhancedKalahPlayer.h"

int OmerMarkEnhancedKalahPlayer::utility(const KalahBoard &board) {
	int utility = 0;
	utility += countPotentialStones(board.getHousesContents(m_myColor));
	utility += board.getStoreContents(m_myColor);
	utility -= countPotentialStones(board.getHousesContents(Definitions::getOppositePlayer(m_myColor)));
	utility -= board.getStoreContents(Definitions::getOppositePlayer(m_myColor));
	return utility;
}

int OmerMarkEnhancedKalahPlayer::countPotentialStones(vector<int> houses) {
	int sum = 0;
	for (int i = 0; i < houses.size(); i++) {
		if (houses[i] < houses.size() - i) {
			sum += houses[i];
		}
	}
	return sum;
}
