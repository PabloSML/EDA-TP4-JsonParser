#pragma once
#include "JSONError.h"

enum statesArray{INITIAL}:

class FSMArray {
public:
	FSMArray(JSONError err);
	statesArray getState();
	eventsArray getEvent(char s);
private: 
	statesArray currentState;
	JSONError* err; //recibe una referenca al error que se encuentra almacenado en JSON y de haber uno lo acutaliza a false y expecifica el tipo
};
