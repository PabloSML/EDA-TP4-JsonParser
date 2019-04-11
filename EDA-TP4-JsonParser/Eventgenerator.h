#pragma once
#include <iostream>
#include <string>
using namespace std;

enum event_t {CONTINUE, ERROR, QUIT};

class Eventgenerator
{
public:

	Eventgenerator(){}


	string getLabel() const { return label; }
	void setLabel(string label) { this->label = label; }

	virtual event_t getReport() = 0;
	virtual void setReport(event_t ev) = 0;

	virtual void cycle() = 0;
	virtual void getEvent(char c) = 0;

private:
	string label;
};