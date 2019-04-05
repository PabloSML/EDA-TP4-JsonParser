#include "JSONObject.h"

JSONObject::JSONObject(void){}

JSONObject::JSONObject(string& s)
{
	
}

JSONObject::JSONObject(const char * s)
{
	
}

const char * 
JSONObject::getFieldType(const char * f)
{
	bool found = false;
	const char* type = "invalid";

	for (int i = 0; i < fieldCount && !found; i++)
	{
		found = fields[i].getFieldName() == f;

		if (found)
		{
			i--;
			if (fields[i].getFieldType() == string("object"))
				type = "object";
			else if (fields[i].getFieldType() == string("array"))
				type = "array";
			else if (fields[i].getFieldType() == string("string"))
				type = "string";
			else if (fields[i].getFieldType() == string("number"))
				type = "number";
			else if (fields[i].getFieldType() == string("bool"))
				type = "bool";
		}
	}

	return type;
}

void*
JSONObject::copyField(const char* f)	//le falta todavia, solo copie lo que hicimos en clase
{
	bool found = false;
	for (int i = 0; i < fieldCount && !found; i++)
	{
		found = fields[i].getFieldName() == f;

		if (found)
		{
			i--;
			if (fields[i].getFieldType() == string("object"))
				JSONObject* newJSON = new JSONObject(fields[i].getContent());
			else if (fields[i].getFieldType() == string("number"))
				double* newJSON = new double(stod(fields[i].getContent()));
		}
	}
}
