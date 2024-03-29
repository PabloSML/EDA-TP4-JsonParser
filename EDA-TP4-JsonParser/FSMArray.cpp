#include <iostream>
#include "FSMArray.h" //incluye definicion de states

using namespace std;

FSMArray::FSMArray() : Eventgenerator()
{
	currentEvent = events::OPENBRACKET;
	currentState = states::INITIAL;
	this->setLabel(string("object"));
}

void
FSMArray::cycle() {

	const FSMCellA FSMTable[STATES][EVENTS] = {};

	FSMTable[currentState][currentEvent].action(this);
	currentState = FSMTable[currentState][currentEvent].nextState;
}


void
FSMArray::getEvent(char s)
{

}

states
FSMArray::getState() {
	return currentState;
}

void
ok(void*userData)
{
	FSMArray* tempFSM = (FSMArray*)userData;
	tempFSM->setReport(event_t::CONTINUE);
}

void
error(void*userData)
{
	FSMArray* tempFSM = (FSMArray*)userData;
	tempFSM->setReport(event_t::ERROR);
}

void
quit(void*userData)
{
	FSMArray* tempFSM = (FSMArray*)userData;
	tempFSM->setReport(event_t::QUIT);
}