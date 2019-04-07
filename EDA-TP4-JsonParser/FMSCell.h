#include "JSONError.h"
#define ERROR_STR "Number badly formed"

enum states { INITIAL, NEGATIVE, DIGIT, COMA, EXPOI, EXPONENT, ZERONOT, ERROR };
enum events { DIGITS, ZERO, COMA, NEGATIVE, EXPONENT, PLUS, ELSE };

typedef struct {
	states nextState;
	bool(*action)(void* UserData);
}FMSCell;

bool continueToDo(void* UserData) {
	return true;
}

bool error(void* UserData) {
	(*JSONError)UserData.setErrorString(ERROR_STR);
	return false;
}



