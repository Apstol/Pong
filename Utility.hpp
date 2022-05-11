#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// TODO: rename to "normalized"
sf::Vector2f unitVectorFrom(sf::Vector2f vector);

void centerOrigin(sf::Text& text);
void centerOrigin(sf::RectangleShape& text);

extern const float PI;
