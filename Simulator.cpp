/**
 * @file Simulator.cpp
 * @author Michael Zalla
 * @date 12-5-2013
 *
 * Contains implementation of the public interface and private methods of
 * the Simulator class. For details about this class, see 'Simulator.h'.
 */

//Protected includes
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

//Class header include
#include "Simulator.h"

//Class dependencies
#include "SimulatorConfig.h"
#include "Board.h"
#include "Player.h"

//Include namespace containing Property and Card action functions
#include "Actions.h"

using namespace std;

/*** Public interface implementation ***/

/**
* Simulator class constructor. Accepts an exisitng SimulatorConfig object
* describing the simulation parameters (how the simulation should be run).
*
* @param 	config 	An existing SimulatorConfig object
*/
Simulator::Simulator(SimulatorConfig config) : config_(config) {
	//Set up the output handle for writing simulation results
	try {
		//Open a new file with a dynamic filename
		this->output_handle_.open(this->getOutputPath().c_str(),
								  ofstream::out | ofstream::trunc);
	} catch(const ofstream::failure &e) {
		throw runtime_error("Exception occured when opening a file for writing.\n\n");
	}
	//Run the simulation
	this->runSimulation();
}

/**
 * Simulator class destructor. Closes the output file handler and
 * deallocates all Player objects on the heap.
 */
Simulator::~Simulator() {
	//Close the output file handler
	this->output_handle_ << "\n";
	this->output_handle_.close();
	//Delete Player objects allocated on the heap
	for(unsigned int i = 0; i < this->players_.size(); i++) {
		delete this->players_[i];
	}
}

/*** Private method implementation ***/

/* Simulation loop. Simulates player turns and outputs simulation results. */
void Simulator::runSimulation() {
	//Populate the Board with Monopoly properties	
	this->board_.addProperty(*(new Property("Go")));
	this->board_.addProperty(*(new Property("Mediterranean Avenue")));
	this->board_.addProperty(*(new Property("Community Chest", Actions::drawCommunityChest)));
	this->board_.addProperty(*(new Property("Baltic Avenue")));
	this->board_.addProperty(*(new Property("Income Tax")));
	this->board_.addProperty(*(new Property("Reading Railroad")));
	this->board_.addProperty(*(new Property("Oriental Avenue")));
	this->board_.addProperty(*(new Property("Chance", Actions::drawChance)));
	this->board_.addProperty(*(new Property("Vermont Avenue")));
	this->board_.addProperty(*(new Property("Connecticut Avenue")));
	this->board_.addProperty(*(new Property("In Jail/Just Visiting")));
	this->board_.addProperty(*(new Property("St. Charles Place")));
	this->board_.addProperty(*(new Property("Electric Company")));
	this->board_.addProperty(*(new Property("States Avenue")));
	this->board_.addProperty(*(new Property("Virginia Avenue")));
	this->board_.addProperty(*(new Property("Pennsylvania Railroad")));
	this->board_.addProperty(*(new Property("St. James Place")));
	this->board_.addProperty(*(new Property("Community Chest", Actions::drawCommunityChest)));
	this->board_.addProperty(*(new Property("Tennessee Avenue")));
	this->board_.addProperty(*(new Property("New York Avenue")));
	this->board_.addProperty(*(new Property("Free Parking")));
	this->board_.addProperty(*(new Property("Kentucky Avenue")));
	this->board_.addProperty(*(new Property("Chance", Actions::drawChance)));
	this->board_.addProperty(*(new Property("Indiana Avenue")));
	this->board_.addProperty(*(new Property("Illinois Avenue")));
	this->board_.addProperty(*(new Property("B. & O. Railroad")));
	this->board_.addProperty(*(new Property("Alantic Avenue")));
	this->board_.addProperty(*(new Property("Ventnor Avenue")));
	this->board_.addProperty(*(new Property("Water Works")));
	this->board_.addProperty(*(new Property("Marvin Gardens")));
	this->board_.addProperty(*(new Property("Go To Jail", Actions::goToJail)));
	this->board_.addProperty(*(new Property("Pacific Avenue")));
	this->board_.addProperty(*(new Property("North Carolina AVenue")));
	this->board_.addProperty(*(new Property("Community Chest", Actions::drawCommunityChest)));
	this->board_.addProperty(*(new Property("Pennsylvania Avenue")));
	this->board_.addProperty(*(new Property("Short Line")));
	this->board_.addProperty(*(new Property("Chance", Actions::drawChance)));
	this->board_.addProperty(*(new Property("Park Place")));
	this->board_.addProperty(*(new Property("Luxury Tax")));
	this->board_.addProperty(*(new Property("Boardwalk")));

	//Generate the Players to act out our simulation
	for(unsigned int i = 0; i < this->config_.playerCount(); i++) {
		//Determine a seed to pass to the Player objects
		int seed = (this->config_.hasSeed()) ? this->config_.seed() : time(NULL);
		//Create a new Player object, passing it a reference to our Board,
		//the seed, and a reference to the output stream
		this->players_.push_back(new Player(i));
	}
	
	//Simulate the game loop for the number of turn (rounds) specified by the user
	for(unsigned int r_index = 0; r_index < this->config_.turnCount(); r_index++) {
		//For each round (turn set) of the simulation
		this->printRoundLabel(r_index);
		for(unsigned int p_index = 0; p_index < this->config_.playerCount(); p_index++) {
			//For each participating Player
			Player& player = *(this->players_[p_index]);
			this->output_handle_ << " Player " << player.getId() << "'s turn ...\n";
			//Recursive 'move' method
			this->simulateTurn(player);
			//Space out turn reports
			this->output_handle_ << "\n";
		}
	}
	
	//Record Property statistics once the simulation completes
	this->printPropertyStatistics();

}

/**
 * Recursive move function. Simulates a Player's dice roll and responds
 * to the resulting roll, depending on the Player's current state. This
 * method is responsible for updating the Player's location, updating 'land'
 * counters for each Property on the Board, tracking the Player's 'jail'
 * state, and responding to events generated by properties and cards. This
 * method also manages the two card decks as well as each Player's hand. 
 *
 * @param 	player 		A reference to a Player object
 * @param 	r_depth 	A recursive depth tracker used to trigger events
 */
void Simulator::simulateTurn(Player& player, int r_depth) {
	
	//Simulate the Player's dice roll
	int die1, die2;
	bool doubles = ((die1 = this->getDiceRoll()) == (die2 = this->getDiceRoll()));
	//Report the dice roll
	this->output_handle_ << " Player " << player.getId() << " rolled ";
	this->output_handle_ << "(" << die1 << ", " << die2 << ")\n";

	/**
	 * Possible roll cases:
	 *
	 * 1. The player is not in jail, and rolls two different numbers - RETURN
	 * 2. The player is not in jail, and rolls doubles - RECURSIVE
	 * 3. The player is not in jail, and rolls doubles for the third time - RETURN
	 * 4. The player is in jail, and rolls doubles - RETURN
	 * 5. The player is in jail, has been in jail for 3 turns - RETURN
	 * 6. The player is in jail, and does not roll doubles - RETURN
	 */
	
	 if(!player.isDetained()) {
	 	/* Case 1 */
	 	if(!doubles) {
	 		this->advancePlayerBy(player, die1 + die2);
	 		return;
	 	} else
	 	/* Case 2 */
	 	if(doubles && r_depth < 2) {
	 		this->advancePlayerBy(player, die1 * 2);
	 		return this->simulateTurn(player, r_depth + 1);
	 	} else
	 	/* Case 3 */
	 	if(r_depth >= 2) {
	 		//The Player has rolled 'doubles' three times in a row. As per Monopoly
	 		//rules, they are sent to jail!
	 		this->output_handle_ << "Player " << player.getId() << " has rolled 'doubles' three times!\n";
	 		this->arrestPlayer(player);
	 		return;
	 	}
	 } else {
	 	/* Cases 4 & 5 */
	 	//What if a player rolls 'doubles' on their fourth try?
	 	if(doubles || player.getTurnsInJail() >= Player::MAXIMUM_JAIL_SENTENCE) {
	 		//Let the Player advance according to their roll
	 		this->releasePlayer(player);
	 		this->advancePlayerBy(player, die1 + die2);
	 	} else {
	 	/* Case 6 */
	 		this->output_handle_ << "Player " << player.getId() << " spends another lonely night in Jail.\n";
	 		player.incrementTurnsInJail();
	 		return;
	 	}
	 }

}

int Simulator::getDiceRoll() { return (rand() % 6) + 1; }

/**
 * When a Player is to move to a specified Property on the Board, this
 * method updates the Player's location while incrementing the 'land'
 * counter for the respective Property.
 *
 * @param 	player 	A reference to a Player object
 * @param 	sum 	The total value of a dice roll
 */
void Simulator::advancePlayerBy(Player& player, int roll) {
	//Determine the Player's destination
	//We'll write it this way so that the location index still 'wraps'
	Property& destination = this->board_.propertyAt(player.getLocation() + roll);
	player.setLocation(this->board_.indexOf(destination));
	//Report the Player's move
	this->output_handle_ << " Player " << player.getId() << " moves to ";
	this->output_handle_ << destination.name() << "\n";
	//Increase the destination Property's counter
	destination.incrementCount();
	//Have the Property respond to the Player if necessary
	destination.respond(this->board_, player, this->output_handle_);
}

/* Moves a Player to the Jail, updating that Player's state */
void Simulator::arrestPlayer(Player& player) {
	player.setLocation(Board::JAIL_LOCATION);
	this->board_.propertyAt(Board::JAIL_LOCATION).incrementCount();
	player.setDetention(true);
	//Report the arrest
	this->output_handle_ << " Player " << player.getId() << " is hauled off to Jail!\n";
}

/* Releases the Player from Jail, updating the Player's state */
void Simulator::releasePlayer(Player& player) {
	//Release the player
	player.setDetention(false);
	//Report the release
	this->output_handle_ << " Player " << player.getId() << " was released from Jail!\n";
}

//Private helper methods

/* Constructs a filepath string based on the current simulation */
string Simulator::getOutputPath() const {
	//Set up a dynamic filepath describing the simulation
	ostringstream output_path;
	output_path << this->config_.playerCount() << 'p';
	output_path << this->config_.turnCount() << 'r';
	if(this->config_.hasSeed()) { output_path << this->config_.seed() << 's'; }
	if(this->config_.isVerbose()) { output_path << 'v'; }
	//Return a string copy of the path
	return string("output/" + output_path.str() + ".out");
}	

/* Outputs a boxed round label for a given round */
void Simulator::printRoundLabel(int n) {
	this->output_handle_ << "|================================|\n";
	this->output_handle_ << "|        Starting Round ";
	this->output_handle_.width(9);
	this->output_handle_ << left << n;
	this->output_handle_ << "|\n";
	this->output_handle_ << "|================================|\n\n";
}

/* Outputs 'landed on' statistics for all Properties on the Board */
void Simulator::printPropertyStatistics() {
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

