#include "plugin.hpp"


Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
	p->addModel(modelSimpleVCO);
	p->addModel(modelSimpleNoise);
	p->addModel(modelSimpleMult);
	p->addModel(modelSimpleSampleAndHold);
	p->addModel(modelSimpleMixer);
	p->addModel(modelSimpleVCA);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
