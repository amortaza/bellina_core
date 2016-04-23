#pragma once

#include "bellina/bl-node.h" // z-index.h (plugin) needs to be self contained

namespace z_index {
	void init();
	void uninit();

	void onNode(PluginCallback);
	void tickBeforeEnd();
}