#include "JSONError.h"
#define ERROR_STR "Number badly formed"


typedef struct {
	states nextState;
	void(*action)(void* userData);

}FMSCell;





