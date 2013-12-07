/**
 * @file main.cpp
 * @author Michael Zalla
 * @date 12-7-2013
 *
 * Demonstrates the Monopoly simulator class. Excepts two mandatory command-line
 * arguments and supports two additional optional arguments:
 *
 * 		1. The number of players in the simulation  	[REQUIRED]
 * 		2. The number of turns allowed for each player 	[REQUIRED]
 *  	3. The initial random seed  					[OPTIONAL]
 *  	4. Flag for 'verbose mode' 						[OPTIONAL]
 *
 * These arguments are passed into the SimulatorConfig object and used by
 * the Simulator to configure specific simulations.
 */

//Class dependencies
#include "SimulatorConfig.h"
#include "Simulator.h"

using namespace std;

int main(int argc, char *argv[]) {

	//Attempt to instantiate a config object describing how our simulation should run
	Simulator s((SimulatorConfig(argc, argv)));
	s.runSimulation();

	return EXIT_SUCCESS;

}