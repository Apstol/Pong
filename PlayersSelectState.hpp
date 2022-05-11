#pragma once

#include <array>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "GameOptions.hpp"

class PlayersSelectState : public State
{
	public:
		PlayersSelectState(Game* game);

		virtual void handleEvent(sf::Event& event) override;
		virtual void update(sf::Time delta);
		virtual void draw();
	
	private:
		int _selectedOption;
		std::array<sf::Text, GameOptions::PlayersOptionsCount> _numPlayersOptions;
};
