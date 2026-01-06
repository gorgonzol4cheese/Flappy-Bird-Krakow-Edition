#include "StateMachine.h"
#include <iostream>
using namespace std;

namespace Flappy {
	//MECHANIKA ZMIAN STANOW
	void StateMachine::AddState(StateRef newState, bool isReplacing) { //funkcja zapewnia przeechowanie nowego stanu w "poczekalni"?
		this->_isAdding = true; //nadaje "flage", zmiany zachodza na koncu
		this->_isReplacing = isReplacing; //wyrzucic LUB odlozyc
		//zapisuje isReplacing, ktora przyszla z "zewnatrz" do _isReplacing (zmiennej calej klasy)

		this->_newState = move(newState); //przekazanie arg funkcji przestaje byc wlascicielem stanu
		//i przekazuje go zmiennej _newState
	}

	void StateMachine::RemoveState() {
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges() {

		//Usuwanie State
		if (this->_isRemoving && !this->_states.empty()) {//sprawdza czy stos NIE JEST pusty
			this->_states.pop(); //zdejmowanie State "gornego"

			if (!this->_states.empty()) { //jesli pod spodem stos NIE JEST pusty
				this->_states.top()->Resume(); //to powraca do tego State, ktory byl wczesniej
			}

			this->_isRemoving = false; //zerowanie Flagi
		}

		//Dodawanie i Zamiana State
		if (this->_isAdding) {

			if (!this->_states.empty()) { //jesli stos NIE JEST pusty

				if (this->_isReplacing) { //jesli jest zaznaczone
					this->_states.pop(); //to aktualny stan gry jest usuwany
				}
				else { //jesli NIE ZMIENIAMY, to aktaulny stan gry jest pauzowany i zostaje na stosie
					this->_states.top()->Pause();
				}
			}

			this->_states.push(move(this->_newState)); //nowy stan jest wrzucant na gore
			this->_states.top()->Init(); //inicjalizacja tekstur itp.

			this->_isAdding = false; //zerowanie Flagi
		}
	}

	StateRef& StateMachine::GetActiveState() { //referencia aktualnego stanu gry
		return this->_states.top();
	}
}