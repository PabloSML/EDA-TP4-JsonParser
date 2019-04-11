#include <iostream>
#include "FSMDigit.h" //incluye definicion de states

using namespace std;

FSMDigit::FSMDigit() : Eventgenerator()
{
	currentEvent = events::DIGITS;
	currentState = states::INITIAL;
	//err = NULL;
}

void FSMDigit::cycle() {
	/*const FMSCell FSMTable[STATES][EVENTS] = {  { {states::DIGIT, ok},	{states::DIGIT, ok},	{states::DIGIT, ok},    {states::DIGIT, ok},    {states::COMA, ok},		{states::ERROR, error},	{states::EXPONENT, ok}, {states::DIGIT, ok},     {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ZERONOT, ok},  	{states::DIGIT, ok},	{states::DIGIT, ok},	{states::DIGIT, ok},    {states::COMA, ok},		{states::ERROR, error},	{states::EXPONENT, ok}, {states::ERROR, error},  {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ERROR, error},	{states::COMA, error},  {states::COMA, ok},		{states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error},	{states::ERROR, error}, {states::COMA, ok},      {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::NEGATIVE, ok},	{states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::EXPONENT, ok},	{states::ERROR, error}, {states::ERROR, error},  {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ERROR, error},	{states::EXPOI, error}, {states::EXPOI, ok},	{states::ERROR, error}, {states::EXPOI, ok},	{states::ERROR, error},	{states::ERROR, error}, {states::EXPOI, ok},     {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ERROR, error},	{states::ERROR, error}, {states::ERROR, error},	{states::ERROR, error}, {states::ERROR, error}, {states::EXPONENT, ok},	{states::ERROR, error}, {states::ERROR, error},  {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::ERROR, error},   {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error}, {states::ERROR, error},  {states::ERROR, error}, {states::QUIT, ok}},
												{ {states::QUIT, ok},		{states::QUIT, ok},     {states::QUIT, ok},     {states::ERROR, error}, {states::QUIT, ok},     {states::ERROR, error}, {states::QUIT, ok},     {states::QUIT, ok},      {states::ERROR, error}, {states::QUIT, ok}} }; Esta esta mal*/

										//EVENTS		DIGITS						ZERO					COMA					NEGATIVE				 E						PLUS					ELSE					QUIT			STATES
	const FSMCell FSMTable[STATES][EVENTS] = {	{ {states::DIGIT, ok},		{states::ZERONOT, ok},	{states::ERROR, error},	{states::NEGATIVE, ok},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error},	{states::QUIT, ok}},	// INITIAL
												{ {states::DIGIT, ok},		{states::DIGIT, ok},	{states::ERROR, error},	{states::ERROR, error},	{states::EXPOI, error},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error}},// NEGATIVE
												{ {states::DIGIT, ok},		{states::DIGIT, ok},	{states::COMAI, ok},	{states::ERROR, error},	{states::EXPOI, ok},	{states::ERROR, error},	{states::ERROR, error},	{states::QUIT, ok}},	// DIGIT
												{ {states::DIGIT, ok},		{states::DIGIT, ok},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error}},// COMAI
												{ {states::COMA, ok},		{states::COMA, ok},		{states::ERROR, error},	{states::ERROR, error},	{states::EXPOI, ok},	{states::ERROR, error},	{states::ERROR, error},	{states::QUIT, ok}},	// COMA
												{ {states::EXPONENT, ok},	{states::ERROR, error},	{states::ERROR, error},	{states::EXPONENT, ok},	{states::ERROR, error},	{states::EXPONENT, ok},	{states::ERROR, error},	{states::ERROR, error}},// EXPOI
												{ {states::EXPONENT, ok},	{states::EXPONENT, ok},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error},	{states::ERROR, error},	{states::QUIT, ok}},	// EXPONENT
												{ {states::DIGIT, ok},		{states::ERROR, error},	{states::COMA, ok},		{states::ERROR, error},	{states::EXPOI, ok},	{states::ERROR, error},	{states::ERROR, error},	{states::QUIT, ok}},	// ZERONOT
												{ {states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok}},	// ERROR
												{ {states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok},		{states::QUIT, ok}}		// QUIT
											};


	FSMTable[currentState][currentEvent].action(getReport()); 
	currentState = FSMTable[currentState][currentEvent].nextState;

}


void
FSMDigit::getEvent(char s)
{
	if (isdigit(s) && s != '0') {
		currentEvent = events::DIGITS;
	}
	else if (s == '0') {
		currentEvent = events::ZERO;
	}
	else if (s == '.') {
		currentEvent = events::COMA;
	}
	else if (s == '-') {
		currentEvent = events::NEGATIVE;
	}
	else if (s == 'E' || s == 'e') {
		currentEvent = events::E;
	}
	else if (s == '+') {
		currentEvent = events::PLUS;
	}
	else if (s == NULL) {
		currentEvent = events::QUIT;
	}
	else {
		currentEvent = events::ELSE;
	}
}

states FSMDigit::getState(){
	return currentState;
}