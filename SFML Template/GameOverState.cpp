
#include <sstream>
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include <iostream>
#include <fstream>
#include "MainMenuState.hpp"
 namespace Flappy {
     GameOverState::GameOverState(GameDataRef data, int score, int surowka, int level)
        : _data(data), _score(score), _surowkaCollected(surowka), _level(level) {

     }
     void GameOverState::Init() {
         _highScore = 0;
         std::ifstream readFile(HIGH_SCORE_FILEPATH);
         if (readFile.is_open()) {
             if (!(readFile >> _highScore)) {
                 _highScore = 0;
             }
         }

         std::ofstream writeFile(HIGH_SCORE_FILEPATH);
         if (writeFile.is_open()) {
             if (_score > _highScore) {
                 _highScore = _score;
             }
             writeFile << _highScore;
         }
         writeFile.close();

         _data->assets.LoadTexture(GAME_OVER_BACKGROUND_TEXTURE,
             GAME_OVER_BACKGROUND_FILEPATH);
         _data->assets.LoadTexture("Game Over Title",
             GAME_OVER_TITLE_FILEPATH);
         if (_level == 2) {
             _data->assets.LoadTexture("Game Over Body",
                 GAME_OVER_BODY_LEVEL_2_FILEPATH);
         } else {
             _data->assets.LoadTexture("Game Over Body",
                 GAME_OVER_BODY_FILEPATH);
         }
         _data->assets.LoadTexture("Play Button",
             PLAY_BUTTON_FILEPATH);
         _data->assets.LoadFont("Flappy Font",
             FLAPPY_FONT_FILEPATH);
         _background.setTexture(_data->assets.GetTexture(GAME_OVER_BACKGROUND_TEXTURE));
         _gameOverTitle.setTexture(_data->assets.GetTexture("Game Over Title"));
         _gameOverContainer.setTexture(_data->assets.GetTexture("Game Over Body"));
         _retryButton.setTexture(_data->assets.GetTexture("Play Button"));

         _gameOverContainer.setPosition((_data->window.getSize().x / 2)-(_gameOverContainer.getGlobalBounds().width/2),
             (_data->window.getSize().y / 2)-(_gameOverContainer.getGlobalBounds().height/2));
         _gameOverTitle.setPosition((_data->window.getSize().x / 2)-(_gameOverTitle.getGlobalBounds().width/2),
             _gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height*1.2));

         _retryButton.setPosition((_data->window.getSize().x / 2)-(_retryButton.getGlobalBounds().width/2),
            _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height+_retryButton.getGlobalBounds().height*0.2f);

         _scoreText.setFont(_data->assets.GetFont("Flappy Font"));
         _scoreText.setString(std::to_string(_score));
         _scoreText.setCharacterSize(56);
         _scoreText.setFillColor(sf::Color::White);
         _scoreText.setOrigin(_scoreText.getGlobalBounds().width/2,_scoreText.getGlobalBounds().height/2);
         _scoreText.setPosition(_data->window.getSize().x / 10*7.25,_data -> window.getSize().y / 2.15);

         _highScoreText.setFont(_data->assets.GetFont("Flappy Font"));
         _highScoreText.setString(std::to_string(_highScore));
         _highScoreText.setCharacterSize(56);
         _highScoreText.setFillColor(sf::Color::White);
         _highScoreText.setOrigin(_highScoreText.getGlobalBounds().width/2,_highScoreText.getGlobalBounds().height/2);
         _highScoreText.setPosition(_data->window.getSize().x / 10*7.25,_data -> window.getSize().y / 1.78);

         // 1. Настройка текста
         _surowkaText.setFont(this->_data->assets.GetFont("Flappy Font")); // Используем ваш шрифт
         _surowkaText.setString(std::to_string(_surowkaCollected)); // Передаем количество собранного
         _surowkaText.setCharacterSize(56); // Подберите размер, как у обычного score
         _surowkaText.setFillColor(sf::Color::White); // Или цвет, который вам нравится

         // 2. Позиционирование
         // Вам нужно подогнать координаты X и Y, чтобы текст встал под надписью SUROWKA
         _surowkaText.setOrigin(_surowkaText.getGlobalBounds().width / 2, _surowkaText.getGlobalBounds().height / 2);
         _surowkaText.setPosition(_data->window.getSize().x / 3.3f, _data->window.getSize().y / 1.9f);

         _data->assets.LoadTexture("Menu Button", MENU_BUTTON_FILEPATH);
         _menuButton.setTexture(_data->assets.GetTexture("Menu Button"));

         // Позиционируем кнопку (например, ниже кнопки рестарта)
         _menuButton.setPosition(_retryButton.getPosition().x,
                        _retryButton.getPosition().y + _retryButton.getGlobalBounds().height + 20);
     }
     void GameOverState::HandleInput() {
         sf::Event event;
         while (_data->window.pollEvent(event)) {
             if (sf::Event::Closed == event.type) {
                 _data->window.close();
             }
            if (_data->input.IsSpriteClicked(_retryButton,sf::Mouse::Left,_data->window)) {
                _data->machine.AddState(StateRef(new GameState(_data, _level)),true);
            }
             // Проверка клика по кнопке меню
             if (_data->input.IsSpriteClicked(_menuButton, sf::Mouse::Left, _data->window)) {
                 // Переходим в MainMenuState
                 _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
             }
        }
     }
     void GameOverState::Update(float delta) {

     }
     void GameOverState::Draw(float delta) {
         _data->window.clear();
         _data->window.draw(_background);
         _data->window.draw(_gameOverTitle);
         _data->window.draw(_gameOverContainer);
         _data->window.draw(_retryButton);
         _data->window.draw(_scoreText);
         _data->window.draw(_highScoreText);
         _data->window.draw(_surowkaText);
         _data->window.draw(_menuButton);
         _data->window.display();
     }


 }
