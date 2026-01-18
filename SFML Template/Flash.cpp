#include "Flash.hpp"

namespace Flappy {
    Flash::Flash(GameDataRef data):_data(data) {
        _shape = sf::RectangleShape(sf::Vector2f(_data->window.getSize()));
        _shape.setFillColor(sf::Color(255,255,255,0));//будет белый
        _flashOn = true;
    }
    void Flash::Show(float delta) {
        if (_flashOn) {
            int alpha =(int)_shape.getFillColor().a+(FLASH_SPEED*delta);
            if (alpha >= 255){
                alpha = 255.0f;
            _flashOn = false;
            }
            _shape.setFillColor(sf::Color(255,255,255,alpha));
        }
        else {int alpha =(int)_shape.getFillColor().a-(FLASH_SPEED*delta);
            if (alpha <= 0.0f){
                alpha = 0.0f;
                _flashOn = false;
            }
            _shape.setFillColor(sf::Color(255,255,255,alpha));
        }
    }
    void Flash::Draw() {
        _data->window.draw(_shape);

    }


}
