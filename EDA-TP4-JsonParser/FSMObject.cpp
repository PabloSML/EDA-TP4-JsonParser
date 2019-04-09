#include <cstdio>
#include "FSMObject.h"
#include "FSMDigit.h"
#include <cstdlib>
using namespace std;

typedef struct {
	statesob; nextState;
	bool(*action)(void* UserData);
}FMSCell;
FSMObject::FSMObject(string& s, JSONError* err, int *i) {
	currentState = INITIAL;
	this->err = err;
	this->index = i;
	this->s = s;
}
void FSMObject::cycle(eventsob ev) {
	const FMSCell FSMTable[STATES_OBJ][EVENTS_OBJ] = { { {statesob::STRINGI, ok},  {statesob::ERROR, error},    {statesob::ERROR, error},  {statesob::NEWOREND,find_object},         {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},		   {statesob::ERROR, error},  {statesob::ERROR, error},                 {statesob::QUIT, ok},      {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::FINDVALUE, ok}, {statesob::ERROR, error},                 {statesob::STRINGI, ok},   {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::ERROR, error}, {statesob::ERROR, error},                  {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::WAITFORV, find_string},  {statesob::ERROR, error},  {statesob::NEWOREND,find_string},          {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::ERROR, error},  {statesob::NEWOREND, find_array},         {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::ERROR, error},  {statesob::ERROR, error},                 {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::ERROR, error},  {statesob::ERROR, error},                 {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::ERROR, error},  {statesob::NEWOREND, find_bool_or_null},  {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::ERROR, error},  {statesob::NEWOREND, find_bool_or_null},  {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::ERROR, error},  {statesob::ERROR, error},                 {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::ERROR, error}, {statesob::ERROR, error},           {statesob::ERROR, error},  {statesob::NEWOREND, find_bool_or_null},  {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
											   { {statesob::QUIT, ok},     {statesob::ERROR, error},           {statesob::ERROR, error},  {statesob::ERROR, error},                 {statesob::ERROR, error},  {statesob::ERROR, error}, {statesob::QUIT,ok} },
						     				   { {statesob::INITIAL, ok},  {statesob::STRINGI, ok},            {statesob::WAITFORV, ok},  {statesob::FINDVALUE, ok},                {statesob::NEWOREND, ok},  {statesob::ERROR, error}, {statesob::QUIT,ok} } };
	
	ExtraInfo* toConect;
	toConect->i = index;
	toConect->to_check = s;
	toConect->error_t = err;
	FSMTable[currentState][ev].action(toConect);
	currentState = FSMTable[currentState][ev].nextState;

}


eventsob FSMObject::getState() {
	return currentState;
}


void FSMObject::getEvent(char s) {
	eventsob event_;
	if (s == '{') {
		event_ = eventsob::OPENKEYS;
	}
	else if (s == '}') {
		event_ = eventsob::CLOSEKEYS;
	}
	else if (s == ':') {
		event_ = eventsob::TWODOTS;
	}
	else if (s == ',') {
		event_ = eventsob::COMA;
	}
	else if (s == '[') {
		event_ = eventsob::OPENCORCHETES;
	}
	else if (s == R"(\)") {
		event_ = eventsob::BARRAINVERTIDA;
	}
	else if (isalpha(s)) {
		event_ = eventsob::LETTER;
	}
	else if (isdigit(s)) {
		event_ = eventsob::NUM;
	}
	else if (s == '-') {
		event_ = eventsob::NEG;
	}
	else if (isspace(s)) {
		event_ = eventsob::BLANKSPACE;
	}
	else if (s == NULL) {
		event_ = eventsob::QUIT;
	}
	else {
		event_ = eventsob::ELSE;
	}
	return event_;
}


void ok(void* UserData) {
	return;
}
void error(void* UserData) {
	(((ExtraInfo*)UserData)->error_t)->setError(true);
	(((ExtraInfo*)UserData)->error_t)->setErrorString(ERROR_OBJ);
}

void find_string(void* UserData) {
  
}

void find_array(void* UserData) {

}

void find_num(void* UserData) {
	string toParse = (((ExtraInfo*)UserData)->to_check);
	int* i = (((ExtraInfo*)UserData)->index);
	int end = toParse.find_first_of();
	if (end == string::npos) {
		error(UserData);
	}
	string toFSM = toParse.substr(*i + 1, end + 1 - i * );
	FSMDigit parseDig(toFSM, (((ExtraInfo*)UserData)->error_t),i);
	for (int j = 0; j < toFSM && parseDig.getState() != ERROR; j++) {
		cycle(parseDig.getEvent(toFSM[j]));
	}
	if (parseDig.getState() != ERROR) {
		cycle(parseDig.getEvent(NULL));
	}
	else {

	}
}