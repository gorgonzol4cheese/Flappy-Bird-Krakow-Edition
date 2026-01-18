#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>

namespace Flappy {

	class Land {
	public:
		Land(GameDataRef data);

		void MoveLand(float delta);
		void DrawLand();

		const vector<sf::Sprite>& GetSprites() const; //do kolizji

	private:
		GameDataRef _data;

		vector<sf::Sprite>_landSprites;
	};
}
