#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Flappy {
	//MENU WEJSCIOWE/PIERWSZY EKRAN
	class GameOverState : public State {
	public:
		GameOverState(GameDataRef data, int score);

		void Init(); //przygotowamnie
		void HandleInput(); //obsluga wejscia
		void Update(float delta); //logika
		void Draw(float delta); //rysowanie

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _gameOverTitle;
		sf::Sprite _gameOverContainer;
		sf::Sprite _retryButton;

		sf::Text _scoreText;
		sf::Text _highScoreText;

		int _score;
		int _highScore;

	};
}