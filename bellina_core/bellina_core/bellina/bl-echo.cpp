#include "stdafx.h"

#include "bl-echo.h"
#include "bl-types.h"

using namespace std;

using namespace bl;
using namespace bl::echo;

Echo::~Echo() {
	typedef map<string, list<ListenerCallback>*>::iterator it1;
	for (it1 it = listenerRegistry.begin(); it != listenerRegistry.end(); it++) {
		list<ListenerCallback>* callbacks = it->second;

		callbacks->clear();

		delete callbacks;
	}

   	listenerRegistry.clear();
}

void Echo::listen(char* eventName, ListenerCallback callback) {
   	string key = string(eventName);

	list<ListenerCallback>* callbacks;

	auto e2 = listenerRegistry.find(key);

	if (e2 == listenerRegistry.end()) {
		callbacks = new list<ListenerCallback>();
		listenerRegistry[key] = callbacks;
	}
	else {
		callbacks = e2->second;
	}

	callbacks->push_back(callback);
}

void Echo::fire(char* eventName, void*eventData) {
   	string key = string(eventName);

	list<ListenerCallback>* callbacks;

	auto e2 = listenerRegistry.find(key);

	if (e2 != listenerRegistry.end()) {
		callbacks = e2->second;

		list<ListenerCallback>::const_iterator iterator;

		for (iterator = callbacks->begin(); iterator != callbacks->end(); ++iterator) {
			ListenerCallback cb = *iterator;

			cb(eventData);
		}
	}
}

