/**
 * @file SimulatorConfig.h
 * @author Michael Zalla
 * @date 12-5-2013
 *
 * Implements the SimulationConfig class which accepts the Monopoly Simulation
 * program's command-line arguments and provides constant config information to
 * the Simulation object. The Simulator class will require 2 settings, but support
 * up to four:
 *
 * 		1. The number of players in the simulation  	[REQUIRED]
 * 		2. The number of turns allowed for each player 	[REQUIRED]
 *  	3. The initial random seed  					[OPTIONAL]
 *  	4. Flag for 'verbose mode' 						[OPTIONAL]
 */

#ifndef SIMULATOR_CONFIG_H
#define SIMULATOR_CONFIG_H

//Protected includes
#include <cstdlib>
#include <stdexcept>
#include <string>
//#include "unistd.h"

using namespace std;

class SimulatorConfig {
	
public:

	/**
	 * SimulatorConfig constructor. Accepts command-line argument information
	 * provided by the user of the class.
	 *
	 * @param 	argc 	The number of arguments passed to the program
	 * @param 	argv 	A pointer to an array of character pointers (strings)
	 */
	SimulatorConfig(int argc, char *argv[]) : has_seed_(false) {
		if(argc < 3 || argc > 5) {
			throw invalid_argument("Invalid number of command-line arguments!");
		} else {
			int pc = atoi(argv[1]);
			/*
			if(pc < 2 || pc > 6) {
				throw invalid_argument("Invalid number of players. Only 2—6 players may play!");
			}
			*/
			this->player_count_ = atoi(argv[1]);
			this->turn_count_ = atoi(argv[2]);
			if(argc > 3) {
				//Was a seed specified
				this->has_seed_ = true;
				this->seed_ = atoi(argv[3]);
				if(argc > 4) {
					//Was 'verbose' mode specified?
					string flag = argv[4];
					this->verbose_ = (flag == "-v") ? true : false;
				}
			}
		}
	}

	/* Accessors methods */

	int playerCount() const { return this->player_count_; }
	
	int turnCount() const { return this->turn_count_; }
	
	bool hasSeed() const { return this->has_seed_; }
	int seed() const {
		if(!this->has_seed_) {
			throw runtime_error("Seed was not provided in the config object!");
		}
		return this->seed_;
	}
	
	bool isVerbose() const { return this->verbose_; }

private:

	int player_count_;
	int turn_count_;
	bool has_seed_;
	int seed_;
	bool verbose_;

};

#endif