#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "HUD.h"

namespace Flappy {
	//MENU WEJSCIOWE/PIERWSZY EKRAN
	class GameState : public State {
	public:
		GameState(GameDataRef data);

		void Init(); //przygotowamnie
		void HandleInput(); //obsluga wejscia
		void Update(float delta); //logika
		void Draw(float delta); //rysowanie

	private:
		GameDataRef _data;

		sf::Sprite _background;

		Pipe* pipe; //wskaznik do obiektu pipe
		Land* land; //wskaznik do obiektu land
		Bird* bird; //wskaznik do obiektu bird
		Collision collision; //bez wskaznika bo nie musimy go ciagle rekonstruowac
		Flash* flash;
		HUD* hud;

		sf::Clock clock;

		int _gameState;

		int _score;

	};
}