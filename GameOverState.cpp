#include <string>

#include "GameOverState.hpp"
#include "Utility.hpp"

GameOverState::GameOverState(Game* game)
: State(game),
  _selectedOption(GameOptions::GameOver::PlayAgain)
{
	std::string textString = _game->leftPlayerScore() == 10
		? "PLAYER 1 WON!"
		: "PLAYER 2 WON!";

	_text.setFont(_game->font());
	_text.setCharacterSize(40);
	_text.setString(textString);
	_text.setFillColor(sf::Color::White);
	centerOrigin(_text);
	_text.setPosition(320, 120);

	sf::Text playAgainOption;
	playAgainOption.setFont(_game->font());
	playAgainOption.setCharacterSize(40);
	playAgainOption.setString("PLAY AGAIN");
	playAgainOption.setFillColor(sf::Color::White);
	centerOrigin(playAgainOption);
	playAgainOption.setPosition(320, 240);

	sf::Text exitOption;
	exitOption.setFont(_game->font());
	exitOption.setCharacterSize(40);
	exitOption.setString("EXIT");
	exitOption.setFillColor(sf::Color(211, 211, 211, 133));
	centerOrigin(exitOption);
	exitOption.setPosition(320, 300);

	_gameOverOptions = { playAgainOption, exitOption };
}

void GameOverState::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			_selectedOption = (_selectedOption - 1 + _gameOverOptions.size()) % _gameOverOptions.size();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			_selectedOption = (_selectedOption + 1) % _gameOverOptions.size();
		}
		else if (event.key.code == sf::Keyboard::Enter)
		{
			switch (static_cast<GameOptions::GameOver>(_selectedOption))
			{
				case GameOptions::GameOver::PlayAgain:
					_game->reset();
					_game->setNextStateId(States::ID::PlayersSelect);
					break;
				case GameOptions::GameOver::Exit:
					_game->setIsPlaying(false);
					break;
			}
		}
	}
}

void GameOverState::update(sf::Time delta)
{
	for (sf::Text& option : _gameOverOptions)
	{
		option.setFillColor(sf::Color(211, 211, 211, 133));
	}
	_gameOverOptions[_selectedOption].setFillColor(sf::Color::White);
}

void GameOverState::draw()
{
	_game->window().draw(_text);
	for (sf::Text option : _gameOverOptions)
	{
		_game->window().draw(option);
	}
}
