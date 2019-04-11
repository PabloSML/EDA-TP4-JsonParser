#include "FSMMonster.h"
#include "FSMDigit.h"

eventMonster
FSMMonster::getEvent(char c)
{
	eventMonster return_value;
	if (evGen == NULL)
	{
		//ANALIZA CHARS Y DA ESTADO
	}

	else
	{
		evGen->getEvent(c);
		evGen->cycle();
		switch (*(evGen->getReport()))
		{
		case event_t::STARTED:
			return_value = eventMonster::STARTED;
			break;
		case event_t::CONTINUE:
			return_value = eventMonster::CONTINUE;
			break;
		case event_t::ERROR:
			return_value = eventMonster::ERROR;
			break;
		case event_t::QUIT:
			return_value = eventMonster::QUIT;
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
}