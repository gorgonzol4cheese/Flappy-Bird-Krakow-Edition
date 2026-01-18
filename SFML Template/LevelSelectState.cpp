#include <iostream>
#include <fstream>
#include "LevelSelectState.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

namespace Flappy {
    LevelSelectState::LevelSelectState(GameDataRef data) : _data(data) {}

    void LevelSelectState::Init() {
        // 1. Загрузка текстур
        _data->assets.LoadTexture("Level Selection Background", MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Level Button", PLAY_BUTTON_FILEPATH);
        _data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

        _background.setTexture(_data->assets.GetTexture("Level Selection Background"));

        // 2. Логика разблокировки (зависит от ваших достижений)
        CheckLevelUnlockStatus();

        // 3. Настройка кнопок
        _level1Button.setTexture(_data->assets.GetTexture("Level Button"));
        _level1Button.setPosition(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f);

        _level2Button.setTexture(_data->assets.GetTexture("Level Button"));
        _level2Button.setPosition(SCREEN_WIDTH / 3.0f * 2.0f, SCREEN_HEIGHT / 2.0f);
        if (!_isLevel2Unlocked) {
            _level2Button.setColor(sf::Color(150, 150, 150));
        }
        
        // Центрируем кнопки
        _level1Button.setOrigin(_level1Button.getGlobalBounds().width / 2, _level1Button.getGlobalBounds().height / 2);
        _level2Button.setOrigin(_level2Button.getGlobalBounds().width / 2, _level2Button.getGlobalBounds().height / 2);

        _level1Text.setFont(_data->assets.GetFont("Flappy Font"));
        _level1Text.setString("Level 1");
        _level1Text.setCharacterSize(28);
        _level1Text.setFillColor(sf::Color::White);
        _level1Text.setOrigin(_level1Text.getGlobalBounds().width / 2, _level1Text.getGlobalBounds().height / 2);
        _level1Text.setPosition(_level1Button.getPosition());

        _level2Text.setFont(_data->assets.GetFont("Flappy Font"));
        _level2Text.setString("Level 2");
        _level2Text.setCharacterSize(28);
        _level2Text.setFillColor(sf::Color::White);
        _level2Text.setOrigin(_level2Text.getGlobalBounds().width / 2, _level2Text.getGlobalBounds().height / 2);
        _level2Text.setPosition(_level2Button.getPosition());

        _lockText.setFont(_data->assets.GetFont("Flappy Font"));
        _lockText.setString("Locked");
        _lockText.setCharacterSize(20);
        _lockText.setFillColor(sf::Color::White);
        _lockText.setOrigin(_lockText.getGlobalBounds().width / 2, _lockText.getGlobalBounds().height / 2);
        _lockText.setPosition(_level2Button.getPosition().x,
            _level2Button.getPosition().y + _level2Button.getGlobalBounds().height / 2 + 16.0f);
    }

    void LevelSelectState::HandleInput() {
        sf::Event event;
        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                _data->window.close();
            }

            // Клик по Уровню 1
            if (_data->input.IsSpriteClicked(_level1Button, sf::Mouse::Left, _data->window)) {
                // Передаем "1" в GameState
                _data->machine.AddState(StateRef(new GameState(_data, 1)), true);
            }

            // Клик по Уровню 2
            if (_data->input.IsSpriteClicked(_level2Button, sf::Mouse::Left, _data->window)) {
                if (_isLevel2Unlocked) {
                    _data->machine.AddState(StateRef(new GameState(_data, 2)), true);
                } else {
                    //std::cout << "Соберите 15 surowka на 1 уровне!" << std::endl;
                }
            }
        }
    }

    void LevelSelectState::Update(float dt) {}

    void LevelSelectState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_level1Button);
        _data->window.draw(_level2Button);
        _data->window.draw(_level1Text);
        _data->window.draw(_level2Text);
        if (!_isLevel2Unlocked) {
            _data->window.draw(_lockText);
        }
        _data->window.display();
    }

    void LevelSelectState::CheckLevelUnlockStatus() {
        _isLevel2Unlocked = false;
        //return;
        std::ifstream unlockFile(LEVEL_UNLOCK_FILEPATH);
        if (unlockFile.is_open()) {
            int value = 0;
            if (unlockFile >> value) {
                _isLevel2Unlocked = (value != 0);
            }
        }
    }
}
