#include "stdafx.h"

#include <ctime>

#include "g2/g2.h"

#include "bellina/bellina.h"

#include "plugins/focus/focus.h"
#include "plugins/click/click.h"
#include "plugins/double-click/double-click.h"
#include "plugins/node-drag/node-drag.h"
#include "plugins/z-index/z-index.h"
#include "plugins/mouse-in/mouse-in.h"
#include "plugins/resize/resize.h"
#include "plugins/mouse-drag/mouse-drag.h"

#include "widgets/button/button.h"

using namespace node_drag;
using namespace bl;
using namespace bl::flags;

using namespace g2::flags;

g2::TextureRef* guitar;
g2::TextureRef* jet;

int frame = 0;
long double first = time(0);

void Render_My_Bellina() {

	frame++;
	if (frame % 512 == 0) {
		long double delta = time(0) - first;
		printf("FPS = %1.2f\n", (float)frame / delta);
	}

	bl::root();
	{
		bl::color(50, 0, 10);

		button::begin("bad");
		button::title("Jordan");
		button::click([]() {printf("!!! click\n"); });
		button::end();

		/*bl::div(); {

			bl::id("red");

			bl::color(150, 0, 50);
			bl::pos(100, 100);
			bl::dim(320, 240);

			bl::removeFlag(BL_TEXT_ALIGN_ANY);
			bl::addFlag(BL_TEXT_ALIGN_RIGHT | BL_TEXT_ALIGN_BOTTOM);
			bl::text("Clown");

			//bl::on("node-drag", [](void* e) { printf("red\n"); return true; });

			/*bl::on("resize", [](void* e) {
				printf("resize red\n");
				return true; });*/
		//} 
		//bl:end();

		//bl::use("z-index");
	}
	bl::end();
	
	bl::paint();
}

void Init_OnGL() {
	bl::init();

	// needs to be before click
	pango::load(mouse_in::load);

	//pango::load(focus::load);
	pango::load(click::load);

	//pango::load(double_click::load);

	pango::load(node_drag::load);

	//bl::pluginSetBool(z_index::plugin_name, "")
	//pango::load(z_index::load);

	

	//pango::load(resize::load);
}

void UnInit() {
	bl::uninit();
}