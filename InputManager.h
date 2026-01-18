#pragma once

#include <SFML/Graphics.hpp>

namespace Flappy {
	//MENADZER WEJSCIA
	class InputManager {
	public:
		InputManager(){} //konstruktor
		~InputManager(){} //dekonstruktor

		//funkcja sprawdza czy gracz kliknal na konkretny punkt w grze
		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

		//funckja sprawdza gdzie jest kursor myszy
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);

	};
}