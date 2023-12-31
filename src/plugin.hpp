#pragma once
#include <rack.hpp>


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
// extern Model* modelMyModule;
extern Model* modelSimpleVCO;
extern Model* modelSimpleNoise;
extern Model* modelSimpleMult;
extern Model* modelSimpleSampleAndHold;
extern Model* modelSimpleMixer;
extern Model* modelSimpleVCA;
