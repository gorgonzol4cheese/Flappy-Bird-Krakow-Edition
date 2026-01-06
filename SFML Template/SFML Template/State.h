#pragma once

namespace Flappy {
	class State {//transkacje pomiedzy stanami gry, klasa abstrakcyjna, bo = 0;
	public:
		//kazdy ekran w grze - menu, czy fatyczna gra musi wykonywac te rzeczy
		virtual void Init() = 0; //wczytywanie tekstur itp.
		virtual void HandleInput() = 0; //sprawdzanien co klika gracz
		virtual void Update() = 0; //updatowanie np poruszania sie, przeliczanie logiki gry
		virtual void Draw(float delta) = 0; //"rysowanie" na ekranie, np. poruszania sie

		virtual void Pause(){} //kiedy pauzujemy
		virtual void Resume(){} //pozbycie sie pauzy
	};
}