#pragma once
#include"JSONError.h"
#define ERROR_OBJ "Object badly formed"
#define STATES 9
#define EVENTS 12

enum states{ INITIAL, STRINGI, STRINGC, STRING, NEWV, FINDVALUE, RESET, END, IGNORE }; //SEPAN DISCULPAR EL SPANGLISH
enum events{ OPENKEYS, CLOSEKEYS, TWODOTS, COMA, COMILLAS, OPENCORCHETES, BARRAINVERTIDA, LETTER, NUM, NEG, PERMITTEDSTRING, ELSE };

typedef struct {
	int* index;
	JSONError* error_t;
	string to_check; 
}Data;

bool ok(void* UserData);
bool error(void* UserData);
bool find_string(void* UserData); /*encuentra y parsea string*/
bool find_array(void* UserData); /*encuentra y parsea array*/
bool find_bool_or_null(void* UserData); /*encuentra y parsea null o bool*/
bool find_num(void* UserData); /*encuentra y parsea numeros*/
bool find_object(void* UserData);