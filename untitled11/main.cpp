
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <string>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024

int main() {
    // 1. Создаем окно
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }),
        "Flappy Bird: Krakow Edition");
    window.setFramerateLimit(60);

    // 2. Создаем и загружаем шрифт
    //добавляем ресурсы
    sf::Font font;
    if (!font.openFromFile("assets/EarthTheory.otf")) {
        std::cerr << "Error" << std::endl;
        return -1;
    }
    sf::Texture dragonTex, bgTex, pipeTex;
    if (!dragonTex.loadFromFile("assets/dragon.png")) return -1;
    if (!bgTex.loadFromFile("assets/fon1.png")) return -1;
    if (!pipeTex.loadFromFile("assets/pipe.png")) return -1;
    // --- ОБЪЕКТЫ ---
    sf::Sprite dragon(dragonTex);
    sf::Sprite background(bgTex);

    //масштабируем фон под размер экрана
    background.setScale({(float)SCREEN_WIDTH / bgTex.getSize().x,
        (float)SCREEN_HEIGHT/bgTex.getSize().y});


    // 3. Переменные состояния
    float velocity = 0.f;
    const float gravity = 0.6f;
    int Score = 0;
    int BestScore = 0;
    bool isPlaying = false;

    // 4. Настройка кнопки PLAY
    sf::RectangleShape playButton({200.f, 80.f});
    playButton.setOrigin({100.f, 40.f});
    playButton.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f});
    playButton.setFillColor(sf::Color::Black);
    playButton.setOutlineColor(sf::Color::Red);
    playButton.setOutlineThickness(5.f);

    // 5. Настройка текстов (используем font)
    sf::Text playText(font, "PLAY", 40);
    playText.setFillColor(sf::Color::White);
    // Центрируем текст внутри кнопки
    sf::FloatRect pBounds = playText.getLocalBounds();
    playText.setOrigin({pBounds.size.x / 2.f, pBounds.size.y / 2.f});
    playText.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 5.f});

    sf::Text scoreDisplay(font, "", 30);
    scoreDisplay.setPosition({20.f, 20.f});
    scoreDisplay.setFillColor(sf::Color::White);

    // ГЛАВНЫЙ ЦИКЛ ПРИЛОЖЕНИЯ
    while (window.isOpen()) {
        // --- ОБРАБОТКА СОБЫТИЙ ---
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Проверка нажатия на кнопку "PLAY"
            if (!isPlaying) {
                if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseBtn->position);
                    if (playButton.getGlobalBounds().contains(mousePos)) {
                        isPlaying = true; // Переключаемся в игру
                        dragon.setPosition({200.f, SCREEN_HEIGHT/ 2.f});
                        velocity = 0;
                        Score = 0;
                    }
                }
            }else {
                //прыжок в игре
                if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                    if (key->code == sf::Keyboard::Key::Space)velocity = - 10.f;
                }
            }
        }

        // --- ЛОГИКА ---
        //LOGIKA
        if (isPlaying) {
            velocity += gravity;
            dragon.move({0.f, velocity});

            // Проигрыш при падении
            if (dragon.getPosition().y > SCREEN_HEIGHT || dragon.getPosition().y < 0) {
                isPlaying = false;
            }
        }

        if (!isPlaying) {
            scoreDisplay.setString("Best score: " + std::to_string(BestScore) +
                                 "\nScore: " + std::to_string(Score));
        }

        // --- ОТРИСОВКА ---
        window.clear(sf::Color::Black); // Черный фон меню

        if (!isPlaying) {
            // Рисуем меню
            //RYSUJEMY MENU
            window.draw(scoreDisplay);
            window.draw(playButton);
            window.draw(playText);
        } else {
            window.draw(background);
            window.draw(dragon);
            sf::Text scoreText(font, "Score: "+ std::to_string(Score), 30);
            window.draw(scoreText);
            //TUTAJ KOD DLA GRY
            // Здесь будет код самой игры, когда ты его добавишь
            // Пока просто закрасим экран синим, чтобы видеть, что кнопка сработала

        }

        window.display();
    }

    return 0;
}