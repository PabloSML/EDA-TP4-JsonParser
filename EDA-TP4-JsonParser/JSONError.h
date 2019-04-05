#pragma once

class JSONError
{
public:

	JSONError(bool has Failed = false, const char * Desc = NULL);
	string getErorString(void);
	bool hasFailed(void);
}