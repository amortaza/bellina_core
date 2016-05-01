#include "stdafx.h"

#include "bl-types.h"
#include "bl-core.h"
#include "bl-globals.h"
#include "bl-plugin.h"
#include "bl-plugin-bubble.h"
#include "bl-node.h"

#include "BasePluginCtx.h"

using namespace std;

using namespace bl;
using namespace bl::_;
using namespace bl::plugin;

namespace bl {
	namespace plugin {
		//map<string, Plugin*> pluginByNameSignatureKey;
		map<string, Plugin*> pluginRegistryByName;

		map<string, int> pluginIntProperty;
		map<string, bool> pluginBoolProperty;

		bool isRegistered(char* name) {
			string key(name);

			auto e2 = pluginRegistryByName.find(key);
			
			return e2 != pluginRegistryByName.end();
		}
	}
}

void bl::pluginCtxOnNode(char* pluginName, char* signature, PluginCtxFactory factory) {
	BasePluginCtx* ctx = current_node->getPluginCtxFromShadow(pluginName, signature, factory);
	
	ctx->onNode(signature);
}

/*void bl::pluginSetInt(char* name, char* prop_name, int value) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	pluginIntProperty[key] = value;
}

void bl::pluginSetBool(char* name, char* prop_name, bool value) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	pluginBoolProperty[key] = value;
}

int bl::pluginGetInt(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = pluginIntProperty.find(key);
	if (e2 == pluginIntProperty.end()) throw "plugin value not found in pluginGetInt";

	return e2->second;
}

bool bl::pluginGetBool(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = pluginBoolProperty.find(key);
	if (e2 == pluginBoolProperty.end()) throw "plugin value not found in pluginGetBool";

	return e2->second;
}

bool bl::pluginHasInt(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = pluginIntProperty.find(key);
	if (e2 == pluginIntProperty.end()) return false;

	return true;
}

bool bl::pluginHasBool(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = pluginBoolProperty.find(key);
	if (e2 == pluginBoolProperty.end()) return false;

	return true;
}*/

void bl::pluginLoad(PluginLoad load) {
	load();
}

void bl::pluginRegister(char* pluginName, 
						PluginInit init, 
						PluginOnNode onNode, 
						PluginUninit uninit) {

	if (plugin::isRegistered(pluginName)) {
		printf("Plugin \"%s\" is already loaded.  Ignoring re-load request.\n", pluginName);
		return;
	}

	Plugin* plugin = new Plugin();

	plugin->name.assign(pluginName, strlen(pluginName));
	plugin->init = init;
	plugin->onNode = onNode;
	plugin->uninit = uninit;

	pluginRegistryByName[plugin->name] = plugin;

	if (init != nullptr) init();
}


void bl::use(char* pluginName, char* signature) {
	on(pluginName, signature, nullptr);
}

/*void bl::use_1s(char* pluginName, char* sArg) {
	on_1s(pluginName, sArg, nullptr);
}

void bl::on_1s(char* pluginName, char* sArg, PluginCallback cb) {
	if (!isRegistered(pluginName)) {
		printf("Unregistered plugin cannot be used, see \"%s\"\n", pluginName);
		return;
	}

	string key(pluginName);

	auto e2 = pluginMap.find(key);

	Plugin* plugin = e2->second;

	_::pluginBubble->setCallback(cb, current_node, pluginName);

	plugin->onNode();
}*/

void bl::on(char* pluginName, char* signature, PluginCallback cb) {
	if (!isRegistered(pluginName)) {
		printf("Unregistered plugin cannot be used, see \"%s\"\n", pluginName);
		return;
	}

	string key(pluginName);

	auto e2 = pluginRegistryByName.find(key);

	if (e2 == pluginRegistryByName.end()) {
		printf("Unexpectedly did not find %s in bl::on\n",key.c_str());
		return;
	}

	Plugin* plugin = e2->second;

	_::pluginBubble->addCallback(cb, current_node, pluginName, signature);

	plugin->onNode(signature);
}

void bl::pluginCall(char* pluginName, char* signature, Node* node, void* eventData) {
	_::pluginBubble->bubbleUp(node, pluginName, signature, eventData);
}

void bl::plugin::uninit() {
	//
	typedef map<string, Plugin*>::iterator it1;
	for (it1 it = pluginRegistryByName.begin(); it != pluginRegistryByName.end(); it++) {
		Plugin* plugin = it->second;

		if (plugin->uninit != nullptr) plugin->uninit();

		delete plugin;
	}

	//
	pluginIntProperty.clear();
	pluginBoolProperty.clear();
}

string bl::plugin::util::getPluginKey(char*nodeId, char* pluginName, char* signature) {
	string key(nodeId);
	key.append(":");
	key.append(pluginName);
	key.append(".");
	key.append(signature);
	return key;
}

string bl::plugin::util::getPluginKey(char* pluginName, char* signature) {
	string key(pluginName);
	
	key.append(".");
	key.append(signature);

	return key;
}
		