#include "plugin.hpp"


struct SimpleMult : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	SimpleMult() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(IN_INPUT, "");
		configOutput(OUT1_OUTPUT, "");
		configOutput(OUT2_OUTPUT, "");
		configOutput(OUT3_OUTPUT, "");
		configOutput(OUT3_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
		float inputSignal = inputs[IN_INPUT].getVoltage();
		getOutput(OUT1_OUTPUT).setVoltage(inputSignal);
		getOutput(OUT2_OUTPUT).setVoltage(inputSignal);
		getOutput(OUT3_OUTPUT).setVoltage(inputSignal);
		getOutput(OUT4_OUTPUT).setVoltage(inputSignal);
	}
};


struct SimpleMultWidget : ModuleWidget {
	SimpleMultWidget(SimpleMult* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SimpleMult.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.149, 23.632)), module, SimpleMult::IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.149, 48.666)), module, SimpleMult::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.149, 70.256)), module, SimpleMult::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.149, 90.536)), module, SimpleMult::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.269, 111.476)), module, SimpleMult::OUT4_OUTPUT));
	}
};


Model* modelSimpleMult = createModel<SimpleMult, SimpleMultWidget>("SimpleMult");
