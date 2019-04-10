#include "FSMObj.h"

void FSMObj::FSMObj(JSONError* err) {
	this->currentState = statesObj::INITIAL;
	this->err = err;
}
statesObj FSMObj::getState() {
	return currentState;
}

void FSMObj::cycle(char s) {

}

eventsObj FSMObj::getEvent(char s) {
  
}