#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
using namespace std;

namespace Flappy {
	
	//struktura danych gry,
	//zamiast tworzenia osobnych okien w nowych Stanach Gry, pakujemy je wszystkie do struktury
	struct GameData {

		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	//shared_ptr powoduje, ze kazdy Stan Gry ma dostep do tych samych zasobow
	//jesli tekstura jest zaladowana, to jest ona dostepna w calym GameData
	typedef shared_ptr<GameData> GameDataRef;


	class Game {
	public:
		Game(int width, int height, string title);

	private:
		const float delta = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = make_shared<GameData>();

		void Run();
	};
}