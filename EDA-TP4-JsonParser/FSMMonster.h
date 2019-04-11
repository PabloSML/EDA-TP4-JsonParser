#pragma once
#include <iostream>
#include "Eventgenerator.h"
using namespace std;

enum stateMonster {COMPLETAR, CON, ESTADOS};
enum eventMonster {COMPLETAR, CON, EVENTOS, STARTED, CONTINUE, ERROR, QUIT};

typedef struct {
	stateMonster nextState;
	void(*action)(void* UserData);

}FSMCellM;

class FSMMonster {

public:
	FSMMonster() { evGen = NULL; }

	void setGenerator(Eventgenerator* evGen) { this->evGen = evGen; }

	eventMonster getEvent(char c);
	void cycle(eventMonster ev);

private:
	Eventgenerator* evGen;
};

void createANumMachine(void* UserData);