/**
 * Function or method description.
 *
 * @param 	param1 	Description
 * @param 	param2 	Description
 * @param 	param3	Description
 * @return 			Description
 */

#include <stdexcept>
#include <iostream>
#include <string>

//Class dependencies
//#include "Board.h"
//#include "Player.h"
#include "SimulatorConfig.h"
#include "Simulator.h"

using namespace std;

int main(int argc, char *argv[]) {

	//Attempt to instantiate a config object describing how our simulation should run
	/*
	try {
		//Pass in a copy of the command-line arguments provided by the user
		SimulatorConfig config(argc, argv);
		//cout << config.playerCount() << " :: " << config.turnCount() << " :: " << config.seed() << " :: " << config.isVerbose() << "\n\n";
	} catch (const invalid_argument &e) {
		//An error occured trying to create a config; terminate the application
		cout << e.what() << "\n\n";
		return EXIT_FAILURE;
	}
	*/
	Simulator s((SimulatorConfig(argc, argv)));

	return EXIT_SUCCESS;

}