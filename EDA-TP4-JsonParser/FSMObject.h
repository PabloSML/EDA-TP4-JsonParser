#pragma once
#include "Eventgenerator.h"

enum states { INITIAL = 0, PONERMAS };
enum events { OPENKEY = 0, PONERMAS };

typedef struct {
	states nextState;
	void(*action)(void* UserData);

}FSMCellO;

class FSMObject : public Eventgenerator {

public:
	FSMObject();

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
