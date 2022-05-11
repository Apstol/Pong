#include "State.hpp"

State::State(Game* game)
: _game(game)
{
}

void State::handleRealtimeInput()
{
	// Empty by default
}

void State::handleEvent(sf::Event& event)
{
	// Empty by default
}
