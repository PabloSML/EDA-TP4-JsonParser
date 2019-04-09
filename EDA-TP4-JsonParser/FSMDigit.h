#pragma once
class FSMDigit {
public:
	FSMDigit(string& s, JSONError& err, int *i);
	void cycle(events ev);
	events getEvent(char s);
	states getState();
}
private:
	states currentState;
	JSONError* err; //recibe una referenca al error que se encuentra almacenado en JSON y de haber uno lo acutaliza a false y expecifica el tipo
	string s;
	int* index; 
};

void ok(void* UserData);
void error(void *UserData);