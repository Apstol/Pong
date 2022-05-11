#pragma once

#include <cmath>

#include "Utility.hpp"
#include "AIPlayer.hpp"

const float AIPlayer::SpeedModifier = 1.f/3.f;

AIPlayer::AIPlayer(Paddle& paddle, const Ball& ball)
: Player(paddle),
  _ball(ball)
{
}

void AIPlayer::handleRealtimeInput()
{
	// Empty for AI
}

void AIPlayer::update(sf::Time delta)
{
	sf::Vector2f paddleDirection;

	sf::Vector2f unitVector = unitVectorFrom(_ball.velocity());

	float angle = atan2(unitVector.y, -unitVector.x);

	// tanA = b / a
	// b = tanA * a
	float b = std::tan(angle) * _ball.position().x; 

	float interceptionPoint = b + _ball.position().y;

	if (std::abs(_paddle.position().y - interceptionPoint) <= 20)
	{
		paddleDirection = sf::Vector2f(0.f, 0.f);
	}
	else if (_paddle.position().y < interceptionPoint)
	{
		paddleDirection = sf::Vector2f(0.f, 1.f);
	}
	else if (_paddle.position().y > interceptionPoint)
	{
		paddleDirection = sf::Vector2f(0.f, -1.f);
	}

	_paddle.setVelocity(paddleDirection, _paddle.speed() * SpeedModifier);
	_paddle.update(delta);
}
