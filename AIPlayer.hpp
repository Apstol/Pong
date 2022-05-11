#pragma once

#include <SFML/System/Vector2.hpp>

#include "Paddle.hpp"
#include "Ball.hpp"
#include "Player.hpp"

class AIPlayer : public Player
{
	public:
		AIPlayer(Paddle& paddle, const Ball& ball);
		virtual void handleRealtimeInput();
		virtual void update(sf::Time delta);

	private:
		sf::Keyboard::Key _upKey;
		sf::Keyboard::Key _downKey;
		static const float SpeedModifier;
		const Ball& _ball;
};
