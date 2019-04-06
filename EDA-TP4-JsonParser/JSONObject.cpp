#include "JSONObject.h"
#include <cstring>
#include <array>
#include <cctype>
#include <iostream>;
#define INITIALSIZE 100

//#define MARKERS "{[\"tfn-0123456789" // Todos los posibles primeros caracteres de un json value

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
		int i = 0;
		for (int counter = 0; counter < fieldCount; counter++) {
			bool saved = false;
			int sum = 0;
			int aux = s.find_first_of('"', i);  //guardo el name
			i = aux + 1;
			aux = s.find_first_of('"', i);
			fields[counter].setFieldName(s.substr(i, aux + 1));
			i = aux + 1;
			i = s.find_first_not_of(': ', i);
			while (!saved) {     //quiero guardar el content segun que es:objeto array string o cualquier otra cosa
				int start = i;
				int end;
				if (start == '"') {           //caso 1: si me encuentro con un string 
					start++;
					end = s.find_first_of('"', start);
					/*int check=s.find_first_of("\"); no me deja escapar la barra invertida*/
				}
				if (start == '{') {        //caso 2: si me encuentro con un objeto
					sum++;
					end = start + 1;
					for (end; sum != 0; end++) {
						if (s[end] == '{') {
							sum++;
						}
						if (s[end] == '}') {
							sum--;
						}
					}
				}
				if (start == '[') {        //caso 3: si me encuentro con un array
					sum++;
					end = start + 1;
					for (end; sum != 0; end++) {
						if (s[end] == '[') {
							sum++;
						}
						if (s[end] == ']') {
							sum--;
						}
					}
				}
				else {
					end = s.find_first_of(",{");     //caso 4: si me encuentro con cualquier otra cosa
				}
				fields[counter].setContent(s.substr(start, end));
				i = end + 1;
				saved = true;
			}
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
				unsigned int index = content.find_first_not_of(' '); // Se busca un marker para ver el tipo de elemento ({[\"tfn-0123456789)

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
			void* copy;
			i--;
			if (fields[i].getFieldType() == string("object"))
			{
				copy = new JSONObject(fields[i].getContent());
			}
			else if (fields[i].getFieldType() == string("array"))
			{
				string type = string(getArrayType(f));

			}
			else if (fields[i].getFieldType() == string("string"))
			{
				copy = new string(fields[i].getContent());
			}
			else if (fields[i].getFieldType() == string("number"))
			{
				copy = new double(stod(fields[i].getContent()));
			}
			else if (fields[i].getFieldType() == string("bool"))
			{

			}
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
	unsigned int size = 0;
	if (isFieldPresent(f))
	{
		if (!strcmp(getFieldType(f), "bool"))
		{
			size = sizeof(bool);
		}
		else if (!strcmp(getFieldType(f), "number"))
		{
			size = sizeof(double);
		}
		else if (!strcmp(getFieldType(f), "object"))
		{
			JSONObject* copy =(JSONObject*) copyField(f);
			unsigned int cant = copy->getFieldCount();
			delete copy;
			size = cant;
		}
		else if (!strcmp(getFieldType(f), "string"))
		{
			for (int i = 0; i < fieldCount; i++)
			{
				if (fields[i].getFieldName() == string(f))
				{
					size = fields[i].getContent().length;
				}
			}
		}
		else if (!strcmp(getFieldType(f), "array"))
		{
			int cont = 0;

			for (int i = 0; i < fieldCount; i++)
			{
				if (fields[i].getFieldName() == string(f))
				{
					if (!strcmp(getArrayType(f), "string"))
					{
						for (int a = 0; a < fields[i].getContent().length; a++)
						{
							if (fields[i].getContent()[a] == '"')
							{
								cont++;
							}
						}
						return cont / 2;
					}
					else if (!strcmp(getArrayType(f), "number") || !strcmp(getArrayType(f), "bool"))
					{
						for (int a = 0; a < fields[i].getContent().length; a++)
						{
							if (fields[i].getContent()[a] == ',')
							{
								cont++;
							}
						}
						return cont + 1;
					}
					else if (!strcmp(getArrayType(f), "object"))
					{
						int elements = 0;
						for (int a = 0; a < fields[i].getContent().length; a++)
						{
							if (fields[i].getContent()[a] == '{')
							{
								cont++;
							}
							if (fields[i].getContent()[a] == '}')
							{
								cont--;
							}
							if (cont == 0)
							{
								elements++;
							}
						}
						size = elements;
					}
					else if (!strcmp(getArrayType(f), "array"))
					{
						int elements = 0;
						for (int a = 0; a < fields[i].getContent().length; a++)
						{
							if (fields[i].getContent()[a] == '[')
							{
								cont++;
							}
							if (fields[i].getContent()[a] == ']')
							{
								cont--;
							}
							if (cont == 0)
							{
								elements++;
							}
						}
						size = elements;
					}
				}
			}
		}
	}
	return size;
}