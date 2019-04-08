#include <iostream>
#include "FSMDigit.h" //incluye definicion de states
#include "FSMDigitAux.h" //incluye la deficion de la estructura FMSCell
#include "FMSCell.h"

using namespace std;

void FSMDigit::cycle(string& s) {

	const FMSCell FSMTable[STATES][EVENTS] ={	{{states::DIGIT, continueToDo},		{states::DIGIT, continueToDo}, {states::DIGIT, continueToDo}, {states::COMA, continueToDo}, {states::EXPONENT, continueToDo},	{states::EXPONENT, continueToDo}, {states::DIGIT, continueToDo}},
												{{states::ZERONOT, continueToDo},	{states::DIGIT, continueToDo}, {states::DIGIT, continueToDo}, {states::COMA, continueToDo}, {states::EXPONENT, continueToDo},	{states::EXPONENT, continueToDo}, {states::ERROR, error}},
												{{states::ERROR, error},			{states::ERROR, error},        {states::COMA, continueToDo},  {states::ERROR, error},       {states::ERROR, error},				{states::ERROR, error},			  {states::COMA, continueToDo}},
												{{states::NEGATIVE, continueToDo},	{states::ERROR, error},        {states::ERROR, error},        {states::ERROR, error},       {states::EXPONENT, continueToDo},	{states::ERROR, error},           {states::ERROR, error}},
												{{states::ERROR, error},			{states::ERROR, error},        {states::EXPOI, continueToDo}, {states::EXPOI, continueToDo},{states::ERROR, error},				{states::ERROR, error},           {states::EXPOI, continueToDo}},
												{{states::ERROR, error},			{states::ERROR, error},        {states::ERROR, error},        {states::ERROR, error},       {states::EXPONENT, continueToDo},	{states::ERROR, error},           {states::ERROR, error}},
												{{states::ERROR, error},			{states::ERROR, error},        {states::ERROR, error},        {states::ERROR, error},       {states::ERROR, error},				{states::ERROR, error},           {states::ERROR, error}},
											};
	
	bool ok = true; //corta antes si el programa dio error
	states state = INITIAL; 
	events event_;
	JSONError error_t(true,"");
	for (int i = 0; i < s.length() && ok; i++) {
		if (isdigit(s[i]) && s[i] != '0') {
			event_ = events::DIGITS;
		}
		else if (s[i] == '0') {
			event_ = events::ZERO;
		}
		else if (s[i] == '.') {
			event_ = events::COMA;
		}
		else if (s[i] == '-') {
			event_ = events::NEGATIVE;
		}
		else if (s[i] == 'E' || s[i] == 'e') {
			event_ == events::EXPONENT;
		}
		else if (s[i] == '+') {
			event_ = events::PLUS;
		}
		else{
			event_ = events::ELSE;
		}
		ok = FSMTable[state][event_].action(&error_t);
		state = FSMTable[state][event_].nextState;
	}
}