#include <sstream>
#include <iostream>
#include "GameState.h"
#include "DEFINITIONS.h"
#include "GameOverState.h"

namespace Flappy {

	GameState::GameState(GameDataRef data) : _data(data) {

	}

	//Ladowanie tekstury
	void GameState::Init() {

		//zaladowanie tekstury
		_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH); //w zbiorze _data idziemy do assets i ladujemy plik z dysku
		_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		_data->assets.LoadTexture("Land", LAND_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

		//towrzenie obiektow
		pipe = new Pipe(_data);
		land = new Land(_data);
		bird = new Bird(_data);
		flash = new Flash(_data);
		hud = new HUD(_data);

		//odzyskiwanie tekstury
		_background.setTexture(this->_data->assets.GetTexture("Game Background")); //ustawia jako _background wczesnuej zaladowana teksture i ja nazywa

		_score = 0;
		hud->UpdateScore(_score);

		_gameState = GameStates::eReady;
	}

	void GameState::HandleInput() {
		//dla zamykania okna
		sf::Event event;
		while (_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}

			//jesli klika w ekran gry to ptak sie rusza
			if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window)) {
				//sprawdza czy nie ma gameover
				if (GameStates::eGameOver != _gameState) {
					_gameState = GameStates::ePlaying;
					bird->Tap();
				}
			}
		}
	}

	void GameState::Update(float delta) {
		//sprawdza czy nie ma gameover
		if (GameStates::eGameOver != _gameState) {
			bird->Animate(delta);
			land->MoveLand(delta); //funkcja od poruszania podloza
		}

		if (GameStates::ePlaying == _gameState) {

			pipe->MovePipes(delta); //funkcja od poruszania rur

			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY) {

				pipe->RandomisePipeOffset();

				pipe->SpawnInvisiblePipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnScoringPipe();

				clock.restart();
			}
			bird->Update(delta);

			//KOLIZJA Z PODLOZEM
			vector<sf::Sprite> landSprites = land->GetSprites();
			//sprawdzanie czy ptak koliduje
			for (int i = 0; i < landSprites.size(); i++) {
				
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landSprites.at(i), 1.0f)) {
					_gameState = GameStates::eGameOver;

					clock.restart(); //do gameover
				}
			}

			//KOLIZJA Z RURAMI
			vector<sf::Sprite> pipeSprites = pipe->GetSprites();
			//sprawdzanie czy ptak koliduje
			for (int i = 0; i < pipeSprites.size(); i++) {

				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprites.at(i), 1.0f)) {
					_gameState = GameStates::eGameOver;

					clock.restart(); //do gameover
				}
			}

			//dla SCORE PIPES
			if (GameStates::ePlaying == _gameState) {//if zeby nie liczylo dodatkowego punktu po kolizji
				vector<sf::Sprite>& scoringSprites = pipe->GetScoringSprites();
				for (int i = 0; i < scoringSprites.size(); i++) {

					if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f)) {

						_score++;

						hud->UpdateScore(_score);

						scoringSprites.erase(scoringSprites.begin() + i);
					}
				}
			}
		}

		if (GameStates::eGameOver == _gameState) {
			flash->Show(delta);

			//GAMEOVER
			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS) {
				_data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
			}
		}
	}

	void GameState::Draw(float delta) {

		_data->window.clear(); //czysci okno
		_data->window.draw(_background); //rysuje przygotowane przez nas tlo 
		//buffor tylny - komputer maluje tlo w pamieci (window.draw())
		//buffor przedni - obraz ktory widzi uzytkonik na monitorze

		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();

		flash->Draw();

		hud->Draw();

		_data->window.display(); //wyswietla obraz na ekranie monitora (poprzez swap buforow)
	}
}