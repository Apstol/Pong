#include <SFML/Graphics/Rect.hpp>

#include <cmath>

#include "Utility.hpp"

const float PI = 3.1416f;

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2, bounds.height / 2);
}

void centerOrigin(sf::RectangleShape& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2, bounds.height / 2);
}

sf::Vector2f unitVectorFrom(sf::Vector2f vector)
{
	float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	return vector / magnitude;
}
