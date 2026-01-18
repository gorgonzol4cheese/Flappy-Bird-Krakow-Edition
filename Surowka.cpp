
#include "Surowka.hpp"
#include "DEFINITIONS.hpp"
#include <random>

namespace Flappy {
    Surowka::Surowka(GameDataRef data, std::string textureName)
        : _data(data), _textureName(std::move(textureName)) {
        // Текстура должна быть загружена в AssetManager в начале игры
    }

    void Surowka::SpawnSurowka(float x, float y) {
        sf::Sprite sprite(this->_data->assets.GetTexture(_textureName));
        sprite.setPosition(x, y);
        _surowkaSprites.push_back(sprite);
    }

    void Surowka::Update(float delta) {
        for (size_t i = 0; i < _surowkaSprites.size(); ) {
            // Двигаем surowka вместе с трубами
            _surowkaSprites[i].move(-PIPE_MOVEMENT_SPEED * delta, 0);

            // Если surowka улетела за экран — удаляем
            if (_surowkaSprites[i].getPosition().x < -_surowkaSprites[i].getGlobalBounds().width) {
                _surowkaSprites.erase(_surowkaSprites.begin() + static_cast<long>(i));
                continue;
            }
            ++i;
        }
    }

    void Surowka::SpawnRandomSurowka(float screenWidth, float screenHeight) {
        if (_surowkaClock.getElapsedTime().asSeconds() > SUROWKA_SPAWN_FREQUENCY) {
            // Настройка рандома
            static std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> dis(
                static_cast<int>(screenHeight * 0.1f),
                static_cast<int>(screenHeight * 0.8f));

            float randomY = static_cast<float>(dis(gen));
            float spawnX = screenWidth + 50.0f; // Появляется чуть за правым краем экрана

            // Создаем surowka
            this->SpawnSurowka(spawnX, randomY);

            _surowkaClock.restart(); // Сбрасываем таймер
        }
    }

    void Surowka::DrawSurowka() {
        for (auto& surowka : _surowkaSprites) {
            this->_data->window.draw(surowka);
        }
    }

    const std::vector<sf::Sprite>& Surowka::GetSprites() const {
        return _surowkaSprites;
    }

    void Surowka::RemoveSurowka(int index) {
        _surowkaSprites.erase(_surowkaSprites.begin() + index);
    }
}
