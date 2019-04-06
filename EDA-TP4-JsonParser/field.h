#pragma once
#include <iostream>
#include <string>
using namespace std;

class Field
{
public:
	Field(){
		fieldType = NULL;
		fieldName = string(NULL);
		content = string(NULL);
	}

	void setFieldName(string n);
	void setContent(string c);
	void setFieldType(const char* t);
	const char* getFieldType();
	string getFieldName();
	string getContent();

private:
	const char* fieldType;
	string fieldName;
	//string& fieldName;
	string content;
};