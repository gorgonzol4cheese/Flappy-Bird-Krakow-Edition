#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINITIONS.h"
#include <vector> //do przetrzymywania Sprite'ow

namespace Flappy {
	class Pipe {
	public:
		Pipe(GameDataRef);

		void SpawnBottomPipe();
		void SpawnTopPipe();
		void SpawnInvisiblePipe();
		void SpawnScoringPipe();
		void MovePipes(float delta);
		void DrawPipes();
		void RandomisePipeOffset(); //randomizuje Offset

		const vector<sf::Sprite>& GetSprites() const;
		vector<sf::Sprite>& GetScoringSprites();

	private:
		GameDataRef _data;
		vector<sf::Sprite> pipeSprites;
		vector<sf::Sprite> scoringPipes;

		int _landHeight; //wysokosc tekstury land
		int _pipeSpawnYOffset; //jak wysoko do gory i do dolu ma sie przemieszczac
	};
}