#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "GameOptions.hpp"

class Paddle : public sf::Drawable, sf::Transformable
{
	public:
		Paddle(sf::RenderWindow& window, GameOptions::Speed speedOption, sf::Vector2f position);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time delta);
		sf::FloatRect globalBounds() const;
		sf::Vector2f position() const;
		float speed() const;
		void setVelocity(sf::Vector2f direction);
		void setVelocity(sf::Vector2f direction, float speed);

	protected:
		void _adaptPosition();

		sf::RectangleShape _shape;
		float _speed;
		sf::Vector2f _velocity;
		const sf::RenderWindow* const _window;
};
