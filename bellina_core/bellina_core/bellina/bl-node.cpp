#include "stdafx.h"

#include"g2/g2.h"

#include"bl-globals.h"
#include"bl-shadow-node.h"
#include"bl-node.h"
#include"bl-flags.h"
#include"bl-echo.h"
#include"bl-util.h"
#include"bl-shadow.h"

using namespace std;

using namespace g2;
using namespace g2::flags;

using namespace bl;
using namespace bl::echo;
using namespace bl::flags;

BasePluginCtx* Node::getPluginCtxFromShadow(char* pluginName, char* signature, PluginCtxFactory factory) {
	ShadowNode* shadow = shadow_::getShadowNode(this);

	return shadow->getPluginCtx(pluginName, signature, factory);
}

Node::Node(Node* parent) {

	this->parent = parent;

	nid = 0;	

	global_pos.x = 0;
	global_pos.y = 0;

	canvas = 0;
	texture_ = 0;
	mask_ = 0;

	w = h = -1;
	font_name = 0;
	font_size = 24;
	text_ = 0;

	canvasOpacity1(1.f);
	canvasOpacity2(1.f);

	textOpacity(1.f);

	pos(0, 0);
	padding(0, 0, 0, 0);

	color1(255, 0, 0);
	color2(255, 0, 0);
	textColor(255, 255, 255);

	textTops(false);

	borderColor(BL_BORDER_ALL, 255, 255, 0);
	borderOpacity(BL_BORDER_ALL, 1.f);
	borderThickness(BL_BORDER_ALL, 1);
	borderTops(BL_BORDER_ALL, false);

	flags = G2_COLOR_SOLID | G2_ALPHA_NONE | BL_TEXT_ALIGN_DEFAULT;
}

void Node::id(char* _id) {
	nid = _strdup(_id);
}

void Node::textTops(bool tops) {
	text_tops_canvas = tops;
}

void Node::color1(unsigned char _r, unsigned char _g, unsigned char _b) {
	r1 = _r; g1 = _g; b1 = _b;
}

void Node::color2(unsigned char _r, unsigned char _g, unsigned char _b) {
	r2 = _r; g2 = _g; b2 = _b;
}

void resetCanvasRef(Node *node, int w, int h) {
	if (node->canvas) delete node->canvas;
	// test new CanvasRef();

	//if (node->nid[0]=='r' || node->nid[0] == 'g')
		//printf("creating node canvas %i %i for %s\n", w, h, node->nid);
	node->canvas = g2::createCanvas(w,h);
}

void Node::dim(int _w, int _h) {
	if (_w < 4) _w = 4;
	if (_h < 4) _h = 4;

	if (_w != w || _h != h) {
		w = _w; h = _h;
		resetCanvasRef(this, _w, _h);
	}
}

void Node::pos(int _x, int _y) {
	x = _x; y = _y;
}

void Node::addKid(Node* kid) {
	kids.push_back(kid);
}

void Node::text(char *_text) {
	text_ = _strdup(_text);

	if (!font_name) font("arial", font_size);
}

void Node::font(char *name, int size) {
	font_size = size;

	if (font_name) delete[] font_name;
	font_name = _strdup(name);

	g2::font(font_name, size);

	fontHeight = g2::font_height();
}

void Node::textColor(unsigned char r, unsigned char g, unsigned char b) {
	text_red = r; text_green = g; text_blue = b;
}

void Node::textOpacity(float alpha) {
	text_alpha = alpha;
}

void Node::padding(int l, int t, int r, int b) {
	padding_left = l; padding_top = t; padding_right = r; padding_bottom = b;

	if (l < 1 && t < 1 && r < 1 && b < 1)
		removeFlag(G2_PAD);
	else
		addFlag(G2_PAD);
}

void Node::canvasOpacity1(float opacity) {
	alpha1_canvas = opacity;
}

void Node::canvasOpacity2(float opacity) {
	alpha2_canvas = opacity;
}

void Node::texture(TextureRef* ref) {
	texture_ = ref;
}

void Node::mask(TextureRef* ref) {
	mask_ = ref;
}

void Node::resetFlags(int flags_) {
	flags = flags_;
}

void Node::addFlag(int flag) {
	flags |= flag;
}

void Node::removeFlag(int flag) {
	flags &= ~flag;
}

Node::~Node() {
	// id
	if (nid) delete[] nid;

	// font
	if (font_name) delete[] font_name;

	// text
	if (text_) delete[] text_;

	// texture ref
	if (texture_) delete texture_;
	// test new TextureRef();

	// mask ref
	if (mask_) delete mask_;

	// do not delete mask_

	// canvas ref
	if (canvas) delete canvas;
	// test new CanvasRef();

	// kids
	list<Node*>::const_iterator iterator;

	for (iterator = kids.begin(); iterator != kids.end(); ++iterator) {
		Node *kid = *iterator;

		delete kid;
		// test new Node();
	}
}

void Node::setColorSolidFlag() {
	flags &= ~G2_TEXTURE;
	flags &= ~G2_COLOR_ANY;
	flags |= G2_COLOR_SOLID;
}

void Node::setColorHorizGradientFlag() {
	flags &= ~G2_TEXTURE;
	flags &= ~G2_COLOR_ANY;
	flags |= G2_COLOR_HORIZ_GRADIENT;
}

void Node::setColorVertGradientFlag() {
	flags &= ~G2_TEXTURE;
	flags &= ~G2_COLOR_ANY;
	flags |= G2_COLOR_VERT_GRADIENT;
}

void Node::setTextureFlag() {
	flags |= G2_TEXTURE;
	flags &= ~G2_COLOR_ANY;
}

void Node::borderColor(unsigned int border_flag, unsigned char r, unsigned char g, unsigned char b) {
	if (border_flag & BL_BORDER_LEFT) {
		border_left.red = r;
		border_left.green = g;
		border_left.blue = b;
	}

	if (border_flag & BL_BORDER_TOP) {
		border_top.red = r;
		border_top.green = g;
		border_top.blue = b;
	}

	if (border_flag & BL_BORDER_RIGHT) {
		border_right.red = r;
		border_right.green = g;
		border_right.blue = b;
	}

	if (border_flag & BL_BORDER_BOTTOM) {
		border_bottom.red = r;
		border_bottom.green = g;
		border_bottom.blue = b;
	}
}

void Node::borderThickness(unsigned int border_flag, int thickness) {
	if (border_flag & BL_BORDER_LEFT) border_left.thickness = thickness;
	if (border_flag & BL_BORDER_TOP) border_top.thickness = thickness;
	if (border_flag & BL_BORDER_RIGHT) border_right.thickness = thickness;
	if (border_flag & BL_BORDER_BOTTOM) border_bottom.thickness = thickness;
}

void Node::borderTops(unsigned int border_flag, bool tops) {
	if (border_flag & BL_BORDER_LEFT) border_left.topsCanvas = tops;
	if (border_flag & BL_BORDER_TOP) border_top.topsCanvas = tops;
	if (border_flag & BL_BORDER_RIGHT) border_right.topsCanvas = tops;
	if (border_flag & BL_BORDER_BOTTOM) border_bottom.topsCanvas = tops;
}

void Node::borderOpacity(unsigned int border_flag, float alpha) {
	if (border_flag & BL_BORDER_LEFT) border_left.alpha = alpha;
	if (border_flag & BL_BORDER_TOP) border_top.alpha = alpha;
	if (border_flag & BL_BORDER_RIGHT) border_right.alpha = alpha;
	if (border_flag & BL_BORDER_BOTTOM) border_bottom.alpha = alpha;
}

