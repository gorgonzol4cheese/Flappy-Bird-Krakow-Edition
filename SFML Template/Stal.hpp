#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace Flappy {
    class Stal {
    public:
        Stal(GameDataRef data);

        void SpawnStal(float x, float y);
        void Update(float dt);
        void Draw();

        // Возвращает список всех спрайтов стали для проверки коллизий в GameState
        std::vector<sf::Sprite>& GetSprites();

    private:
        GameDataRef _data;
        std::vector<sf::Sprite> _stalSprites;
    };
}