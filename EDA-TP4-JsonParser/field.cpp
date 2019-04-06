#include "field.h"

const char*
Field::getFieldType() { 
	return fieldType; }

string
Field::getFieldName() { 
	return fieldName;
}

string
Field::getContent() { 
	return content; 
}

void 
Field::setFieldName(string n) {
	fieldName = n;
}

void Field::setContent(string c) {
	content = c;
}
void Field::setFieldType(const char* t) {
	fieldType = t;
}