#pragma once
#include "Eventgenerator.h"
#include "FSMDigit.h"
#include "JSONError.h"
#include <cstdio>
#define MONSTERERROR "Object definition error"
#define MONSTEREVENTS 11
#define MONSTERSTATES 13

enum monsterStates{INITIAL, STRINGI, STRINGN, STRINGE, FINDVALUE, OBJ, NULLORBOOL, ARRAY, NUM, STRING, FINDNEWORQUIT, QUIT, ERROR, IGNORE};
enum monsterEvents{OPENKEYS, CLOSEKEYS, COMILLAS, TWODOTS, COMA, OPENCORCHETE, NUM, LET, BLACKSLASH, BLANKSPACE, ELSE, QUIT};

class MonsterFSM {
public:
	void MonsterFSM(JSONError err);
	void cycle(monsterEvents ev);
    monsterEvents getEvent(char s);
	JSONError* getError() { return err; }
	void setGenerator(Eventgenerator* g) { generator = g; }
	//monsterState getState();

private:
	Eventgenerator* generator;
	monsterStates currentState;
	bool activeEventGenerator;
	char actualchar;
	JSONError* err;
};

void ok(void* UserData);
void error(void* UserData);
void createObjMachine(void* UserData);
void createStringMachine(void* UserData);
void createArrayMachine(void* UserData);
void createANumMachine(void* UserData);