
#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "LevelSelectState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
 namespace Flappy {
     MainMenuState::MainMenuState(GameDataRef data): _data(data){

     }
     void MainMenuState::Init() {
         _data->assets.LoadTexture(MAIN_MENU_BACKGROUND_TEXTURE,
             MAIN_MENU_BACKGROUND_FILEPATH);
         _data->assets.LoadTexture(GAME_TITLE_TEXTURE, GAME_TITLE_FILEPATH);
         _data->assets.LoadTexture(PLAY_BUTTON_TEXTURE, PLAY_BUTTON_FILEPATH);
         _background.setTexture(_data->assets.GetTexture(MAIN_MENU_BACKGROUND_TEXTURE));
         _title.setTexture(_data->assets.GetTexture(GAME_TITLE_TEXTURE));
         _levelSelectionButton.setTexture(_data->assets.GetTexture(PLAY_BUTTON_TEXTURE));
         _title.setPosition( (SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2),_title.getGlobalBounds().height/2);
         _levelSelectionButton.setPosition((SCREEN_WIDTH / 2) - (_levelSelectionButton.getGlobalBounds().width / 2),
             (SCREEN_HEIGHT / 2 )- (_levelSelectionButton.getGlobalBounds().height / 2));
     }
     void MainMenuState::HandleInput() {
         sf::Event event;
         while (_data->window.pollEvent(event)) {
             if (sf::Event::Closed == event.type) {
                 _data->window.close();
             }
             if (_data->input.IsSpriteClicked(_levelSelectionButton, sf::Mouse::Left, _data->window)) {
                 _data->machine.AddState(StateRef(new LevelSelectState(_data)), true);
             }
         }
     }
     void MainMenuState::Update(float delta) {

     }
     void MainMenuState::Draw(float delta) {
         _data->window.clear();
         _data->window.draw(_background);
         _data->window.draw(_title);
         _data->window.draw(_levelSelectionButton);
         _data->window.display();
     }


 }
