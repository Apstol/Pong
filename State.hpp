#pragma once

#include <SFML/Window/Event.hpp>

#include "Game.hpp"

class Game;

class State
{
	public:
		State(Game* game);
		virtual ~State() = default;

		virtual void handleRealtimeInput();
		virtual void handleEvent(sf::Event& event);
		virtual void update(sf::Time delta) = 0;
		virtual void draw() = 0;

	protected:
		Game* _game;
};
