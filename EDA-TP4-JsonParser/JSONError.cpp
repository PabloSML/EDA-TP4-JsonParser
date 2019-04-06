#include "JSONError.h"

JSONError::JSONError(bool hasFailed = false, const char * Desc = NULL)
{
	error = hasFailed;
	errorString = Desc;
}

bool JSONError::hasFailed(void){ return error; }

string JSONError::getErrorString() { return errorString; }

void JSONError::setErrorString(string err) { errorString = err; }

void JSONError::setError(bool err) { error = err; }