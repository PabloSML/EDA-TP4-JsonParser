#include "Eventgenerator.h"

void ok(void* userData) {
	*(event_t*)userData = event_t::CONTINUE;
}

void error(void* userData) {
	*(event_t*)userData = event_t::ERROR;
}

void quit(void* userData) {
	*(event_t*)userData = event_t::QUIT;
}