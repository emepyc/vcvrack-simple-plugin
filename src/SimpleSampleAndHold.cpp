#include "plugin.hpp"


struct SimpleSampleAndHold : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		SIGNAL_INPUT,
		CLOCK_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	SimpleSampleAndHold() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(SIGNAL_INPUT, "");
		configInput(CLOCK_INPUT, "");
		configOutput(OUT_OUTPUT, "");
	}

	float lastSample = 0.0f; // Variable to hold the last sampled value
    bool lastTriggerState = false; // State of the trigger

	// Override the ModuleWidget::step() function to implement the module's logic
	void process(const ProcessArgs& args) override {
        bool currentTriggerState = inputs[CLOCK_INPUT].getVoltage() >= 1.0f;

        // Sample the input signal when the trigger goes from low to high
        if (currentTriggerState && !lastTriggerState) {
            lastSample = inputs[SIGNAL_INPUT].getVoltage();
        }

        // Update the last trigger state
        lastTriggerState = currentTriggerState;

        // Output the last sampled value
        outputs[OUT_OUTPUT].setVoltage(lastSample);
	}
};


struct SimpleSampleAndHoldWidget : ModuleWidget {
	SimpleSampleAndHoldWidget(SimpleSampleAndHold* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SimpleSampleAndHold.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.149, 23.632)), module, SimpleSampleAndHold::SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.149, 48.666)), module, SimpleSampleAndHold::CLOCK_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.149, 103.33)), module, SimpleSampleAndHold::OUT_OUTPUT));
	}
};


Model* modelSimpleSampleAndHold = createModel<SimpleSampleAndHold, SimpleSampleAndHoldWidget>("SimpleSampleAndHold");