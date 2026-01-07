#include "InputManager.h"

namespace Flappy {

	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window) {

		if (sf::Mouse::isButtonPressed(button)) {
			//tworzy niewidzialny prostokat, ktory ma wymiary obrazka //tworzy hitbox
			sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

			if (tempRect.contains(sf::Mouse::getPosition(window))) { //sprawdza czy myszka znajduje sie w hitboxie
				return true;  //^pobiera wspolrzedne myszy w oknie gry^
			}	//funkcja zwraca true, jesli przycisk jest klikniety ORAZ mysz znajduje sie w oknie gry
		}
		return false; //sprite nie jest klikalny
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window) {
		return sf::Mouse::getPosition(window); //zwraca wspolrzedne gdzie znajduje sie kursor myszy
	}
}