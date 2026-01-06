#pragma once

#include <iostream>
#include <memory>
#include <stack> //stos

#include "State.h" //plik zawierajacy wszystkie game states

using namespace std;

namespace Flappy {
	typedef unique_ptr<State> StateRef; //usuwanie State ze stosu, usuwa go z pamieci komputera automatycznie

	class StateMachine { //zarzadza wszystkimi GameStates
	public:
		StateMachine() {} //konstruktor
		~StateMachine() {} //dekonstruktor

		void AddState(StateRef newState, bool isReplacing = true);
		//funkcja dodajaca game state do stosu
		//zamienia obencny game state (usuwa go) na nowy
		void RemoveState(); //manualna zmiana game state

		void ProcessStateChanges(); //funkcja dziala w kazdym loopie

		StateRef& GetActiveState(); //zwraca "gorny" game state

	private:
		stack<StateRef> _states; //stos GameStates !!!
		StateRef _newState; //ostatnie game state do dodania

		//sledzi czy usuwamy, dodajemy czy zamieniamy game state
		bool _isRemoving; //Flaga usuwania
		bool _isAdding; //Flaga dodawania
		bool _isReplacing; //Flaga zamiany
	};
}