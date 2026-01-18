#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include <string>

namespace Flappy {
    class Surowka {
    public:
        Surowka(GameDataRef data, std::string textureName = "Surowka");

        // Tworzy surowkę w konkretnych współrzędnych
        void SpawnSurowka(float x, float y);

        // Tworzy surowkę w losowej pozycji
        void SpawnRandomSurowka(float screenWidth, float screenHeight);

        // Renderuje (rysuje) wszystkie aktywne surowki na ekranie
        void DrawSurowka();

        // Aktualizuje pozycję surowek (ruch wraz z poziomem, analogicznie do rur)
        void Update(float delta);

        // Zwraca listę wszystkich surowek w celu sprawdzenia kolizji
        const std::vector<sf::Sprite>& GetSprites() const;

        // Usuwa konkretną surowkę z listy na podstawie jej indeksu
        void RemoveSurowka(int index);

    private:
        GameDataRef _data;
        sf::Clock _surowkaClock;
        std::vector<sf::Sprite> _surowkaSprites;
        std::string _textureName;
    };
}
