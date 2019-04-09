#pragma once
#include "FSMObjectAux.h"
class FSMObject {
public:
	FSMObject(string& s, JSONError* err, int *i);
	void cycle(eventsob ev);
	eventsob getEvent(char s);
	statesob getState();
private: 
	statesob currentState;
	string s;
	JSONError* err;
	int *index;
};