#include "Game.h"
#include "SplashState.h"

#include <stdlib.h>
#include <time.h>

namespace Flappy {

	Game::Game(int width, int height, string title) {

		srand(time(NULL)); //randomizuje seed

		//tworzenie okna
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

		//dodanie 'pierwszego' stanu gry
		_data->machine.AddState(StateRef(new SplashState(this->_data)));

		//odpalenie gry
		this->Run();
	}
	
	//FUNCKJA RUN - Game Loop + staly krok czasowy
	//staly krok czasowy musi istniec aby nie bylo rozbieznosci przesuwania postaci na komputerach roznej specyfikacji
	void Game::Run() {

		float newTime, frameTime, interpolation; //interpolacja - aktualizacja ruchu (zapewnia wygladzenie ruchu), przy ostatecznych szarpaniu

		float currentTime = this->_clock.getElapsedTime().asSeconds(); //czas na zegarku w momencie startu petli
		float accumulator = 0.0f; //bank czasu - on odpowiada za skladowanie ulamkow sekund, ktore minely

		//petla dziala tak dlugo jak otwarte jest okno
		while (this->_data->window.isOpen()) {
			this->_data->machine.ProcessStateChanges(); //sprawdzenie Flag - czy trzeba zmienic Stan Gry (np. ekran z menu na gre)

			newTime = this->_clock.getElapsedTime().asSeconds(); //wlozenie czasu startu zegarka do zmiennej
			frameTime = newTime - currentTime; //frameTime = obliczanie czasu trwania jednej klatki
			//newTime - czas zapisany na poczatku wykonywania petli
			//currentTime - czas zapisany na koncu poprzedniego obiegu petli

			//zabezpieczenie przed zawieszeniem -
			if (frameTime > 0.25f) { //jesli gra zaciela sie na dluzej niz 0.25sek (np. minute) to
				frameTime = 0.25f; //przyjmij, ze minelo 0.25sek
			}
			currentTime = newTime; //
			accumulator += frameTime; //zbieranie czas po ostatnich klatkach

			//klucz do tego aby gra byla plynna, delta = 1/60sek = ok. 0.0166sek
			while (accumulator >= delta) { //zagladamy do akumulatora zebranych klatek, czy wynosi wiecej niz 0.0166sek
				this->_data->machine.GetActiveState()->HandleInput(); //
				this->_data->machine.GetActiveState()->Update(delta); //jesli tak - wywoluje ruch postaci
				accumulator -= delta; //odejmuje z nagromadzonych frameTimes 0.0166sek
			}

			interpolation = accumulator / delta; //obliczamy "procent" ktory zostal z akumulatora klatek - jaki jestesmy w stanie jeszcze wykorzystac
			this->_data->machine.GetActiveState()->Draw(interpolation); //funkcja rysuje gdzie powinnia znalezc sie postac w % danej ostatniej klatki
		}
	}
}