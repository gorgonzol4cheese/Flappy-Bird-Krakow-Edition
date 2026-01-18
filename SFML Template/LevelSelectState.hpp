#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Flappy {
    class LevelSelectState : public State {
    public:
        LevelSelectState(GameDataRef data);

        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);

    private:
        GameDataRef _data;
        sf::Sprite _background;
        sf::Sprite _level1Button;
        sf::Sprite _level2Button;
       // sf::Sprite _level3Button;
        sf::Sprite _backButton;

        sf::Text _level1Text;
        sf::Text _level2Text;
        sf::Text _lockText;

        bool _isLevel2Unlocked;
       // bool _isLevel3Unlocked;
        
        void CheckLevelUnlockStatus();
    };
}
