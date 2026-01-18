
#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"

#include <iostream>
#include <fstream>
 namespace Flappy {
     GameState::GameState(GameDataRef data, int level): _data(data), _level(level){

     }
   void GameState::Init() {
    // 1. Ładowanie tekstur do pamięci (AssetManager)
    // Każda tekstura jest ładowana z dysku pod unikalną nazwą, aby zapobiec duplikatom
    _data->assets.LoadTexture(GAME_BACKGROUND_TEXTURE, GAME_BACKGROUND_FILEPATH);
    _data->assets.LoadTexture(PIPE_UP_TEXTURE, PIPE_UP_FILEPATH);
    _data->assets.LoadTexture(PIPE_DOWN_TEXTURE, PIPE_DOWN_FILEPATH);
    _data->assets.LoadTexture("Land", LAND_FILEPATH);

    // Ładowanie klatek animacji ptaka
    _data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
    _data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
    _data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
    _data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);

    // Ładowanie rur punktowych, czcionek oraz surowców
    _data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
    _data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
    if (_level == 2) {
        _data->assets.LoadTexture("Item", STAL_FILEPATH);
    } else {
        _data->assets.LoadTexture("Item", SUROWKA_FILEPATH);
    }

    // 2. Tworzenie instancji obiektów gry
    // Dynamiczna alokacja pamięci dla głównych elementów rozgrywki
    pipe = new Pipe(_data);       // Przeszkody
    land = new Land(_data);       // Podłoże
    bird = new Bird(_data);       // Gracz (ptak)
    flash = new Flash(_data);     // Efekt błysku po uderzeniu
    hud = new HUD(_data);         // Interfejs (wynik)
    surowka = new Surowka(_data, "Item"); // Przedmioty do zbierania

    // 3. Konfiguracja początkowa środowiska
    _background.setTexture(_data->assets.GetTexture(GAME_BACKGROUND_TEXTURE));
    _score = 0;                   // Resetowanie wyniku punktowego
    hud->UpdateScore(_score);     // Aktualizacja wyświetlacza wyniku

    // 4. Inicjalizacja licznika surowców i tekstu interfejsu
    _surowkaCollected = 0;
    _surowkaText.setFont(_data->assets.GetFont("Flappy Font"));
    if (_level == 2) {
        _surowkaText.setString("Stal: 0");
    } else {
        _surowkaText.setString("Surowka: 0"); // Tekst widoczny podczas gry
    }
    _surowkaText.setCharacterSize(32);
    _surowkaText.setFillColor(sf::Color::White);
    _surowkaText.setPosition(20.0f, 20.0f); // Pozycjonowanie w lewym górnym rogu

    // 5. Ustawienie flag stanu gry
    _gameState = GameStates::eReady; // Gra czeka na start (pierwsze kliknięcie)
    _gameOverStarted = false;
    _gameOverDisplayed = false;
}
     void GameState::HandleInput() {
         sf::Event event;
         while (_data->window.pollEvent(event)) {
             if (sf::Event::Closed == event.type) {
                 _data->window.close();
             }
             if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window)) {
                 if (GameStates::eGameOver!=_gameState) {
                     _gameState=GameStates::ePlaying;
                     bird->Tap();
                 }
             }
         }
     }
     void GameState::Update(float delta) {
         if (GameStates::eGameOver!=_gameState) {
             bird->Animate(delta);
             land->MoveLand(delta);
         }
         if (GameStates::ePlaying==_gameState) {
             pipe->MovePipes(delta);
             surowka->Update(delta);
             if (_pipeSpawnClock.getElapsedTime().asSeconds() >= PIPE_SPAWN_FREQUENCY) {
                 pipe->RandomisePipeOffset();
                 pipe->SpawnInvisiblePipe();
                 pipe->SpawnBottomPipe();
                 pipe->SpawnTopPipe();
                 pipe->SpawnScoringPipe();

                 float pipeHeight = static_cast<float>(_data->assets.GetTexture(PIPE_UP_TEXTURE).getSize().y);
                 float gapTop = pipeHeight - static_cast<float>(pipe->GetSpawnYOffset());
                 float gapHeight = static_cast<float>(_data->window.getSize().y) - (2.0f * pipeHeight);
                 float margin = 20.0f;
                 if (gapHeight > (margin * 2.0f)) {
                     float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                     float surowkaY = gapTop + margin + t * (gapHeight - (margin * 2.0f));
                     float spawnX = static_cast<float>(_data->window.getSize().x) + 50.0f;
                     surowka->SpawnSurowka(spawnX, surowkaY);
                 }

                 _pipeSpawnClock.restart();
             }
            bird->Update(delta);
            std::vector<sf::Sprite> landSprites= land->GetSprites();
            for (int i=0; i<landSprites.size(); i++) {
                if (collision.CheckSpriteCollision(bird->GetSprite(),0.7f,landSprites.at(i),1.0f)) {
                    _gameState=GameStates::eGameOver;
                    _gameOverClock.restart();
                    _gameOverStarted = true;
                }
            }

             std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
             for (int i = 0; i < pipeSprites.size(); i++) {
                 // Sprawdzenie kolizji ptaka z rurą (z lekkim marginesem 0.625f dla lepszego odczucia gry)
                 if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f,
                     pipeSprites.at(i), 1.0f)) {
                     _gameState = GameStates::eGameOver; // Zmiana stanu na koniec gry
                     _gameOverClock.restart();
                     _gameOverStarted = true;
                 }
             }
             if (GameStates::ePlaying==_gameState) {

                 std::vector<sf::Sprite> &scoringSprites= pipe->GetScoringSprites();
                 for (int i=0; i<scoringSprites.size(); i++) {

                     if (collision.CheckSpriteCollision(bird->GetSprite(),0.625f,scoringSprites.at(i),1.0f)) {
                         _score++;
                       hud->UpdateScore(_score);
                         scoringSprites.erase(scoringSprites.begin()+i);
                     }
                 }
             }

             const std::vector<sf::Sprite> &surowkaSprites = surowka->GetSprites();
             for (size_t i = 0; i < surowkaSprites.size(); ) {
                 if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, surowkaSprites.at(i), 1.0f)) {
                     _surowkaCollected++;
                     if (_level == 2) {
                         _surowkaText.setString("Stal: " + std::to_string(_surowkaCollected));
                     } else {
                         _surowkaText.setString("Surowka: " + std::to_string(_surowkaCollected));
                     }
                     surowka->RemoveSurowka(static_cast<int>(i));
                     if (_level == 1 && _surowkaCollected >= SUROWKA_TO_UNLOCK_NEXT_LEVEL) {
                         std::ofstream unlockFile(LEVEL_UNLOCK_FILEPATH);
                         if (unlockFile.is_open()) {
                             unlockFile << 1;
                         }
                     }
                     if (_level == 2 && _surowkaCollected >= LEVEL_2_GOAL) {
                         //std::cout << "Poziom 2 ukonczony! Stal zebrana." << std::endl;
                     }
                     continue;
                 }
                 ++i;
             }
        }
         if (GameStates::eGameOver==_gameState) {
             flash->Show(delta);
             if (_gameOverStarted && !_gameOverDisplayed &&
                 _gameOverClock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS) {
                 _gameOverDisplayed = true;
                 _data->machine.AddState(StateRef(new GameOverState(_data, _score, _surowkaCollected, _level)),true);
             }
         }
    }

     void GameState::Draw(float delta) {
         _data->window.clear();
         _data->window.draw(_background);
         pipe->DrawPipes();
         land->DrawLand();
         surowka->DrawSurowka();
         bird->Draw();
         flash->Draw();
         hud->Draw();
         _data->window.draw(_surowkaText);
         _data->window.display();
     }


 }
