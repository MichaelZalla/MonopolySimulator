/**
 * @file Simulator.h
 * @author Michael Zalla
 * @date 12-5-2013
 *
 * Contains implementation of the public interface and private methods of
 * the Simulator class. With the help of several supporting classes, the Simulator
 * is designed to simulate a simplified game of Monopoly using a specified number
 * of players and player-turns. One goal of this class is to help determine, through
 * computational modeling, which properties on a Monopoly board are most likely to
 * be landed on by players. This simplified version of Monopoly supports dice rolls,
 * roll rules (such as 'rolling doubles'), and 'Chance' and 'Community Chest' cards.
 * Players may also find themselves sent to the 'Jail' space, where they must wait
 * until they are released, as per the game's rules of play.
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

//Protected includes
#include <string>
#include <vector>
#include <ctime>

#include <sstream>
#include <fstream>

//Class dependencies
#include "SimulatorConfig.h"
#include "Board.h"
#include "Player.h"

class Simulator {

public:

	/**
	 * Simulator class constructor. Accepts an exisitng SimulatorConfig object
	 * describing the simulation parameters (how the simulation should be run).
	 *
	 * @param 	config 	An existing SimulatorConfig object
	 */
 	Simulator(SimulatorConfig config) : config_(config) {
 		
 		//Set up the output handle for writing simulation results
 		try {
 			//Open a new file with a dynamic filename
 			this->output_handle_.open(this->getOutputPath().c_str(), ofstream::out | ofstream::trunc);
 		} catch(const ofstream::failure &e) {
 			throw runtime_error("Exception occured when opening a file for writing.\n\n");
 		}

 		//Generate the Players to act out our simulation
 		for(unsigned int i = 0; i < this->config_.playerCount(); i++) {
 			//Determine a seed to pass to the Player objects
 			int seed = (this->config_.hasSeed()) ? this->config_.seed() : time(NULL);
 			//Create a new Player object, passing it a reference to our Board,
 			//the seed, and a reference to the output stream
 			this->players_.push_back(new Player(i, this->board_, seed, this->output_handle_));
 		}

 		//Run the simulation
 		this->runSimulation();

	}

	//Simulation class destructor
	~Simulator() {
		//Close the output file handler
		this->output_handle_ << "\n";
		this->output_handle_.close();
		//Delete Player objects allocated on the heap
		for(unsigned int i = 0; i < this->players_.size(); i++) {
			delete this->players_[i];
		}
	}

	/* Accessor methods */

private:

	/*** Private member variables ***/

	//Configuration and output
	SimulatorConfig &config_;
	ofstream output_handle_;

	//Internal simulation model
	Board board_;
	vector<Player*> players_;

	/*** Private method implementation ***/

	/* Simulation loop. Simulates player turns and outputs simulation results. */
	void runSimulation() {
		for(unsigned int r_index = 0; r_index < this->config_.turnCount(); r_index++) {
			//For each round (turn set) of the simulation
			this->printRoundLabel(r_index);
			for(unsigned int p_index = 0; p_index < this->config_.playerCount(); p_index++) {
				//For each participating Player
				Player& p = *(this->players_[p_index]);
				this->output_handle_ << " Player " << p.id() << "'s turn ...\n";
				//Recursive 'move' method
				p.move();
				//Space out the turn events
				this->output_handle_ << "\n";
			}
		}
		//Record Property statistics once the simulation completes
		this->printPropertyStatistics();
	}

	//Helper methods

	/* Constructs a filepath string based on the current simulation */
	string getOutputPath() const {
		//Set up a dynamic filepath describing the simulation
		ostringstream output_path;
		output_path << this->config_.playerCount() << 'p' << this->config_.turnCount() << 'r';
		if(this->config_.hasSeed()) { output_path << this->config_.seed() << 's'; }
		if(this->config_.isVerbose()) { output_path << 'v'; }
		//Return a string copy of the path
		return string("output/" + output_path.str() + ".out");
	}	

	/* Outputs a boxed round label for a given round */
	void printRoundLabel(int n) {
		this->output_handle_ << "|================================|\n";
		this->output_handle_ << "|        Starting Round " << n;
		this->output_handle_.width(9);
		this->output_handle_ << "|\n";
		this->output_handle_ << "|================================|\n\n";
	}

	/* Outputs 'landed on' statistics for all Properties on the Board */
	void printPropertyStatistics() {
		this->output_handle_ << "|================================|\n";
		this->output_handle_ << "|       Property Statistics      |\n";
		this->output_handle_ << "|================================|\n\n";
		for(unsigned int i = 0; i < Board::BOARD_SIZE; i++) {
			Property p = this->board_.propertyAt(i);
			this->output_handle_.width(22);
			this->output_handle_ << left << " " + p.name();
			this->output_handle_.width(11);
			this->output_handle_ << right << p.count() << "\n";
		}
	}

};

#endif
