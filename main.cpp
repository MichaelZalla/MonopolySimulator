#include <string>
#include <stdexcept>

#include <iostream>

//Class dependencies
#include "SimulatorConfig.h"
#include "Simulator.h"

using namespace std;

int main(int argc, char *argv[]) {

	//Attempt to instantiate a config object describing how our simulation should run
	Simulator s((SimulatorConfig(argc, argv)));

	return EXIT_SUCCESS;

}