#pragma once

#include <SFML/Graphics/Text.hpp>

#include <array>

#include "State.hpp"

class GameOverState : public State
{
	public:
		GameOverState(Game* game);

		virtual void handleEvent(sf::Event& event) override;
		virtual void update(sf::Time delta);
		virtual void draw();

	private:
		sf::Text _text;
		int _selectedOption;
		std::array<sf::Text, GameOptions::GameOverCount> _gameOverOptions;
};
