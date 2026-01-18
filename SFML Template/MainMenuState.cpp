#include <sstream>
#include <iostream>
#include "MainMenuState.h"
#include "GameState.h"
#include "DEFINITIONS.h"

namespace Flappy {

	MainMenuState::MainMenuState(GameDataRef data) : _data(data) {

	}

	//Ladowanie tekstury
	void MainMenuState::Init() {

		//zaladowanie tekstury
		_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH); //w zbiorze _data idziemy do assets i ladujemy plik z dysku
		_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

		//odzyskiwanie 
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background")); //ustawia jako _background wczesnuej zaladowana teksture i ja nazywa
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));

		//rozmieszczenie //SFML - ma bazowe top left
		_title.setPosition((SCREEN_WIDTH/2) - (_title.getGlobalBounds().width/2), _title.getGlobalBounds().height/4.5); //(SCREEN_WIDTH/2) - (_title.getGlobalBounds().width/2) --> polowa szerokosci
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
	}	

	void MainMenuState::HandleInput() {
		//dla zamykania okna
		sf::Event event;
		while (_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
			//jesli kliknie sie w przycisk start to zabiera nas do stanu rozgrywki
			if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window)) {
				_data->machine.AddState(StateRef(new GameState(_data)), true); 
			}
		}
	}

	//tutaj nie ma niczego z czasem
	void MainMenuState::Update(float delta) {

	}

	void MainMenuState::Draw(float delta) {

		_data->window.clear(); //czysci okno

		_data->window.draw(_background); //rysuje przygotowane przez nas tlo 
		//buffor tylny - komputer maluje tlo w pamieci (window.draw())
		//buffor przedni - obraz ktory widzi uzytkonik na monitorze
		_data->window.draw(_title);
		_data->window.draw(_playButton);

		_data->window.display(); //wyswietla obraz na ekranie monitora (poprzez swap buforow
	}
}