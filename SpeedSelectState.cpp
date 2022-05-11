#include "SpeedSelectState.hpp"
#include "StateIdentifiers.hpp"
#include "Utility.hpp"

SpeedSelectState::SpeedSelectState(Game* game)
: State(game),
  _selectedOption(GameOptions::Speed::Slow)
{
	sf::Text slowSpeedOption;
	slowSpeedOption.setFont(_game->font());
	slowSpeedOption.setCharacterSize(40);
	slowSpeedOption.setString("SLOW");
	slowSpeedOption.setFillColor(sf::Color::White);
	centerOrigin(slowSpeedOption);
	slowSpeedOption.setPosition(320, 180);

	sf::Text mediumSpeedOption;
	mediumSpeedOption.setFont(_game->font());
	mediumSpeedOption.setCharacterSize(40);
	mediumSpeedOption.setString("MEDIUM");
	mediumSpeedOption.setFillColor(sf::Color(211, 211, 211, 133));
	centerOrigin(mediumSpeedOption);
	mediumSpeedOption.setPosition(320, 240);

	sf::Text fastSpeedOption;
	fastSpeedOption.setFont(_game->font());
	fastSpeedOption.setCharacterSize(40);
	fastSpeedOption.setString("FAST");
	fastSpeedOption.setFillColor(sf::Color(211, 211, 211, 133));
	centerOrigin(fastSpeedOption);
	fastSpeedOption.setPosition(320, 300);

	_speedSelectOptions = { slowSpeedOption, mediumSpeedOption, fastSpeedOption };
}

void SpeedSelectState::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			_selectedOption = (_selectedOption - 1 + _speedSelectOptions.size()) % _speedSelectOptions.size();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			_selectedOption = (_selectedOption + 1) % _speedSelectOptions.size();
		}
		else if (event.key.code == sf::Keyboard::Enter)
		{
			_game->setSpeed(static_cast<GameOptions::Speed>(_selectedOption));
			_game->setNextStateId(States::ID::InGame);
		}
	}
}

void SpeedSelectState::update(sf::Time delta)
{
	for (sf::Text& option : _speedSelectOptions)
	{
		option.setFillColor(sf::Color(211, 211, 211, 133));
	}
	_speedSelectOptions[_selectedOption].setFillColor(sf::Color::White);
}

void SpeedSelectState::draw()
{
	for (sf::Text option : _speedSelectOptions)
	{
		_game->window().draw(option);
	}
}
