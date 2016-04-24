#include "stdafx.h"

#include "bellina/bellina.h"

#include "resize.h"

using namespace bl;
using namespace bl::listener;

namespace resize {
	char* plugin_name = "resize";

	/*char* lastDownNodeId = 0;
	Xel::Mouse::Button lastDownButton;

	void freeId() {
		if (lastDownNodeId) {
			delete [] lastDownNodeId;
			lastDownNodeId = 0;
		}
	}
*/
	void init() {
		/*
		bl::listenLongTerm("mouse down", [](void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (lastDownNodeId && !bl::util::isNode(event->node, lastDownNodeId) ) {
				freeId();
			}
		});

		bl::listenLongTerm("mouse up", [](void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (lastDownNodeId && !bl::util::isNode(event->node, lastDownNodeId)) {
				freeId();
			}
		});*/
	}

	void uninit() {
		//freeId();
	}

	void onNode() {
		/*

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (lastDownNodeId) delete[] lastDownNodeId;

			lastDownNodeId = _strdup(bl::node->nid);
			lastDownButton = button;

			return true;
		});

		bl::onMouseUp([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (bl::util::isNode(bl::node, lastDownNodeId ) && button == lastDownButton ) {
				MouseClickEvent event;
				event.mx = mx;
				event.my = my;
				event.button = button;
				event.node = bl::node;

				bl::pluginCall(plugin_name, bl::node, &event);

				bl::fire("click", &event);
			}

			freeId();

			return true;
		});*/
	}
}

void resize::load() {
	bl::pluginRegister(
		resize::plugin_name,
		resize::init,
		resize::onNode,
		nullptr, 
		resize::uninit);
}