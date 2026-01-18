#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"

namespace Flappy {
	class Bird {
	public:
		Bird(GameDataRef data);

		void Draw();
		void Animate(float delta);
		void Update(float delta);
		void Tap();

		const sf::Sprite& GetSprite() const; //do kolizji

	private:
		GameDataRef _data;

		sf::Sprite _birdSprite;
		vector<sf::Texture> _animationFrames;

		unsigned int _animationIterator;
		
		//zegary
		sf::Clock _clock;
		sf::Clock _movementClock;

		//ogarnia jakie sa aktualne stany smoka
		int _birdState;
		float _rotation;
	};
}
