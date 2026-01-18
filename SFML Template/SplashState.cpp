#include <sstream>
#include <iostream>
#include "SplashState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.h"

namespace Flappy {

	SplashState::SplashState(GameDataRef data) : _data(data) {

	}

	//Ladowanie tekstury
	void SplashState::Init() {

		//zaladowanie tekstury
		_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH); //w zbiorze _data idziemy do assets i ladujemy plik z dysku
		//odzyskiwanie tekstury
		_background.setTexture(this->_data->assets.GetTexture("Splash State Background")); //ustawia jako _background wczesnuej zaladowana teksture i ja nazywa
	}

	void SplashState::HandleInput() {
		//dla zamykania okna
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}
	}

	void SplashState::Update(float delta) { //logika czasu

		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) { //sprawdza czy minely juz (w naszym przypadku 3) sekundy
			//MAIN MENU PO 3 SEKUNDACH
			_data->machine.AddState(StateRef(new MainMenuState(_data)), true); //true -> zamienianie okien //false -> do pauzy np (bo nadal chcemy potem uzywac tego samego okna
		}
	}

	void SplashState::Draw(float delta) {

		_data->window.clear(); //czysci okno
		_data->window.draw(_background); //rysuje przygotowane przez nas tlo 
		//buffor tylny - komputer maluje tlo w pamieci (window.draw())
		//buffor przedni - obraz ktory widzi uzytkonik na monitorze
		_data->window.display(); //wyswietla obraz na ekranie monitora (poprzez swap buforow
	}
}