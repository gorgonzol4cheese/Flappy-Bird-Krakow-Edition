#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024

#define SPLASH_STATE_SHOW_TIME 3.0//сколько хотим что б заставка
//была видна прежде чем перейти в главное меню
#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/background2.png"
#define SPLASH_SCENE_BACKGROUND_TEXTURE "background2"

#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/background2.png"
#define GAME_BACKGROUND_FILEPATH "Resources/res/background2.png"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/res/background2.png"

#define GAME_TITLE_FILEPATH "Resources/res/Krakow Edition Title NoBacgroundCut.png"
#define PLAY_BUTTON_FILEPATH "Resources/res/PlayButton.png"

#define PIPE_UP_FILEPATH "Resources/res/WielkiPoiecDluzszy.png"
#define PIPE_DOWN_FILEPATH "Resources/res/WielkiPoiecDluzszyDown.png"
#define SCORING_PIPE_FILEPATH "Resources/res/InvisibleScoringPipe.png"

#define MAIN_MENU_BACKGROUND_TEXTURE "Main Menu Background"
#define GAME_BACKGROUND_TEXTURE "Game Background"
#define GAME_OVER_BACKGROUND_TEXTURE "Game Over Background"
#define GAME_TITLE_TEXTURE "Game Title"
#define PLAY_BUTTON_TEXTURE "Play Button"
#define PIPE_UP_TEXTURE "Pipe Up"
#define PIPE_DOWN_TEXTURE "Pipe Down"
#define STAL_TEXTURE "Stal"

#define LAND_FILEPATH "Resources/res/Land.png"

#define BIRD_FRAME_1_FILEPATH "Resources/res/bird-01.png"
#define BIRD_FRAME_2_FILEPATH "Resources/res/bird-02.png"
#define BIRD_FRAME_3_FILEPATH "Resources/res/bird-03.png"
#define BIRD_FRAME_4_FILEPATH "Resources/res/bird-04.png"

#define FLAPPY_FONT_FILEPATH "Resources/fonts/FlappyFont.ttf"
#define GAME_OVER_TITLE_FILEPATH "Resources/res/Game-Over-Title.png"
#define GAME_OVER_BODY_FILEPATH "Resources/res/Game-Over-Body.png"

#define HIGH_SCORE_FILEPATH "Resources/HighScore.txt"
#define LEVEL_UNLOCK_FILEPATH "Resources/LevelUnlock.txt"

#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_FREQUENCY 2.0f//каждые три секунды появляеться новый трубы

#define BIRD_ANIMATION_DURATION 0.5f
#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALLING 2
#define BIRD_STATE_FLYING 3

#define GRAVITY 350.0f
#define FLYING_SPEED 350.0f
#define FLYING_DURATION 0.25f
#define ROTATION_SPEED 100.0f

enum  GameStates {
    eReady,
    ePlaying,
    eGameOver
};

#define FLASH_SPEED 1500.0f
#define TIME_BEFORE_GAME_OVER_APPEARS 1.5f

#define SUROWKA_FILEPATH "Resources/res/surowka.png"
#define SUROWKA_TO_UNLOCK_NEXT_LEVEL 15
#define SUROWKA_SPAWN_FREQUENCY 2.0f

#define LEVEL_1_GOAL 15
#define LEVEL_2_GOAL 25
#define PIPES_LEVEL_2_DOWN_FILEPATH "Resources/res/WielkiPoiecDluzszyDown.png"
#define PIPES_LEVEL_2_UP_FILEPATH "Resources/res/WielkiPoiecDluzszy.png"

#define GAME_OVER_BODY_LEVEL_2_FILEPATH "Resources/res/Game-Over-Body2.png"
#define STAL_FILEPATH "Resources/res/Stal.png"

#define MENU_BUTTON_FILEPATH "Resources/res/menu_button.png"
