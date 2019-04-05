#pragma once
#include <iostream>
#include <string>
using namespace std;

class field
{
public:
	field() {}

	const char* getFieldType() { return fieldType; }
	string getFieldName() { return fieldName; }
	string getContent() { return content; }

private:
	const char* fieldType;
	string fieldName;
	string content;
};