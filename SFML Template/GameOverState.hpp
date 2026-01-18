#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Flappy {
    class GameOverState : public State {
    public:
        GameOverState(GameDataRef data, int score, int surowka, int level);
        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);
    private:
        GameDataRef _data;

        sf::Sprite _background;
        sf::Sprite _gameOverTitle;
        sf::Sprite _gameOverContainer;
        sf::Sprite _retryButton;


        sf::Text _scoreText;
        sf::Text _highScoreText;
        sf::Text _surowkaText;
        sf::Sprite _menuButton;

        int _score;
        int _highScore;
        int _surowkaCollected;
        int _level;


    };
}
