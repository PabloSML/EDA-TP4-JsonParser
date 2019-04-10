#pragma once
class FSMDigit {
public:
	FSMDigit(JSONError* err);
	void cycle(events ev);
	events getEvent(char s);
	states getState();
}
private:
	states currentState;
	JSONError* err; //recibe una referenca al error que se encuentra almacenado en JSON y de haber uno lo acutaliza a false y expecifica el tipo
};

void ok(void* UserData);
void error(void *UserData);