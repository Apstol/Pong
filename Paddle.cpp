#include "Paddle.hpp"
#include "Utility.hpp"

Paddle::Paddle(sf::RenderWindow& window, GameOptions::Speed speedOption, sf::Vector2f position)
: _window(&window),
  _velocity(0.f, 0.f)
{
	_shape.setSize(sf::Vector2f(16, 100));
	_shape.setFillColor(sf::Color(211, 211, 211, 255));
	centerOrigin(_shape);
	_shape.setPosition(position);

	switch (speedOption)
	{
		case GameOptions::Speed::Slow:
			_speed = 600;	
			break;
		case GameOptions::Speed::Medium:
			_speed = 800;	
			break;
		case GameOptions::Speed::Fast:
			_speed = 1000;	
			break;
	}
}

void Paddle::update(sf::Time delta)
{
	_shape.move(_velocity * delta.asSeconds());
	_adaptPosition();
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}

void Paddle::_adaptPosition()
{
	sf::Vector2f position = _shape.getPosition();

	position.y = std::max(position.y, _shape.getOrigin().y + 16);
	position.y = std::min(position.y, _window->getSize().y - 16 - _shape.getOrigin().y);

	_shape.setPosition(position);
}

sf::FloatRect Paddle::globalBounds() const
{
	return _shape.getGlobalBounds();
}

sf::Vector2f Paddle::position() const
{
	return _shape.getPosition();
}

float Paddle::speed() const
{
	return _speed;
}

void Paddle::setVelocity(sf::Vector2f direction)
{
	_velocity = direction * _speed;
}

void Paddle::setVelocity(sf::Vector2f direction, float speed)
{
	_velocity = direction * speed;
}
