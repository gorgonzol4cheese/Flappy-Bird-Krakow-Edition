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
	
	struct GameData {

		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

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