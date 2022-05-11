#include "Ball.hpp"
#include "Utility.hpp"

#include <algorithm>
#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Ball::Ball(Game* game)
: _game(game),
  _isResetting(false),
  _resetTimeout(sf::Time::Zero)
{
	switch (_game->speed())
	{
		case GameOptions::Speed::Slow:
			_speed = 500;	
			break;
		case GameOptions::Speed::Medium:
			_speed = 700;	
			break;
		case GameOptions::Speed::Fast:
			_speed = 900;	
			break;
	}

	_shape.setSize(sf::Vector2f(16, 16));
	_shape.setFillColor(sf::Color(211, 211, 211, 255));
	centerOrigin(_shape);
	_shape.setPosition(320, 240);

	_velocity = sf::Vector2f(1.f, 0.f) * (_speed / 2.f);
}

void Ball::update(sf::Time delta, const Paddle& leftPaddle, const Paddle& rightPaddle)
{
	if (_isResetting)
	{
		_resetTimeout += delta;
		if (_resetTimeout >= sf::seconds(1))
		{
			_isResetting = false;
			_resetTimeout = sf::Time::Zero;
		}
		else
		{
			return;
		}
	}

	if (_shape.getGlobalBounds().intersects(leftPaddle.globalBounds()))
	{
	    	_adaptPosition();
		_velocity = _velocityOnCollisionWithPaddle(leftPaddle, false);
		_game->playHitSound();
	}
	else if (_shape.getGlobalBounds().intersects(rightPaddle.globalBounds()))
	{
	    	_adaptPosition();
		_velocity = _velocityOnCollisionWithPaddle(rightPaddle, true);
		_game->playHitSound();
	}
	else if (_shape.getGlobalBounds().left <= 0)
	{
		_game->updateRightPlayerScore();
		_resetPosition();
	}
	else if (_shape.getGlobalBounds().left >= 640)
	{
		_game->updateLeftPlayerScore();
		_resetPosition();
	}
	else if (_shape.getGlobalBounds().top < 16)
	{
		sf::Vector2f position = _shape.getPosition();
		_shape.setPosition(position.x, 24);
		_velocity = _velocityOnCollisionWithBorder();
		_game->playHitSound();
	}
	else if (_shape.getGlobalBounds().top + _shape.getGlobalBounds().height > 464)
	{
		sf::Vector2f position = _shape.getPosition();
		_shape.setPosition(position.x, 456);
		_velocity = _velocityOnCollisionWithBorder();
		_game->playHitSound();
	}

	_shape.move(_velocity * delta.asSeconds());
}

sf::Vector2f Ball::_velocityOnCollisionWithPaddle(const Paddle& paddle, bool isRightPaddle)
{
    	float angleDegrees = (_shape.getPosition().y - paddle.position().y) 
			/ (paddle.globalBounds().height / 2)
			* 60;

	float angleRadians = angleDegrees * PI / 180;

	float xComponent = std::cos(angleRadians);
	float yComponent = std::sin(angleRadians);

	if (isRightPaddle)
	{
		xComponent = -xComponent;
	}

	return sf::Vector2f(xComponent, yComponent) * _speed;
}

sf::Vector2f Ball::_velocityOnCollisionWithBorder()
{
	sf::Vector2f unitVector = unitVectorFrom(_velocity);
	unitVector.y = -unitVector.y;

	return unitVector * _speed;
}

void Ball::_resetPosition()
{
	_isResetting = true;

	_shape.setPosition(320, 240);

	sf::Vector2f unitVector = unitVectorFrom(_velocity);

	_velocity = unitVector * (_speed / 2.f);
	_velocity.x = -_velocity.x;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_isResetting)
	{
		return;
	}

	target.draw(_shape, states);
}

sf::Vector2f Ball::velocity() const
{
	return _velocity;
}

sf::Vector2f Ball::position() const
{
	return _shape.getPosition();
}

void Ball::_adaptPosition()
{
	sf::Vector2f position = _shape.getPosition();
	sf::Vector2f unitVector = unitVectorFrom(_velocity);
	_shape.setPosition(position.x - unitVector.x, position.y - unitVector.y);
}
