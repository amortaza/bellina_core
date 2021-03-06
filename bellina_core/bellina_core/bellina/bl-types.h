#pragma once

#include <functional>

#include "Xel/Xel.h"
#include "pango/pango.h"

using namespace std;

namespace bl { extern class Node; }
namespace bl { extern class ShadowNode; }

using namespace pango;

namespace bl {
	extern class Widget;

	typedef function<bool(int mx, int my, Node* bubbledFrom)> NodeMouseMoveCallback;
	typedef function<bool(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> NodeMouseDownCallback;
	typedef function<bool(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> NodeMouseUpCallback;
	typedef function<bool(int amount, int mx, int my, Node* bubbledFrom)> NodeMouseScrollCallback;

	//
	typedef function<void(ShadowNode*)> ShadowCallback;
	typedef function<void(void*)> ListenerCallback;

	// 
	typedef function<Widget*(char* id)> Constructor;

	//	
	struct BorderSide {
		unsigned char red, green, blue;
		int thickness;
		float alpha;
		bool topsCanvas;
	};

	struct Point {
		int x, y;
	};

	struct Color {
		unsigned char r, g, b;
	};
}