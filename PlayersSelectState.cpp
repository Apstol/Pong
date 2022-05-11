#include "PlayersSelectState.hpp"
#include "StateIdentifiers.hpp"
#include "Utility.hpp"

PlayersSelectState::PlayersSelectState(Game* game)
: State(game),
  _selectedOption(GameOptions::NumPlayers::OnePlayer)
{
	sf::Text onePlayerOption;
	onePlayerOption.setFont(_game->font());
	onePlayerOption.setCharacterSize(40);
	onePlayerOption.setString("ONE PLAYER");
	onePlayerOption.setFillColor(sf::Color::White);
	centerOrigin(onePlayerOption);
	onePlayerOption.setPosition(320, 200);

	sf::Text twoPlayersOption;
	twoPlayersOption.setFont(_game->font());
	twoPlayersOption.setCharacterSize(40);
	twoPlayersOption.setString("TWO PLAYERS");
	twoPlayersOption.setFillColor(sf::Color(211, 211, 211, 133));
	centerOrigin(twoPlayersOption);
	twoPlayersOption.setPosition(320, 260);

	_numPlayersOptions = { onePlayerOption, twoPlayersOption };
}

void PlayersSelectState::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			_selectedOption = (_selectedOption - 1 + _numPlayersOptions.size()) % _numPlayersOptions.size();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			_selectedOption = (_selectedOption + 1) % _numPlayersOptions.size();
		}
		else if (event.key.code == sf::Keyboard::Enter)
		{
			_game->setNumPlayers(static_cast<GameOptions::NumPlayers>(_selectedOption));
			_game->setNextStateId(States::ID::SpeedSelect);
		}
	}
}

void PlayersSelectState::update(sf::Time delta)
{
	for (sf::Text& option : _numPlayersOptions)
	{
		option.setFillColor(sf::Color(211, 211, 211, 133));
	}
	_numPlayersOptions[_selectedOption].setFillColor(sf::Color::White);
}

void PlayersSelectState::draw()
{
	for (sf::Text option : _numPlayersOptions)
	{
		_game->window().draw(option);
	}
}
