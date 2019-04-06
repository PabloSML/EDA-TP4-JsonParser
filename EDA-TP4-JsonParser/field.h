#pragma once
#include <iostream>
#include <string>
using namespace std;

class Field
{
public:
	void setFieldName(string& n);
	void setContent(string& c);
	void setFieldType(const char* t);
	const char* getFieldType();
	string getFieldName();
	string getContent();

private:
	const char* fieldType;
	string& fieldName;
	string content;
};