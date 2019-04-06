#include "JSONObject.h"
#include <cctype>
#include <iostream>;
#define INITIALSIZE 100

#define MARKERS "{[\"tfn-0123456789" // Todos los posibles primeros caracteres de un json value

JSONObject::JSONObject(void){}

JSONObject::JSONObject(string& s){
	parseFields(s);
}

JSONObject::JSONObject(const char * s)
{
	string to_app;
	to_app.append(s);
	parseFields(to_app);

}


void
JSONObject::parseFields(string& s) {
	if (!ErrorCheck(s)) { //el string que parseamos esta bien formado
		fieldCount = howManyFields(s);
		fields = new Field[fieldCount];
		int counter = 0;
		string tosave;
		int sum = 0;
		enum states { INITIAL, NEWFIELD, FIELDNAME, FIELDCONTENT, NEWCONTENT, DONE };
		string::iterator iter;
		iter = s.begin();
		states state = INITIAL;
		while (iter < s.end()) {
			switch (state) {
			case INITIAL: { if (*iter == '"') {
				state = NEWFIELD;
			}
			}
						  break;
			case NEWFIELD: {
				counter++;
				tosave = "";
				tosave.push_back(*iter);
				state = FIELDNAME;
			}
						   break;
			case FIELDNAME: {if (*iter != '"') {
				tosave.push_back(*iter);
			}
							else
			{
				fields[count].setFieldName(tosave);
				state = NEWCONTENT;
			}
			}
							break;
			case NEWCONTENT: { if (*iter == '{') {
				tosave = "";
				sum++;
				state = FIELDCONTENT;
			}
			}
							 break;
			case FIELDCONTENT: {
				if (*iter == '{') {
					sum++;
				}
				if (*iter == '{') {
					sum--;
				}
				if (sum != 0) {
					tosave.push_back(*iter);
				}
				else if (sum == 0) {
					sum = 0;
					fields[count].setContent(tosave);
					state = DONE;
				}

			}
							   break;
			case DONE: {if (*iter == '"') {
				state = NEWFIELD;
			}
			}
					   break;
			}
			iter++;
		}
	}

}

unsigned int
JSONObject::getFieldCount() {
	return fieldCount;
}

const char * JSONObject::getFieldType(const char * f)
{
	bool found = false;
	const char* type;

	for (int i = 0; i < fieldCount && !found; i++)
	{
		found = fields[i].getFieldName() == string(f);

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
	if (!found)
	{
		type = "invalid";
		string errorDesc = string("The field name entered does not match current known fields. getFieldType Fail.");
		err.setError(true);
		err.setErrorString(errorDesc);
	}

	return type;
}

unsigned int
JSONObject::howManyFields(string& s)
{
	unsigned int fields = 0;
	int sum = 0;
	unsigned int i = 0;
	unsigned int end = s.find_last_of('}');
	enum states { START, SEARCHING, FOUNDANDSKIP };
	states state = START;
	while (i < end) {
		switch (state)
		{
		case START:
		{
			if (s[i] == ':')
			{
				fields++;
				state = FOUNDANDSKIP;
			}
		}
		break;

		case FOUNDANDSKIP:
		{
			i = s.find_first_not_of(' ', i);

			if (s[i] == '{')
			{
				sum++;
			}
			else if (s[i] == '}')
			{
				sum--;
			}
			else if (sum == 0)
			{
				state = SEARCHING;
			}
		}
		break;

		case SEARCHING:
		{
			if (s[i] == ',')
			{
				state = START;
			}
		}
		break;
		}
		i++;
	}
	return fields;
}

const char*
JSONObject::getArrayType(const char* f)
{
	bool found = false;
	const char* type;

	for (int i = 0; i < fieldCount && !found; i++)
	{
		found = fields[i].getFieldName() == string(f);

		if (found)
		{
			i--;
			if (fields[i].getFieldType == string("array"))
			{
				string content = fields[i].getContent();
				unsigned int index = content.find_first_of(MARKERS, 1); // Se busca un marker para ver el tipo de elemento y se evita el primer caracter del content ("[") 

				if (index == string::npos || content[index] == '{' || content[index] == 'n')
					type = "object";
				else if (content[index] == '[')
					type = "array";
				else if (content[index] == '\"')
					type = "string";
				else if (isdigit(content[index]) || content[index] == '-')
					type = "number";
				else if (content[index] == 't' || content[index] == 'f')
					type = "bool";
			}
		}
	}
	if (!found)
	{
		type = "invalid";
		string errorDesc = string("The array name entered does not match current known arrays. getArrayType Fail.");
		err.setError(true);
		err.setErrorString(errorDesc);
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

bool
JSONObject::isFieldPresent(const char* f)
{
	bool found = false;
	unsigned int count = fieldCount;
	for (int i = 0; i < fieldCount && !found; i++)
	{
		if (fields[i].getFieldName == string(f))
		{
			found = true;
		}
	}

	return found;
}

