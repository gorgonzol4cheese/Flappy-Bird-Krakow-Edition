#include <iostream>
#include "Pipe.h"

namespace Flappy {
	Pipe::Pipe(GameDataRef data) :_data(data) {
		_landHeight = _data->assets.GetTexture("Land").getSize().y; //dzieki temu rury nir sa w powietrzu
		_pipeSpawnYOffset = 0;
	}

	void Pipe::SpawnBottomPipe() {
		sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));

		sprite.setPosition(_data->window.getSize().x, _data->window.getSize().y - sprite.getGlobalBounds().height - _pipeSpawnYOffset);

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnTopPipe(){
		sf::Sprite sprite(_data->assets.GetTexture("Pipe Down"));

		sprite.setPosition(_data->window.getSize().x, - _pipeSpawnYOffset); //tutaj 0 bo dolna rura

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnInvisiblePipe() {//niewidziala bo sie bugowalo
		sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));

		sprite.setPosition(_data->window.getSize().x, _data->window.getSize().y - sprite.getGlobalBounds().height);
		sprite.setColor(sf::Color(0, 0, 0, 0));

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnScoringPipe() {
		sf::Sprite sprite(_data->assets.GetTexture("Scoring Pipe"));

		sprite.setPosition(_data->window.getSize().x, 0);

		scoringPipes.push_back(sprite);
	}

	void Pipe::MovePipes(float delta) {
		for (unsigned short int i = 0; i < pipeSprites.size(); i++) {

			//do problemow z pamiecia, bo rosla za kazdym razem jak nowa rura sie pojawiala
			if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getGlobalBounds().width) {
				pipeSprites.erase(pipeSprites.begin() + i);
				//jesli nie widac ich na ekranie (bo wyszly poza ekran od lewej) to je usuwa
				//- pipeSprites.at(i).getGlobalBounds().width --> zeby nie znikaly od razu jak dotkna lewej sciany ekranu,
				//tylko gdy calkowicie znikna z ekranu od lewej
			}
			else {
				float movement = PIPE_MOVEMENT_SPEED * delta; //dla frame'ow

				pipeSprites.at(i).move(-movement, 0); //-movement zeby lecialo w lewo
			}
		}

		for (unsigned short int i = 0; i < scoringPipes.size(); i++) {

			if (scoringPipes.at(i).getPosition().x < 0 - scoringPipes.at(i).getGlobalBounds().width) {
				scoringPipes.erase(scoringPipes.begin() + i);
			}
			else {
				float movement = PIPE_MOVEMENT_SPEED * delta;

				scoringPipes.at(i).move(-movement, 0);
			}
		}
	}

	void Pipe::DrawPipes() {
		for (unsigned short int i = 0; i < pipeSprites.size(); i++) {
			_data->window.draw(pipeSprites.at(i));
		}
	}

	void Pipe::RandomisePipeOffset() {
		_pipeSpawnYOffset = rand() % (_landHeight + 1); //randomizuje od 0 do wysokosci podloza
	}

	const vector<sf::Sprite>& Pipe::GetSprites() const {
		return pipeSprites;
	}

	vector<sf::Sprite>& Pipe::GetScoringSprites(){
		return scoringPipes;
	}
}