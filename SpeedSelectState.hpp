#pragma once

#include "State.hpp"
#include "GameOptions.hpp"

#include <array>

#include <SFML/Graphics/Text.hpp>

class SpeedSelectState : public State
{
	public:
		SpeedSelectState(Game* game);

		virtual void handleEvent(sf::Event& event) override;
		virtual void update(sf::Time delta);
		virtual void draw();
	
	private:
		int _selectedOption;
		std::array<sf::Text, GameOptions::SpeedCount> _speedSelectOptions;
};
