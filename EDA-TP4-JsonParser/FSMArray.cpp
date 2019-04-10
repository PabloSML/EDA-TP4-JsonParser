#include "FSMArray.h"

FSMArray::FSMArray(JSONError err) {
	state
	this->err = err;
}

statesArray FSMArray::getState() {
	return currentState;
}
