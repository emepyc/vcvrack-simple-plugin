# :warning: Learning Repository :warning:

:exclamation: **This repository is for learning purposes only and should not be used in any real application.** :exclamation:

This repository contains a collection of basic VCV Rack 2 modules for learning purposes.

## Modules

- VCA: A Voltage Controlled Amplifier (VCA) module. It takes an input signal and a control voltage (CV), and outputs the input signal multiplied by the gain and the CV. The gain can be adjusted with a parameter, and can be either linear or logarithmic.

- VCO: A Voltage Controlled Oscillator (VCO) module. It generates a sine waveform based on the input control voltage, following the 1 volt per octave standard.

- Noise: A noise generator module. It generates white noise.

- Mult: A multiple module. It replicates the input signal to multiple outputs.

- SampleAndHold: A sample and hold module. It samples the input signal whenever a trigger is received and holds that value until the next trigger.

- Mixer: A mixer module. It mixes multiple input signals into one output signal.

## Building

To build the modules, you will need a C++ compiler and the necessary libraries. The build process is as follows:

1. Clone the repository: `git clone https://github.com/emepyc/Basic.git`
2. Navigate to the repository folder: `cd Basic`
3. Build the modules: `make`

## Usage

To use the modules, you will need a host for them, such as a digital audio workstation that supports the format of these modules.

## Contributing

Contributions are welcome! Please read the contributing guidelines before making a contribution.

## License

This project is licensed under the MIT License - see the LICENSE file for details.