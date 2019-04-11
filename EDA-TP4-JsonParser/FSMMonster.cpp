#include "FSMMonster.h"
#include "FSMDigit.h"

eventMonster
FSMMonster::getEvent(char c)
{
	eventMonster return_value;
	if (evGen == NULL)
	{
		if (c == '{') {
			return_value = eventMonster::OPENKEYS;
		}
		else if (c == '}') {
			return_value = eventMonster::CLOSEKEYS;
		}
		else if (c == '\"') {
			return_value = eventMonster::COMILLAS;
		}
		else if (c == ',') {
			return_value = eventMonster::COMA;
		}
		else if (c == '[') {
			return_value = eventMonster::OPENCORCHETE;
		}
		else if (isdigit(c) || c == '-') {
			return_value = eventMonster::NUM;
		}
		else if (isalpha(c)) {
			return_value = eventMonster::LET;
		}
		else if (c == '\\') {
			return_value = eventMonster::BLACKSLASH;
		}
		else if (isspace(c)) {
			return_value = eventMonster::BLANKSPACE;
		}
		else if (c == NULL) {
			return_value = eventMonster::QUIT;
		}
		else {
			return_value = eventMonster::QUIT;
		}
	}

	else
	{
		evGen->getEvent(c);
		evGen->cycle();
		switch (evGen->getReport())
		{
		case event_t::CONTINUE:
			return_value = eventMonster::SUBCONTINUE;
			break;
		case event_t::ERROR:
			return_value = eventMonster::SUBERROR;
			break;
		case event_t::QUIT:
			return_value = eventMonster::SUBQUIT;
			break;
		}
	}

	return return_value;
}

void
FSMMonster::cycle(eventMonster ev)
{

}

void
createANumMachine(void* userData)
{
	FSMDigit* newFSM = new FSMDigit;
	FSMMonster* tempMonster = (FSMMonster*)userData;
	tempMonster->setGenerator(newFSM);
	tempMonster->setEvGenCreated(true);
}