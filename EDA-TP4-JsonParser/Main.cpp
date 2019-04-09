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

		JSONObject original(json);
		cout << "por ahora bien" << endl;
		getchar();
	}
}
