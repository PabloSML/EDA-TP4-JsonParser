#include <iostream>
#include <string>
#include <fstream>
#include "field.h"
#include "JSONObject.h"
#include "JSONError.h"
using namespace std;

int main(void)
{
	int size;
	char* buffer;
	string json;

	ifstream myfile("test.json", ios::in | ios::binary);

	if (myfile.is_open())
	{
		myfile.seekg(0, myfile.end);
		size = myfile.tellg();

		buffer = new char[size];
		myfile.seekg(0, ios::beg);
		myfile.read(buffer, size);
		myfile.close();

		json = string(buffer);

		delete[] buffer;


		// A partir de aca son pruebas arbitrarias que estoy haciendo
		JSONObject original(json);
		JSONObject* glossaryCopy = (JSONObject*)original.copyField("glossary");
		JSONObject* glosdivCopy = (JSONObject*)glossaryCopy->copyField("GlossDiv");
		JSONObject* gloslistCpy = (JSONObject*)glosdivCopy->copyField("GlossList");
		JSONObject* glosentryCpy = (JSONObject*)gloslistCpy->copyField("GlossEntry");
		JSONObject* glosdefCpy = (JSONObject*)glosentryCpy->copyField("GlossDef");

		original.print();
		cout << endl;
		glossaryCopy->print();
		cout << endl;
		glosdivCopy->print();
		cout << endl;
		gloslistCpy->print();
		cout << endl;
		glosentryCpy->print();
		cout << endl;
		glosdefCpy->print();
		getchar();
	}
}
