#pragma once
#include "JSONError.h"
#define ERROR_NUM "Number badly formed"
#define STATES 7
#define EVENTS 7

enum states { INITIAL, NEGATIVE, DIGIT, COMA, EXPOI, EXPONENT, ZERONOT, ERROR };
enum events { DIGITS, ZERO, COMA, NEGATIVE, EXPONENT, PLUS, ELSE };

bool continueToDo(void* UserData) {
	return true;
}

bool error(void* UserData) {
	(*JSONError)UserData.setErrorString(ERROR_STR);
	return false;
}