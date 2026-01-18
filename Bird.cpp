#include "Bird.h"
#include "DEFINITIONS.h"

namespace Flappy {
	
	Bird::Bird(GameDataRef data) : _data(data) {

		_animationIterator = 0;
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 1"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 2"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 3"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 4"));

		_birdSprite.setTexture(_animationFrames.at(_animationIterator));

		_birdSprite.setPosition((_data->window.getSize().x / 4 - (_birdSprite.getGlobalBounds().width / 2)), (_data->window.getSize().y / 2 - (_birdSprite.getGlobalBounds().height / 2)));
		_birdState = BIRD_STATE_STILL;

		//rotacja
		sf::Vector2f origin = sf::Vector2f(_birdSprite.getGlobalBounds().width / 2, _birdSprite.getGlobalBounds().height / 2);
		_birdSprite.setOrigin(origin);
		_rotation = 0;
	}

	void Bird::Draw() {

		_data->window.draw(_birdSprite);
	}

	void Bird::Animate(float delta) {

		if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size()) {
			
			if (_animationIterator < _animationFrames.size() - 1) { //sprawdza czy mamy jeszcze jakis zapas frame'ow

				_animationIterator++;
			}
			else {
				_animationIterator = 0;
			}

			_birdSprite.setTexture(_animationFrames.at(_animationIterator));

			_clock.restart();
		}
	}

	void Bird::Update(float delta) {

		if (BIRD_STATE_FALLING == _birdState) {
			_birdSprite.move(0, GRAVITY * delta);

			//rotacja
			_rotation += ROTATION_SPEED * delta;

			if (_rotation > 25.0f) {
				_rotation = 25.0f;
			}

			_birdSprite.setRotation(_rotation);
		}
		else if (BIRD_STATE_FLYING == _birdState) {
			_birdSprite.move(0, -FLYING_SPEED * delta); //-FLYING_SPEED --> zeby lecial w gore

			//rotacja
			_rotation -= ROTATION_SPEED * delta;

			if (_rotation < -25.0f) {
				_rotation = -25.0f;
			}

			_birdSprite.setRotation(_rotation);
		}

		if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION) {
			_movementClock.restart();
			_birdState = BIRD_STATE_FALLING;
		}

		
	}

	void Bird::Tap() {
		_movementClock.restart(); //czas od poprzedniego kliku
		_birdState = BIRD_STATE_FLYING; //FLYING
	}

	//do kolizji
	const sf::Sprite& Bird::GetSprite() const {
		return _birdSprite;
	}
}