#include <iostream>
#include "Game.h"
#include "DEFINITIONS.h" //definicje wymiarow, parametrow itp.

int main() {

	Flappy::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird: Kraków Edition");
	
	return EXIT_SUCCESS;
}