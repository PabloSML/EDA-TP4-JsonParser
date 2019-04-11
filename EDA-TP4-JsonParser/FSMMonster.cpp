#include "FSMMonster.h"

eventMonster
FSMMonster::getEvent(char c)
{
	if (evGen == NULL)
	{
		//ANALIZA CHARS Y DA ESTADO
	}

	else
	{
		evGen->getEvent(c);
		evGen->cycle();

	}
}

void
FSMMonster::cycle(eventMonster ev)
{

}