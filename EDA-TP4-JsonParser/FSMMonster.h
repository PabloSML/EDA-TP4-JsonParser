#pragma once
#include <iostream>
#include "Eventgenerator.h"
#include "JSONError.h"
using namespace std;

enum stateMonster { INITIAL, STRINGI, STRINGN, STRINGE, FINDVALUE, INSTRING, INMACHINE, FINDNEWORQUIT, QUIT, ERROR, IGNORE };
enum eventMonster { OPENKEYS, CLOSEKEYS, COMILLAS, TWODOTS, COMA, OPENCORCHETE, NUM, LET, BLACKSLASH, BLANKSPACE, ELSE, SUBCONTINUE, SUBERROR, SUBQUIT, QUIT };

typedef struct {
	stateMonster nextState;
	void(*action)(void* UserData);

}FSMCellM;

class FSMMonster {

public:
	FSMMonster() {}
	FSMMonster(JSONError* err)
	{
		evGen = NULL;
		evGenCreated = false;
		this->err = err;
	}

	void setGenerator(Eventgenerator* evGen) { this->evGen = evGen; }

	bool wasEvGenCreated() { return evGenCreated; }
	void setEvGenCreated(bool creation) { this->evGenCreated = creation; }

	eventMonster getEvent(char c);
	void cycle(eventMonster ev);

private:
	Eventgenerator* evGen;
	bool evGenCreated;
	JSONError* err;
};

void createANumMachine(void* UserData);