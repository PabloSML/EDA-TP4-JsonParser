#include "JSONObject.h"
#include <cstring>
#include <array>
#include <cctype>
#include <iostream>;
#define INITIALSIZE 100

using namespace std;
//#define MARKERS "{[\"tfn-0123456789" // Todos los posibles primeros caracteres de un json value

JSONObject::JSONObject(void){}

JSONObject::JSONObject(string& s){
	unparsed = s;
	parseFields(s);
}

JSONObject::JSONObject(const char * s)
{
	string to_app;
	to_app.append(s);
	unparsed = to_app;
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
				int end=start+1;
				if (start == '"') {           //caso 1: si me encuentro con un string 
					start++;
					end = s.find_first_of('"', start);
					int check = s.find_first_of(R"(\)", start);  //las comillas no pueden estar escapadas por la barra
					while (check == end - 1)
					{
						aux=end + 1;
						end = s.find_first_of('"', aux);
						check = s.find_first_of(R"(\)", aux);

					}
				}
				else if (start == '{') {        //caso 2: si me encuentro con un objeto
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
				else if (start == '[') {        //caso 3: si me encuentro con un array
					sum++;
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
					end = s.find_first_of(",{", start+1);     //caso 4: si me encuentro con cualquier otra cosa
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

string 
JSONObject::getUnparsed(void)
{
	return unparsed;
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
JSONObject::copyField(const char* f)
{
	bool found = false;
	void* copy = NULL;
	for (int i = 0; i < fieldCount && !found; i++)
	{
		found = fields[i].getFieldName() == string(f);

		if (found)
		{
			i--;
			if (fields[i].getFieldType() == string("object"))
			{
				string content = string(fields[i].getContent());
				JSONObject* newObject = new JSONObject(content);
				copy = newObject;
			}
			else if (fields[i].getFieldType() == string("array"))
			{
				string type = string(getArrayType(f));
				string arrContent = string(fields[i].getContent());
				unsigned int size = getFieldSize(f);

				if (type == string("object"))
				{
					JSONObject* newObjectArr = new JSONObject[size];
					for (int j = 0; j < size; j++)
					{
						JSONObject* temp = (JSONObject*)copyArrayValue(f, j);
						string tempContent = temp->getUnparsed();
						newObjectArr[j].parseString(tempContent);
						delete temp;
					}
					copy = newObjectArr;
				}
				else if (type == string("array"))
				{

				}
				else if (type == string("string"))
				{
					string* newStringArr = new string[size];
					for (int j = 0; j < size; j++)
					{
						string* temp = (string*)copyArrayValue(f, j);
						newStringArr[j] = *(temp);
						delete temp;
					}
					copy = newStringArr;
				}
				else if (type == string("number"))
				{
					double* newDoubleArr = new double[size];
					for (int j = 0; j < size; j++)
					{
						double* temp = (double*)copyArrayValue(f, j);
						newDoubleArr[j] = *(temp);
						delete temp;
					}
					copy = newDoubleArr;
				}
				else if (type == string("bool"))
				{
					bool* newBoolArr = new bool[size];
					for (int j = 0; j < size; j++)
					{
						bool* temp = (bool*)copyArrayValue(f, j);
						newBoolArr[j] = *(temp);
						delete temp;
					}
					copy = newBoolArr;
				}
			}
			else if (fields[i].getFieldType() == string("string"))
			{
				string* newString = new string(fields[i].getContent());
				copy = newString;
			}
			else if (fields[i].getFieldType() == string("number"))
			{
				double* newDouble = new double(stod(fields[i].getContent()));
				copy = newDouble;
			}
			else if (fields[i].getFieldType() == string("bool"))
			{
				if (fields[i].getContent() == string("true"))
				{
					bool* newTrue = new bool(true);
					copy = newTrue;
				}
				else
				{
					bool* newFalse = new bool(false);
					copy = newFalse;
				}
			}
		}
	}
	if (!found)
	{
		string errorDesc = string("The field name entered does not match current known fields. copyField Fail.");
		err.setError(true);
		err.setErrorString(errorDesc);
	}

	return copy;
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
							if (fields[i].getContent()[a] == '\"')
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

void
JSONObject::print(void)
{
	cout << "Start of JSON object" << endl;
	cout << "FIELD" << "\t:\t" << "TYPE" << endl;
	cout << "---------------" << endl;
	for (int i = 0; i < fieldCount; i++)
	{
		cout << fields[i].getFieldName() << "\t:\t" << fields[i].getFieldType << endl;
	}
	cout << "End of JSON object" << endl;
}

bool
JSONObject::isEmpty(void)
{
	if (fieldCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void*
JSONObject::copyArrayValue(const char* f, unsigned int pos)
{
	void* copy=NULL;
	if (isFieldPresent(f))
	{
		if (pos < getFieldSize(f))
		{
			for (int i = 0; i < fieldCount; i++)
			{
				if (fields[i].getFieldName() == string(f))
				{
					string contenido = fields[i].getContent();
					string valor = string(NULL);
					if (!strcmp(getArrayType(f), "object"))
					{
						int comas = 0, cont = 0;
						for (int b = 1; b < (contenido.length - 1); b++)
						{
							if (contenido[b] == '{')
							{
								cont++;
							}
							else if (contenido[b] == '}')
							{
								cont--;
								b++;
								if (cont == 0)
								{
									comas++;
								}
							}

							if (comas == pos)
							{
								b++;
								for (; contenido[b] != ',' || b < contenido.length; b++)
								{
									valor.push_back(contenido[b]);
								}
							}
						}
						JSONObject* obj = new JSONObject(valor);
						copy = obj;
					}
					if (!strcmp(getArrayType(f), "number"))
					{
						int comas = 0;
						for (int b = 0; b < contenido.length; i++)
						{
							if (contenido[b] == ',')
							{
								comas++;
							}
							if (comas == pos)
							{
								b++;
								for (; contenido[b] != ',' || b < contenido.length; b++)
								{
									valor.push_back(contenido[b]);
								}
							}
						}
						double* num = new double(stod(valor));
						copy = num;
					}
					if (!strcmp(getArrayType(f), "bool"))
					{
						int comas = 0;
						bool* tof=NULL;
						for (int b = 0; b < contenido.length; i++)
						{
							if (contenido[b] == ',')
							{
								comas++;
							}
							if (comas == pos)
							{
								b++;
								for (; contenido[b] != ',' || b < contenido.length; b++)
								{
									valor.push_back(contenido[b]);
								}
							}
						}
						if (valor == "false" || valor == "0")
						{
							tof = new bool(false);
						}
						else if (valor == "true" || valor == "1")
						{
							tof = new bool(true);
						}
						copy = tof;
					}
					if (!strcmp(getArrayType(f), "string"))
					{
						int comas = 0, cont = 0;
						for (int b = 0; b < contenido.length; i++)
						{
							if (contenido[b] == '\"')
							{
								if (cont == 0)
								{
									cont++;
								}
								else
								{
									cont--;
									comas++;
									b++;
								}
							}
							if (comas == pos)
							{
								b+=2;
								for (; contenido[b] != '\"' || b < contenido.length; b++)
								{
									valor.push_back(contenido[b]);
								}
							}
						}
						copy = &valor;
					}
					if (!strcmp(getArrayType(f), "array"))
					{
						int comas = 0, cont = 0;
						for (int b = 1; b < (contenido.length-1); i++)
						{
							if (contenido[b] == '[')
							{
								cont++;
							}
							else if(contenido[b] == ']')
							{
								cont--;
								b++;
								if (cont == 0)
								{
									comas++;
								}
							}
							
							if (comas == pos)
							{
								b++;
								for (; contenido[b] != ',' || b < (contenido.length-1); b++)
								{
									valor.push_back(contenido[b]);
								}
							}
						}
						Field* arreglo = new Field;
						arreglo->setFieldName(string("ArrayValueCopy"));
						arreglo->setContent(valor);
						arreglo->setFieldType(getArrayType("ArrayValueCopy"));
						copy = arreglo;
					}
				}
			}
		}
		else
		{
			string errorDesc = string("The position entered is grater than the number of elements within the array. copyArrayValue Fail.");
			err.setError(true);
			err.setErrorString(errorDesc);
		}
	}
	else
	{
		string errorDesc = string("The array name entered does not match current known arrays. copyArrayValue Fail.");
		err.setError(true);
		err.setErrorString(errorDesc);
	}

	return copy;
}