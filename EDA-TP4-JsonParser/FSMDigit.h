#pragma once
#include "Eventgenerator.h"
#define STATES 10
#define EVENTS 8


//INITIAL: en este estado solo puede haber "-" o digitos inicluido el cero
//NEG: en este estado solo puede haber coma, exponente o digitos o quit
//DIG: en este estado solo puede haber coma, exponente o digitos o quit
//COMAI: en este estado solo puede haber digitos
//COMA: en este estado solo puede haber exponente o digitos o quit
//EXPOI: en este estado solo puede haber "+", "-"
//EXPONENT: en este estado solo puede haber digitos o QUIT
//ZERONOT: en este estado solo puede haber digitos distintos de cero, coma, exponente o QUIT
//ERROR: se llega en caso de que haya habido un caracter invalido en otro estado
//QUIT: se llega a este estado si termino el parseo y no se encontraron errores
enum states { INITIAL = 0, NEGATIVE, DIGIT, COMAI, COMA, EXPOI, EXPONENT, ZERONOT, ERROR, QUIT };
enum events { DIGITS = 0, ZERO, COMA, NEGATIVE, E, PLUS, ELSE, QUIT };

typedef struct {
	states nextState;
	void(*action)(void* UserData);

}FSMCellD;

class FSMDigit : public Eventgenerator {

public:	
	FSMDigit();

	states getState();

	virtual void getEvent(char c);
	virtual void cycle();

	virtual event_t getReport(void) { return report; }
	virtual void setReport(event_t report) { this->report = report; }

private:
	events currentEvent;
	states currentState;

	event_t report;
};

void ok(void* userData);
void error(void*userData);
void quit(void*userData);
