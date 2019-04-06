#include "JSONObject.h"
#include <cstring>
#include <array>
#include <cctype>
#include <iostream>;
#define INITIALSIZE 100

#define MARKERS "{[\"tfn-0123456789" // Todos los posibles primeros caracteres de un json value

JSONObject::JSONObject(void){}

JSONObject::JSONObject(string& s)
{
	if (!ErrorCheck(s)) { //el string que parseamos esta bien formado
		cantFields = 0;
		string tosave; //realocar vector de fields?
		int sum=0; 
		enum states {INITIAL, NEWFIELD, FIELDNAME, FIELDCONTENT, NEWCONTENT, DONE};
		string::iterator iter;
		iter = s.begin();
		states state = INITIAL;
			while(iter<s.end()){
				switch (state) {
				case INITIAL: { if (*iter == '"') {
					state = NEWFIELD;
				}
				}
							  break;
				case NEWFIELD: {
					cantFields++;
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
					    fields[cantFields].setFieldName(tosave);
				     	state = NEWCONTENT;
				        }
						}
								break;
				case NEWCONTENT: { if (*iter == '{') {
					sum++;
					state = FIELDCONTENT;
				}
				}
								 break;
				case FIELDCONTENT: {
					if (*iter == '{') {
						sum++;
					}
					if (*iter == '}') {
						sum--;
					}
					if (sum != 0) {
						tosave.push_back(*iter);
					}
					else if (sum == 0) {
						sum = 0;
						fields[cantFields].setContent(tosave);
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
	


JSONObject::JSONObject(const char * s)
{
	string to_app;
	to_app.append(s);
	JSONObject(s);

}

const char * 
JSONObject::getFieldType(const char * f)
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
	unsigned int count = getFieldCount();
	for (int i = 0; i < count; i++)
	{
		if (fields[i].getFieldName == f)
		{
			return true;
		}
	}
	return false;
}

/* Devuelve en su nombre el tamaño del campo f, donde por tamaño se
	* entiende:
	* si f es de tipo "object" la cantidad de campos que tiene el objeto
	* (pensar si en este caso conviene generar un JSONObject temporal) con
	* el contenido del campo f y devolver getFieldCount de dicho objeto).
	* si f es de tipo "array" devuelve la cantidad de elementos en el
	* arreglo.
	* si f es de tipo "string" devuelve la cantidad de caracteres en el
	* string.
	* si f es de tipo "number" devuelve sizeof(double).
	* si f es de tipo "bool" devuelve sizeof(bool).
	* si f es no pertenece al objeto devuelve 0. En este último caso genera
	* un error que almacena internamente
	*/
unsigned int
JSONObject::getFieldSize(const char * f)
{
	if (isFieldPresent(f))
	{
		if (!strcmp(getFieldType(f), "bool"))
		{
			return sizeof(bool);
		}
		else if (!strcmp(getFieldType(f), "number"))
		{
			return sizeof(double);
		}
		else if (!strcmp(getFieldType(f), "object"))
		{
			JSONObject* copy = new JSONObject;
			copy =(JSONObject*) copyField(f);
			unsigned int cant = copy->getFieldCount();
			delete copy;
			return cant;
		}
		else if (!strcmp(getFieldType(f), "string"))
		{
			for (int i = 0; i < fieldCount; i++)
			{
				if (fields[i].getFieldName() == string(f))
				{
					return fields[i].getContent().length;
				}
			}
		}
		else if (!strcmp(getFieldType(f), "array"))
		{
			
		}
	}
	else
	{
		return 0;
	}
}