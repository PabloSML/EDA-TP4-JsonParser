#include <cstdio>
#include "FSMObject.h"
#include "FSMDigit.h"
#include <cstdlib>
#include "FSMObjectAux.h"
#include "FMSCell.h"
using namespace std;

bool
FSMObject::cycle(string& s) {
	const FMSCell FSMTable[STATES][EVENTS] = { {{STRINGI, ok}, {END, error}, {STRING, ok},   {STRING, ok}, {END, error},     {RESET,find_object},        {END, error},  {END, error}},
											   {{END,error},   {END, error}, {STRING, ok},  {STRING, ok}, {END, error},    {END, error},				  {END, ok},     {END, error}},
											   {{END, error},  {END, error}, {STRING, ok},  {STRING, ok}, {FINDVALUE, ok}, {END, error},				  {END, error},  {END, error}},
											   {{END, error},  {END, error}, {STRING, ok},  {STRING, ok}, {END, error},    {END, error},				  {STRINGI, ok}, {END, error}},
											   {{END, error},  {STRINGC, ok}, {STRING, ok}, {NEWV, ok}, {END, error},     {RESET, find_string},       {END, error},  {END, error}},
											   {{END, error},  {END, error}, {STRING, ok},  {STRING,ok}, {END, error},    {RESET, find_array},        {END, error},  {END, error}},
												{{END, error},  {END, error}, {IGNORE, ok},  {IGNORE, ok}, {END, error},    {END, error},				  {END, error},  {END, error}},
												{{END, error},  {END, error}, {STRING, ok}, {STRING, ok}, {END, error},    {RESET, find_bool_or_null}, {END, error},  {END, error}},
												{{END, error},  {END, error}, {STRING, ok},  {STRING, ok}, {END, error},    {RESET, find_num},		  {END, error},  {END, error}},
												{{END, error},  {END, error}, {STRING, ok},  {STRING, ok}, {END, error},    {RESET, find_num},          {END, error},  {END, error}},
												{{END, error},  {END, error}, {END, error},  {END, error}, {END, error},    {END, error},               {END, error},  {STRING,ok}},
												{{END, error},  {END, error}, {STRING, ok},  {STRING, ok}, {END, error},     {END, error},			      {END, error},  {END, error} } }
	
	bool ok = true;
	states state = INITIAL;
	events event_;
	Data conection;
	JSONError err;
	conection.error_t(&err);
	int i = s.find_first_not_of(" ");
	while (i < s.length()) {
		if (s[i] == "{") {
			event_ = OPENKEYS;
		}
		else if (s[i] == "}") {
			event_ = CLOSEKEYS;
		}
		else if (s[i] == ":") {
			event_ = TWODOTS;
		}
		else if (s[i] == ",") {
			event_ = COMA;
		}
		else if(s[i]=="["){
			event_ = OPENCORCHETES;
		}
		else if (s[i] == R"(\)") {
			event_ = BARRAINVERTIDA;
		}
		else if (isalpha(s[i])) {
			event_ = LETTER;
		}
		else if(isdigit(s[i])){
			event_ = NUM;
		}
		else if(s[i]=="-"){
			event_ = NEG;
		}
		else if(s[i]=="") //falta corregir
		{

		}
		else {
			event_ = ELSE;
		}
		conection.index = &i;
		conection.to_check = s;
		ok = FSMTable[state][event_].action(&conection);
		state = FSMTable[state][event_].nextState;
	}

}



bool ok(void* UserData) {
	*((*Data)UserData->index)++; //incrementa el indice con el que estoy trabajando el string
	return true;
}

bool error(void* UserData) {
	((*Data)UserData)->setErrorString(ERROR_OBJ);
	return false;
}

bool find_string(void* UserData) {
	int end = ((*Data)UserData)->to_check.find_first_of('"', 1+*((*Data)UserData->index)); //quiero ver donde termine el string para parsearlo 
	int check= ((*Data)UserData)->to_check.find_first_of(R"(\)", *((*Data)UserData->index)); // me fijo si la siguiente aparición esta escapada
	bool well_formed = true;
	while (check == end - 1 && formed)
	{
		aux = end + 1;
		end = ((*Data)UserData)->to_check.find_first_of('"', aux);
		check = ((*Data)UserData)->to_check.find_first_of(R"(\)", aux);
		if (end==string::npos){
			((*Data)UserData)->error_t.setErrorString(ERROR_OBJ);
			return false;
		}

	}

	//ahora que tengo los indices de donde empieza y termina mi string lo parse con la futura fsm de strings
	return true;
}

/*bool find_array(void* UserData) {
	int sum
	int start = *((*Data)UserData->index);

}*/

bool find_bool_or_null(void* UserData) {
	int end= ((*Data)UserData)->to_check.find_first_of(',}', 1 + *((*Data)UserData->index));
	if (end == string::npos) {
		(*Data)UserData.error_t.setErrorString(ERROR_OBJ);
		return false;
	}
	//ahora que tengo el supuesto bool, me fijo si es un bool con la futura fsm de bool
}

bool find_num(void* UserData) {
	int start = *(((*Data)UserData)->index);
	int end = ((*Data)UserData)->to_check.find_first_of(',}', 1 + start); //me fijo donde termina el supuesto numero, si esta bien hecho deberia haber un } o una , alfinal
	if (end == string::npos) {
		((*Data)UserData)->error_t.setErrorString(ERROR_OBJ);
		return false;
	}
	end -= 1;
    
	FSMDigit parseDigit;
	return parseDigit.cycle(((*Data)UserData)->to_check.substr(start, end)); //devuelvo si el numero es valido
}

bool find_object(void* UserData) {

}
