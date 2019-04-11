#pragma once
#include <iostream>
#include "Eventgenerator.h"
using namespace std;

enum stateMonster {COMPLETAR, CON, ESTADOS};
enum eventMonster {COMPLETAR, CON, EVENTOS};

typedef struct {
	stateMonster nextState;
	void(*action)(void* UserData);

}FSMCell;

class FSMMonster {

public:
	FSMMonster() { evGen = NULL; }

	eventMonster getEvent(char c);
	void cycle(eventMonster ev);

private:
	Eventgenerator* evGen;
};