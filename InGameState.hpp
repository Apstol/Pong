#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <array>

#include "State.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Player.hpp"

class InGameState : public State
{
	public:
		InGameState(Game* game);

		virtual void handleRealtimeInput() override;
		virtual void update(sf::Time delta);
		virtual void draw();

	private:
		sf::RectangleShape _upperBorder;
		sf::RectangleShape _lowerBorder;
		std::array<sf::RectangleShape, 14> _centralLine;
		sf::Text _leftPlayerScore;
		sf::Text _rightPlayerScore;
		std::unique_ptr<Player> _playerOne;
		std::unique_ptr<Player> _playerTwo;
		Paddle _leftPaddle;
		Paddle _rightPaddle;
		Ball _ball;
};
