#include <iostream>
#include "FSMDigit.h" //incluye definicion de states
#include "FSMDigitAux.h" //incluye la deficion de la estructura FMSCell
#include "FMSCell.h"

using namespace std;
void FSMDigit::FSMDigit(JSONError* err) {
	currentState = INITIAL;
	this->err = err;
}

void FSMDigit::cycle(events ev) {
	const FMSCell FSMTable[STATES][EVENTS] = {  { {states::DIGIT, ok},		{states::DIGIT, ok},	{states::DIGIT, ok},    {states::DIGIT, ok},    {states::COMA, ok},		{states::ERROR, error},	{states::EXPONENT, ok}, {states::DIGIT, ok},     {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ZERONOT, ok},  	{states::DIGIT, ok},	{states::DIGIT, ok},	{states::DIGIT, ok},    {states::COMA, ok},		{states::ERROR, error},	{states::EXPONENT, ok}, {states::ERROR, error},  {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ERROR, error},	{states::COMA, error},  {states::COMA, ok},		{states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error},	{states::ERROR, error}, {states::COMA, ok},      {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::NEGATIVE, ok},	{states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::EXPONENT, ok},	{states::ERROR, error}, {states::ERROR, error},  {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ERROR, error},	{states::EXPOI, error}, {states::EXPOI, ok},	{states::ERROR, error}, {states::EXPOI, ok},	{states::ERROR, error},	{states::ERROR, error}, {states::EXPOI, ok},     {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ERROR, error},	{states::ERROR, error}, {states::ERROR, error},	{states::ERROR, error}, {states::ERROR, error}, {states::EXPONENT, ok},	{states::ERROR, error}, {states::ERROR, error},  {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ERROR, error},   {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error},  {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::QUIT, ok},		{states::QUIT, ok},     {states::QUIT, ok},     {states::ERROR, error}, {states::QUIT, ok},     {states::ERROR, error}, {states::QUIT, ok},     {states::QUIT, ok},      {states::ERROR, error}, {states::QUIT, ok}} };
	
	FSMTable[currentState][ev].action(err); 
	currentState = FSMTable[currentState][ev].nextState;
	}

events FSMDigit::getEvent(char s) {
	events events_;
		if (isdigit(s) && s != '0') {
			event_ = events::DIGITS;
		}
		else if (s == '0') {
			event_ = events::ZERO;
		}
		else if (s== '.') {
			event_ = events::COMA;
		}
		else if (s == '-') {
			event_ = events::NEGATIVE;
		}
		else if (s == 'E' || s == 'e') {
			event_ == events::E;
		}
		else if (s== '+') {
			event_ = events::PLUS
		}
		else if (s == NULL) {
			event_ = events::QUIT;
		}
		else {
			event_ = events::ELSE;
		}
		return event_;
}

states FSMDigit::getState(){
	return currentState;
}

void ok(void* UserData){
	return;
}

void error(void* UserData) {
	((JSONError*)UserData)->setErrorString(ERROR_NUM);
	return false;
}