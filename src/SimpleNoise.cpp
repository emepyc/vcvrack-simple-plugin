#include "plugin.hpp"


struct SimpleNoise : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		INPUTS_LEN
	};
	enum OutputId {
		NOISE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	std::random_device rd;  // Non-deterministic random number generator
	std::mt19937 gen;       // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> dis; // Uniform distribution

	SimpleNoise() : gen(rd()), dis(-1.0f, 1.0f) {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configOutput(NOISE_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
		float noise = dis(gen); // Generate a random number between -1.0 and 1.0

		// Assuming you have an output port for the noise, for example OUTPUT_NOISE
		outputs[NOISE_OUTPUT].setVoltage(5.0f * noise); // Scale the noise and output it
	}
};


struct SimpleNoiseWidget : ModuleWidget {
	SimpleNoiseWidget(SimpleNoise* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SimpleNoise.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.08, 102.913)), module, SimpleNoise::NOISE_OUTPUT));
	}
};


Model* modelSimpleNoise = createModel<SimpleNoise, SimpleNoiseWidget>("SimpleNoise");
