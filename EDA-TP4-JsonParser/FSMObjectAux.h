#pragma once
#include "JSONError.h"
#define ERROR_OBJ "Object badly formed"
#define STATES_OBJ 7
#define EVENTS_OBJ 13

enum statesob{INITIAL, STRINGI, WAITFORV, FINDVALUE, NEWOREND, ERROR, QUIT}; 
enum eventsob{ OPENKEYS, CLOSEKEYS, TWODOTS, COMA, COMILLAS, OPENCORCHETES, BARRAINVERTIDA, LETTER, NUM, NEG, ELSE, QUIT, BLANKSPACE};
//INITIAL: en este estado solo se permite que ingresen llaves que abren, "{" y espacios en blanco
//STRINGI: en este estado solo se permite que ingresen comiila " y espacio en blanco
//WAITFORV: en este estado solo se permite que ingresen {, [, ", numeros, letras o espacio en blanco. Si el valor ingresado es correcto, la maquina lo parsea segun que es
//NEWOREND: en este estado solo se permite que ingresen : o }, es decir que el objecto termino o hay un nuevo campo.
//ERROR: se llega en caso de que haya habido un caracter invalido en otro estado
//QUIT: se llega a este estado si termino el parseo y no se encontraron errores

typedef struct {
	int* index;
	JSONError* error_t;
	string to_check; 
}ExtraInfo;

void ok(void* UserData);
void error(void* UserData);
void find_string(void* UserData); /*encuentra y parsea string*/
void find_array(void* UserData); /*encuentra y parsea array*/
void find_bool_or_null(void* UserData); /*encuentra y parsea null o bool*/
void find_num(void* UserData); /*encuentra y parsea numeros*/
void find_object(void* UserData);


