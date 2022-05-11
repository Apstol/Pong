#pragma once

#include <utility>
#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "GameOptions.hpp"

class State;

class Game
{
	public:
		Game();

		void run();
		sf::Font& font();
		sf::RenderWindow& window();
		void playHitSound();
		void setNextStateId(States::ID id);
		int leftPlayerScore() const;
		int rightPlayerScore() const;
		void updateLeftPlayerScore();
		void updateRightPlayerScore();
		GameOptions::NumPlayers numPlayers() const;
		GameOptions::Speed speed() const;
		void setNumPlayers(GameOptions::NumPlayers numPlayers);
		void setSpeed(GameOptions::Speed speed);
		bool isGameOver() const;
		void setIsPlaying(bool isPlaying);
		void reset();

	private:
		static const sf::Time TimePerFrame;

		void _handleEvents();
		void _render();
		void _handleStateChange();

		sf::Font _font;
		sf::SoundBuffer _soundBuffer;
		sf::Sound _hitSound;
		sf::Event _currentEvent;
		sf::RenderWindow _window;
		std::unique_ptr<State> _activeState;
		States::ID _nextStateId;
		int _leftPlayerScore;
		int _rightPlayerScore;
		GameOptions::NumPlayers _numPlayers;
		GameOptions::Speed _speed;
		bool _isPlaying;
};
