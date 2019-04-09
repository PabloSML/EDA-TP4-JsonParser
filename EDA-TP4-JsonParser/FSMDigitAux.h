#pragma once
#include "JSONError.h"
#define ERROR_NUM "Number badly formed"
#define STATES 9
#define EVENTS 8

enum states { INITIAL, NEGATIVE, DIGIT, COMAI, COMA, EXPOI, EXPONENT, ZERONOT, ERROR, QUIT};
//INITIAL: en este estado solo puede haber "-" o digitos inicluido el cero
//NEG: en este estado solo puede haber coma, exponente o digitos o quit
//DIG: en este estado solo puede haber coma, exponente o digitos o quit
//COMAI: en este estado solo puede haber digitos
//COMA: en este estado solo puede haber exponente o digitos o quit
//EXPOI: en este estado solo puede haber "+", "-"
//EXPONENT: en este estado solo puede haber digitos o QUIT
//ZERONOT: en este estado solo digitos distintos de cero, coma, exponente o QUIT
//ERROR: se llega en caso de que haya habido un caracter invalido en otro estado
//QUIT: se llega a este estado si termino el parseo y no se encontraron errores
enum events { DIGITS, ZERO, COMA, NEGATIVE, E, PLUS, ELSE, QUIT};

