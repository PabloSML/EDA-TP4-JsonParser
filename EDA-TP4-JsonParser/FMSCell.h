#include "JSONError.h"
#define ERROR_STR "Number badly formed"


typedef struct {
	states nextState;
	bool(*action)(void* UserData);
}FMSCell;





