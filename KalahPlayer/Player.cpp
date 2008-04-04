#include "Player.h"

Player::Player(const GameTimer::TimeParams &tp) : m_gameTimer(tp)
{
};

Player::~Player()
{
};

string Player::getName() const
{
	return m_myName;
};
