#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"
#include "Surowka.hpp"

namespace Flappy {
    class GameState : public State {
    public:
        GameState(GameDataRef data, int level = 1);
        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);
    private:
        GameDataRef _data;

        sf::Sprite _background;
        Pipe *pipe;
        Land *land;
        Bird *bird;
        Collision collision;
        Flash *flash;
        HUD *hud;
        Surowka *surowka;
        sf::Clock _pipeSpawnClock;
        sf::Clock _gameOverClock;
        bool _gameOverStarted;
        bool _gameOverDisplayed;

        int _gameState;

        int _score;
        int _level;
        int _surowkaCollected;
        sf::Text _surowkaText;


    };
}
