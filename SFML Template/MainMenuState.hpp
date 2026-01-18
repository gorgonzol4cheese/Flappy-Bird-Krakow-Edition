#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Flappy {
    class MainMenuState : public State {
    public:
        MainMenuState(GameDataRef data);
        void Init();
        void HandleInput();
        void Update(float delta);
        void Draw(float delta);
    private:
        GameDataRef _data;

        sf::Sprite _background;
        sf::Sprite _title;
        sf::Sprite _levelSelectionButton;

    };
}
