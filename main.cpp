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

	//Attempt to instantiate a config object describing how our
	//simulation should run
	Simulator s((SimulatorConfig(argc, argv)));

	return EXIT_SUCCESS;

}