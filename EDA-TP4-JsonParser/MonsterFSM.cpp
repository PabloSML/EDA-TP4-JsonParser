#include "MonsterFSM.h"
#include "FSMDigit.h"
#include <cstdlib>

using namespace std;

typedef struct {
	monsterStates nextState;
	void(*action)(void* UserData);

}FMSCell;

MonsterFSM::MonsterFSM(JSONError err) {
	currentState = monsterStates::INITIAL;
	this->err = err;
}
monsterEvents
MonsterFSM::getEvent(char s) {
	actualChar = s;
	monsterEvents ev;
	if (s == '{') {
		ev = monsterEvents::OPENKEYS;
	}
	else if (s == '}') {
		ev = monsterEvents::CLOSEKEYS;
	}
	else if (s == '"') {
		ev = monsterEvents::COMILLAS;
	}
	else if (s == ',') {
		ev = monsterEvents::COMA;
	}
	else if (s == '[') {
		ev = monsterEvents::OPENCORCHETE;
	}
	else if (isdigit(s)) {
		ev = monsterEvents::NUM;
	}
	else if (isalpha(s)) {
		ev = monsterEvents::LET;
	}
	else if (s == R"(\)") {
		ev = monsterEvents::BLACKSLASH;
	}
	else if (isspace(s)) {
		ev = monsterEvents::BLANKSPACE;
	}
	else if (s == NULL) {
		ev = monsterEvents::QUIT;
	}
	else{
		ev = monsterEvents::QUIT;
    }
	return ev;
}

void MonsterFSM::cycle(monsterEvents ev) {                            //INITIAL                     STRINGI                          STRINGN                      STRINGE                          FINDVALUE                                   OBJ                       NULLORBOLL                       ARRAY                       NUM                       ARRAY                       NUM                      STRING                      FINDORQUIT                      QUIT                       ERROR                         IGNORE
	/*const FMSCell MonsterFSMTable[MONSTEREVENTS][MONSTERSTATES] = { { {monsterStates::STRINGI, ok},  {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok}, {monsterStates::ERROR, error},  {monsterStates::OBJ, createObjMachine},      {monsterStates::OBJ, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NUM,ok}, {monsterStates::STRING, ok}, {monsterStates::ERROR, error}}, //{monsterStates::QUIT, ok}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok} },
																	{ {monsterStates::ERROR, error}, {monsterStates::ERROR, error}, {monsterStates:STRINGN, ok},  {monsterStates::ERROR, error},  {monsterStates::ERROR, error},               {monsterStates::OBJ, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NUM,ok}, {monsterStates::STRING, ok}, {monsterStates::QUIT, ok}},      //{monsterStates::QUIT, ok}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok} },
																	{ {monsterStates::ERROR, error}, {monsterStates::STRING, ok},   {monsterStates::STRINGE, ok}, {monsterStates::ERROR, error},  {monsterStates::STRING, createStringMachine},{monsterStates::OBJ, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NUM, ok}, {monsterStates::STRING, ok}, {monsterStates::ERROR, error}}, //{monsterStates::QUIT, ok}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok} },
																	{ {monsterStates::ERROR, error}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok}, {monsterStates::FINDVALUE, ok}, {monsterStates::ERROR, error},               {monsterStates::OBJ, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NUM,ok}, {monsterStates::STRING, ok}, {monsterStates::ERROR, error}},  //{monsterStates::QUIT, ok}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok} },
																	{ {monsterStates::ERROR, error}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok}, {monsterStates::ERROR, error},  {monsterStates::ERROR, error},               {monsterStates::OBJ, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NUM,ok}, {monsterStates::STRING, ok}, {monsterStates::STRINGI, ok}},   //{monsterStates::QUIT, ok}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok} },
																	{ {monsterStates::ERROR, error}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok}, {monsterStates::ERROR, error},  {monsterStates::ARRAY, createArrayMachine},  {monsterStates::OBJ, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NULLORBOOL, ok}, {monsterStates::ARRAY, ok}, {monsterStates::NUM,ok}, {monsterStates::STRING, ok}, {monsterStates::ERROR, ok}}    //{monsterStates::QUIT, ok}, {monsterStates::ERROR, error}, {monsterStates::STRINGN, ok} } 
																  
																	
	
	//{ {monsterStates::ERROR, error}, { monsterStates::ERROR, error }, { monsterStates::STRINGN, ok }, { monsterStates::ERROR, error }, { monsterStates::NUM, createANumMachine } };
		*/
       
	FSMCellM MonsterFSMTable[20][20];
			MonsterFSMTable[currentState][ev].action(this);
			currentState = MonsterFSMTable[currentState][ev];

}

void
createANumMachine(void* userData)
{
	FSMDigit* newFSM = new FSMDigit;
	MonsterFSM* hola = (MonsterFSM*)userData;
	hola->setGenerator(newFSM);
}



