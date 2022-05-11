#pragma once

#include <SFML/System/Vector2.hpp>

#include "Paddle.hpp"
#include "Player.hpp"

class HumanPlayer : public Player
{
	public:
		HumanPlayer(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, Paddle& paddle);

		virtual void handleRealtimeInput();
		virtual void update(sf::Time delta);

	private:
		sf::Keyboard::Key _upKey;
		sf::Keyboard::Key _downKey;
};
