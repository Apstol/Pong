#pragma once

#include "Paddle.hpp"
#include "Game.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Ball : public sf::Drawable, sf::Transformable
{
	public:
		Ball(Game* game);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time delta, const Paddle& leftPaddle, const Paddle& rightPaddle);
		sf::Vector2f velocity() const;
		sf::Vector2f position() const;

	private:
		sf::Vector2f _velocityOnCollisionWithPaddle(const Paddle& paddle, bool isRightPaddle);
		sf::Vector2f _velocityOnCollisionWithBorder();
		void _resetPosition();
		void _adaptPosition();

		sf::RectangleShape _shape;
		float _speed;
		sf::Vector2f _velocity;
		Game* const _game;
		bool _isResetting;
		sf::Time _resetTimeout;
};
