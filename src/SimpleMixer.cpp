#include "plugin.hpp"


struct SimpleMixer : Module {
	enum ParamId {
		GAIN_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUT1_INPUT,
		INPUT2_INPUT,
		INPUT3_INPUT,
		INPUT4_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	SimpleMixer() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(INPUT1_INPUT, "");
		configInput(INPUT2_INPUT, "");
		configInput(INPUT3_INPUT, "");
		configInput(INPUT4_INPUT, "");
		configParam(GAIN_PARAM, 0.f, 4.f, 0.f, "");
		configOutput(OUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
		float out = 0.0f;
		out += inputs[INPUT1_INPUT].getVoltage();
		out += inputs[INPUT2_INPUT].getVoltage();
		out += inputs[INPUT3_INPUT].getVoltage();
		out += inputs[INPUT4_INPUT].getVoltage();
		out *= params[GAIN_PARAM].getValue();
		outputs[OUT_OUTPUT].setVoltage(out * 0.25f);
	}
};


struct SimpleMixerWidget : ModuleWidget {
	SimpleMixerWidget(SimpleMixer* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SimpleMixer.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.149, 23.632)), module, SimpleMixer::INPUT1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.149, 41.045)), module, SimpleMixer::INPUT2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.004, 57.498)), module, SimpleMixer::INPUT3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.095, 75.225)), module, SimpleMixer::INPUT4_INPUT));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(5.004, 92.255)), module, SimpleMixer::GAIN_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.149, 112.67)), module, SimpleMixer::OUT_OUTPUT));
	}
};


Model* modelSimpleMixer = createModel<SimpleMixer, SimpleMixerWidget>("SimpleMixer");