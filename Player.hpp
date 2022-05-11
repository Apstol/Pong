#pragma once

#include <SFML/System/Time.hpp>

#include "Paddle.hpp"

class Player
{
	public:
		Player(Paddle& paddle);
		virtual ~Player() = default;

		virtual void handleRealtimeInput() = 0;
		virtual void update(sf::Time delta) = 0;

	protected:
		Paddle& _paddle;
};
