#include "plugin.hpp"


struct SimpleVCA : Module {
	enum ParamId {
		GAIN_PARAM,
		LINLOG_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUT_INPUT,
		CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	SimpleVCA() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(GAIN_PARAM, 0.f, 1.f, 0.f, "");
		configParam(LINLOG_PARAM, 0.f, 1.f, 0.f, "");
		configInput(INPUT_INPUT, "");
		configInput(CV_INPUT, "");
		configOutput(OUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
		float in = inputs[INPUT_INPUT].getVoltage();
		// assuming a standard -5V to 5V range
		float cv = inputs[CV_INPUT].getVoltage() / 5.f; // Normalize CV to 0-1 range
		float gain = params[GAIN_PARAM].getValue();
		if (params[LINLOG_PARAM].getValue() == 0) {
			gain = 1.0f - std::pow(1.0f - gain, 2.0f);
		}
		float out = in * gain * cv;
		outputs[OUT_OUTPUT].setVoltage(out);
	}
};


struct SimpleVCAWidget : ModuleWidget {
	SimpleVCAWidget(SimpleVCA* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SimpleVCA.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(4.765, 57.388)), module, SimpleVCA::GAIN_PARAM));
		addParam(createParamCentered<BefacoSwitch>(mm2px(Vec(4.74, 80.169)), module, SimpleVCA::LINLOG_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.149, 23.632)), module, SimpleVCA::INPUT_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.149, 41.045)), module, SimpleVCA::CV_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.149, 105.999)), module, SimpleVCA::OUT_OUTPUT));
	}
};


Model* modelSimpleVCA = createModel<SimpleVCA, SimpleVCAWidget>("SimpleVCA");