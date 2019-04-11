#pragma once
#include "Eventgenerator.h"

#define STATES
#define EVENTS

enum states { INITIAL = 0, PONERMAS};
enum events { OPENBRACKET = 0, PONERMAS};

typedef struct {
	states nextState;
	void(*action)(void* UserData);

}FSMCellA;

class FSMArray : public Eventgenerator {

public:
	FSMArray();

	states getState();
	
	virtual void getEvent(char c);
	virtual void cycle();

	virtual event_t getReport(void) { return report; }
	virtual void setReport(event_t report) { this->report = report; }

private: 
	events currentEvent;
	states currentState;

	event_t report;
};

void ok(void* userData);
void error(void*userData);
void quit(void*userData);
