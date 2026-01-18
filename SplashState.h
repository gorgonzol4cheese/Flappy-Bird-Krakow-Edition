#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Flappy {
	//MENU WEJSCIOWE/PIERWSZY EKRAN
	class SplashState : public State {
	public:
		SplashState(GameDataRef data);

		void Init(); //przygotowamnie
		void HandleInput(); //obsluga wejscia
		void Update(float delta); //logika
		void Draw(float delta); //rysowanie

	private:
		GameDataRef _data;

		sf::Clock _clock;

		//sf::Texture _backgroundTexture;
		sf::Sprite _background;
	};
}