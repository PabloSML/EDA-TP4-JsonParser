#pragma once

enum event_t {STARTED, CONTINUE, ERROR, QUIT};

class Eventgenerator
{
public:

	Eventgenerator(){}

	event_t getReport() { return ev; }
	void setReport(event_t ev) { this->ev = ev; }

	virtual void cycle() = 0;

	virtual void getEvent(char c) = 0;

private:

	event_t ev;
};