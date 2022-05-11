#include <string>

#include <SFML/System/Vector2.hpp>

#include "AIPlayer.hpp"
#include "HumanPlayer.hpp"
#include "InGameState.hpp"
#include "GameOptions.hpp"
#include "Utility.hpp"

InGameState::InGameState(Game* game)
: State(game),
_leftPaddle(game->window(), game->speed(), sf::Vector2f(8.f, 240.f)),
_rightPaddle(game->window(), game->speed(), sf::Vector2f(632.f, 240.f)),
_ball(game)
{
	switch (game->numPlayers())
	{
		case GameOptions::NumPlayers::OnePlayer:
			_playerOne = std::make_unique<AIPlayer>(_leftPaddle, _ball);
			_playerTwo = std::make_unique<HumanPlayer>(sf::Keyboard::Up, sf::Keyboard::Down, _rightPaddle);
			break;
		case GameOptions::NumPlayers::TwoPlayers:
			_playerOne = std::make_unique<HumanPlayer>(sf::Keyboard::W, sf::Keyboard::S, _leftPaddle);
			_playerTwo = std::make_unique<HumanPlayer>(sf::Keyboard::Up, sf::Keyboard::Down, _rightPaddle);
			break;
	}

	_leftPlayerScore.setFont(_game->font());
	_leftPlayerScore.setCharacterSize(42);
	_leftPlayerScore.setString(std::to_string(_game->leftPlayerScore()));
	_leftPlayerScore.setFillColor(sf::Color(211, 211, 211, 255));
	centerOrigin(_leftPlayerScore);
	_leftPlayerScore.setPosition(260, 32);

	_rightPlayerScore.setFont(_game->font());
	_rightPlayerScore.setCharacterSize(42);
	_rightPlayerScore.setString(std::to_string(_game->rightPlayerScore()));
	_rightPlayerScore.setFillColor(sf::Color(211, 211, 211, 255));
	centerOrigin(_rightPlayerScore);
	_rightPlayerScore.setPosition(380, 32);

	_upperBorder.setSize(sf::Vector2f(640, 16));
	_upperBorder.setFillColor(sf::Color(211, 211, 211, 255));
	centerOrigin(_upperBorder);
	_upperBorder.setPosition(320, 8);

	_lowerBorder.setSize(sf::Vector2f(640, 16));
	_lowerBorder.setFillColor(sf::Color(211, 211, 211, 255));
	centerOrigin(_lowerBorder);
	_lowerBorder.setPosition(320, 472);

	int offset = 16;
	for (int i = 0; i < _centralLine.size(); ++i)
	{
		_centralLine[i].setSize(sf::Vector2f(16, 16));
		_centralLine[i].setFillColor(sf::Color(211, 211, 211, 255));
		centerOrigin(_centralLine[i]);
		_centralLine[i].setPosition(320, 16 + offset + i * 16);
		offset += 16;
	}
}

void InGameState::handleRealtimeInput()
{
	_playerOne->handleRealtimeInput();
	_playerTwo->handleRealtimeInput();
}

void InGameState::update(sf::Time delta)
{
	_playerOne->update(delta);
	_playerTwo->update(delta);
	_ball.update(delta, _leftPaddle, _rightPaddle);

	_leftPlayerScore.setString(std::to_string(_game->leftPlayerScore()));
	_rightPlayerScore.setString(std::to_string(_game->rightPlayerScore()));

	if (_game->isGameOver())
	{
		_game->setNextStateId(States::ID::GameOver);
	}
}

void InGameState::draw()
{
	_game->window().draw(_leftPlayerScore);
	_game->window().draw(_rightPlayerScore);

	for (const sf::RectangleShape& block : _centralLine)
	{
		_game->window().draw(block);
	}

	_game->window().draw(_leftPaddle);
	_game->window().draw(_rightPaddle);
	_game->window().draw(_ball);

	_game->window().draw(_upperBorder);
	_game->window().draw(_lowerBorder);
}
