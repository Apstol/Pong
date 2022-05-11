#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, Paddle& paddle)
: Player(paddle),
  _upKey(upKey),
  _downKey(downKey)
{
}

void HumanPlayer::handleRealtimeInput()
{
	if (sf::Keyboard::isKeyPressed(_upKey))
	{
		_paddle.setVelocity(sf::Vector2f(0.f, -1.f));
	}
	else if (sf::Keyboard::isKeyPressed(_downKey))
	{
		_paddle.setVelocity(sf::Vector2f(0.f, 1.f));
	}
	else
	{
		_paddle.setVelocity(sf::Vector2f(0.f, 0.f));
	}
}

void HumanPlayer::update(sf::Time delta)
{
	_paddle.update(delta);
}

