#include <SFML/Graphics.hpp>

#define SCREEN_HEIGHT 1024
#define SCREEN_WIDTH 1024

int main() {

	sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH,SCREEN_HEIGHT }), "Flappy Bird: Krakow Edition");

	while (window.isOpen()) {
		//eventy

		//logika gry

		//powstawanie obiektow

		window.clear();

		//dodawanie obiektow SFML

		window.display();
	}
	return EXIT_SUCCESS;
}