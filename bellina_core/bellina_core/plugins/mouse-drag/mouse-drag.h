#pragma once

#include "bellina/bl-node.h" 

using namespace bl;

namespace mouse_drag {
	void load();

	void init();
	void uninit();

	void onNode();

	struct MouseDragEvent {
		int mx;
		int my;

		int dx, dy;
		int deltaX, deltaY;

		Node* node;
	};
}