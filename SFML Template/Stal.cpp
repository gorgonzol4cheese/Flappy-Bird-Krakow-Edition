#include "Stal.hpp"
#include "DEFINITIONS.hpp"

namespace Flappy {
    Stal::Stal(GameDataRef data) : _data(data) {}

    void Stal::SpawnStal(float x, float y) {
        // Подхватывает текстуру, загруженную в GameState::Init под именем "Item"
        sf::Sprite sprite(this->_data->assets.GetTexture("Item")); 
        sprite.setPosition(x, y);
        _stalSprites.push_back(sprite);
    }

    void Stal::Update(float dt) {
        for (int i = 0; i < _stalSprites.size(); i++) {
            // Движение влево вместе с трубами и землей
            _stalSprites[i].move(-PIPE_MOVEMENT_SPEED * dt, 0);

            // Удаление, если улетела за экран
            if (_stalSprites[i].getPosition().x < -100) {
                _stalSprites.erase(_stalSprites.begin() + i);
            }
        }
    }

    void Stal::Draw() {
        for (auto& s : _stalSprites) {
            _data->window.draw(s);
        }
    }

    std::vector<sf::Sprite>& Stal::GetSprites() { return _stalSprites; }
}