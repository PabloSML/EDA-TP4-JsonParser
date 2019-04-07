#include <iostream>
#include "FSMDigit.h"
#include "FMSCell.h"
#define STATES 8
#define EVENTS 7

using namespace std;

void FSMDigit::cycle(string& s) {

	const FMSCell FSMTable[STATES][EVENTS] = { {DIGIT, continueToDo}, {DIGIT, continueToDo}, {DIGIT, continueToDo}, {COMA, continueToDo}, {EXPONENT, continueToDo}, {EXPONENT, continueToDo}, {DIGIT, continueToDo},
											{ZERONOT, continueToDo},  {DIGIT, continueToDo}, {DIGIT, continueToDo}, {COMA, continueToDo}, {EXPONENT, continueToDo}, {EXPONENT, continueToDo}, {ERROR, error},
											{ERROR, error},           {ERROR, error},        {COMA, continueToDo},  {ERROR, error},       {ERROR, error},           {ERROR, error},			  {COMA, continueToDo},
											{NEGATIVE, continueToDo}, {ERROR, error},        {ERROR, error},        {ERROR, error},       {EXPONENT, continueToDo}, {ERROR, error},           {ERROR, error},
											{ERROR, error},           {ERROR, error},        {EXPOI, continueToDo}, {EXPOI, continueToDo},{ERROR, error},			{ERROR, error},           {EXPOI, continueToDo},
											{ERROR, error},           {ERROR, error},        {ERROR, error},        {ERROR, error},       {EXPONENT, continueToDo}, {ERROR, error},           {ERROR, error},
											{ERROR, error},           {ERROR, error},        {ERROR, error},        {ERROR, error},       {ERROR, error},			{ERROR, error},           {ERROR, error} }
	bool ok = true; //corta antes si el programa dio error
	states state = INITIAL; 
	events event_;
	JSONError error_t(true,"");
	for (int i = 0; i < s.length() && ok; i++) {
		if (isdigit(s[i]) && s[i] != "0") {
			event_ = DIGIT;
		}
		else if (s[i] == "0") {
			event_ = ZERO;
		}
		else if (s[i] == ".") {
			event_ = COMA;
		}
		else if (s[i] == "-") {
			event_ = NEGATIVE;
		}
		else if (s[i] == "E" || s[i] == "e") {
			event_ == EXPONENT;
		}
		else if (s[i] == "+") {
			event_ = PLUS;
		}
		else{
			event_ = ELSE;
		}
		ok = FSMTable[state][event_].action(error_t);
		state = FSMTable[state][event_].nextState;
	}
}