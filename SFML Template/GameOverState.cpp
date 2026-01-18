#include <sstream>
#include <iostream>
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "GameState.h"

namespace Flappy {

	GameOverState::GameOverState(GameDataRef data) : _data(data) {

	}

	//Ladowanie tekstury
	void GameOverState::Init() {

		//zaladowanie tekstury
		_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH); //w zbiorze _data idziemy do assets i ladujemy plik z dysku
		_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		_data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
		//odzyskiwanie tekstury
		_background.setTexture(this->_data->assets.GetTexture("Game Over Background")); //ustawia jako _background wczesnuej zaladowana teksture i ja nazywa
		_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
		_gameOverContainer.setTexture(this->_data->assets.GetTexture("Game Over Body"));
		_retryButton.setTexture(this->_data->assets.GetTexture("Play Button"));

		//pozycje tekstur
		_gameOverContainer.setPosition((_data->window.getSize().x / 2) - (_gameOverContainer.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_gameOverContainer.getGlobalBounds().height / 2));
		_gameOverTitle.setPosition((_data->window.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2));
		_retryButton.setPosition((_data->window.getSize().x / 2) - (_retryButton.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + (_retryButton.getGlobalBounds().height * 0.2));
	}

	void GameOverState::HandleInput() {
		//dla zamykania okna
		sf::Event event;
		while (_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window)) {
				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float delta) {

	}

	void GameOverState::Draw(float delta) {

		_data->window.clear(); //czysci okno
		_data->window.draw(_background); //rysuje przygotowane przez nas tlo 
		//buffor tylny - komputer maluje tlo w pamieci (window.draw())
		//buffor przedni - obraz ktory widzi uzytkonik na monitorze

		_data->window.draw(_gameOverTitle);
		_data->window.draw(_gameOverContainer);
		_data->window.draw(_retryButton);

		_data->window.display(); //wyswietla obraz na ekranie monitora (poprzez swap buforow
	}
}