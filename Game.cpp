#include <SFML/System/Clock.hpp>

#include <stdexcept>

#include "PlayersSelectState.hpp"
#include "SpeedSelectState.hpp"
#include "InGameState.hpp"
#include "GameOverState.hpp"
#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: _window(sf::VideoMode(640, 480), "Pong"),
  _leftPlayerScore(0),
  _rightPlayerScore(0),
  _isPlaying(true)
{
	_window.setKeyRepeatEnabled(false);

	if (!_font.loadFromFile("./resources/8bitOperatorPlus8-Bold.ttf"))
	{
		throw std::runtime_error("Failed to load font!");
	}	

	if (!_soundBuffer.loadFromFile("./resources/hit.wav"))
	{
		throw std::runtime_error("Failed to load sound!");
	}

	_hitSound.setBuffer(_soundBuffer);

	_activeState = std::make_unique<PlayersSelectState>(this);
	_nextStateId = States::None;
}

sf::Font& Game::font()
{
	return _font;
}

sf::RenderWindow& Game::window()
{
	return _window;
}

void Game::setNextStateId(States::ID id)
{
	_nextStateId = id;
}

void Game::_handleStateChange()
{
	if (_nextStateId == States::ID::None)
	{
		return;
	}

	switch (_nextStateId)
	{
		case States::ID::PlayersSelect:
			_activeState = std::make_unique<PlayersSelectState>(this);
			break;
		case States::ID::SpeedSelect:
			_activeState = std::make_unique<SpeedSelectState>(this);
			break;
		case States::ID::InGame:
			_activeState = std::make_unique<InGameState>(this);
			break;	
		case States::ID::GameOver:
			_activeState = std::make_unique<GameOverState>(this);
			break;	
	}

	_nextStateId = States::ID::None;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate{ sf::Time::Zero };

	while (_window.isOpen() && _isPlaying)
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			_handleEvents();
			_activeState->update(TimePerFrame);
		}

		_handleStateChange();
		
		_render();
	}
}

void Game::_handleEvents()
{
	while (_window.pollEvent(_currentEvent))
	{
		if (_currentEvent.type == sf::Event::Closed)
		{
			_window.close();
		}

		_activeState->handleEvent(_currentEvent);
	}

	_activeState->handleRealtimeInput();
}

void Game::_render()
{
		_window.clear();

		_activeState->draw();

		_window.display();
}

void Game::playHitSound()
{
    	_hitSound.play();
}

int Game::leftPlayerScore() const
{
	return _leftPlayerScore;
}

int Game::rightPlayerScore() const
{
	return _rightPlayerScore;
}

void Game::updateLeftPlayerScore()
{
	_leftPlayerScore += 1;
}

void Game::updateRightPlayerScore()
{
	_rightPlayerScore += 1;
}

GameOptions::NumPlayers Game::numPlayers() const
{
	return _numPlayers;
}

GameOptions::Speed Game::speed() const
{
	return _speed;
}

void Game::setNumPlayers(GameOptions::NumPlayers numPlayers)
{
	_numPlayers = numPlayers;
}

void Game::setSpeed(GameOptions::Speed speed)
{
	_speed = speed;
}

bool Game::isGameOver() const
{
	return _leftPlayerScore == 10 || _rightPlayerScore == 10;
}

void Game::setIsPlaying(bool isPlaying)
{
	_isPlaying = isPlaying;
}

void Game::reset()
{
	_leftPlayerScore = 0;
	_rightPlayerScore = 0;
}
