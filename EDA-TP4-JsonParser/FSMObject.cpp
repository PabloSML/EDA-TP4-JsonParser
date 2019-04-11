#include <iostream>
#include "FSMObject.h" //incluye definicion de states

using namespace std;

FSMObject::FSMObject() : Eventgenerator()
{
	currentEvent = events::OPENKEY;
	currentState = states::INITIAL;
	this->setLabel(string("object"));
}

void
FSMObject::cycle() {
	
	const FSMCellO FSMTable[STATES][EVENTS] = {};

	FSMTable[currentState][currentEvent].action(this);
	currentState = FSMTable[currentState][currentEvent].nextState;
}


void
FSMObject::getEvent(char s)
{
	
}

states
FSMObject::getState() {
	return currentState;
}

void
ok(void*userData)
{
	FSMObject* tempFSM = (FSMObject*)userData;
	tempFSM->setReport(event_t::CONTINUE);
}

void
error(void*userData)
{
	FSMObject* tempFSM = (FSMObject*)userData;
	tempFSM->setReport(event_t::ERROR);
}

void
quit(void*userData)
{
	FSMObject* tempFSM = (FSMObject*)userData;
	tempFSM->setReport(event_t::QUIT);
}