#pragma once //skopiowane i poprawione z SplashState.h

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Flappy {
	//MENU WEJSCIOWE/PIERWSZY EKRAN
	class MainMenuState : public State {
	public:
		MainMenuState(GameDataRef data);

		void Init(); //przygotowamnie
		void HandleInput(); //obsluga wejscia
		void Update(float delta); //logika
		void Draw(float delta); //rysowanie

	private:
		GameDataRef _data;

		//sf::Clock _clock;

		//sf::Texture _backgroundTexture;
		sf::Sprite _background;
		sf::Sprite _title;
		sf::Sprite _playButton;
	};
}