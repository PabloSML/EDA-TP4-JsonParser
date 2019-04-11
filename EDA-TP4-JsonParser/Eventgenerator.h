#pragma once
#include <iostream>
#include <string>
using namespace std;

enum event_t {STARTED, CONTINUE, ERROR, QUIT};

class Eventgenerator
{
public:

	Eventgenerator(){}

	event_t* getReport() { return report; }
	void setReport(event_t ev) { *(this->report) = ev; }

	string getLabel() const { return label; }
	void setLabel(string label) { this->label = label; }

	virtual void cycle() = 0;

	virtual void getEvent(char c) = 0;

private:
	event_t* report;
	string label;
};

void start(void* userData);
void ok(void* userData);
void error(void* userData);
void quit(void* userData);