#pragma once

enum statesObj{INITIAL, STRINGI, STRINGP, STRINGE, FIND_VALUE, OBJ, ARRAY, STRING, OPENARRAY, OPENOBJ, OPENSTRING, NEWOREND, QUIT, ERROR};
enum eventsObj{OPENKEYS, CLOSEKEYS, COMILLAS, TWODOTS, OPENARRAY, CLOSEARRAY, NUMBER, LETTER, COMA, SLASH, BLANKSPACE, ELSE, QUIT};

class FSMObj{
public:
	FSMObj(JSONError* err);
	statesObj getState();
	eventsObj getEvent(char s);
private:
	statesObj currentState;
	JSONError* err; //recibe una referenca al error que se encuentra almacenado en JSON y de haber uno lo acutaliza a false y expecifica el tipo
};