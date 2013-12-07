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
#include <stdexcept>

#include <iostream>

//Class header include
#include "Simulator.h"

//Class dependencies
#include "SimulatorConfig.h"
#include "Board.h"
#include "Player.h"
#include "lib/Queue.h"
#include "Card.h"

//Include namespace containing Property and Card action functions
#include "CardActions.h"

using namespace std;

/*** Public interface implementation ***/

/**
* Simulator class constructor. Accepts an exisitng SimulatorConfig object
* describing the simulation parameters (how the simulation should be run).
*
* @param 	config 	An existing SimulatorConfig object
*/
Simulator::Simulator(SimulatorConfig config) : config_(config) {
	//Seed the random number generator, if a seed was specified
	if(this->config_.hasSeed()) {
		srand(this->config_.seed());
	}
	//Clear the contents of the output file, if it exists
	this->clearOutput();
	//Print config summary
	this->printConfigSummary();
	//Conditional output until reporting of Property statistics
	this->allowOutput(this->config_.isVerbose());
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

/* Simulation loop. Simulates player turns and outputs simulation results. */
void Simulator::runSimulation() {
	
	this->populateBoard();
	this->populateChanceDeck();
	this->populateCommunityChestDeck();

	//Generate the Players to act out our simulation
	for(unsigned int i = 0; i < this->config_.playerCount(); i++) {
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
			//State where the player currently resides
			this->output_handle_ << "Player " << player.getId() << " starting on ";
			string current = this->board_.propertyAt(player.getLocation()).name();
			this->output_handle_ << current << "\n";
			//Recursive 'move' method
			this->simulateTurn(player);
		}
	}
	
	//Record Property statistics once the simulation completes
	this->printPropertyStatistics();

}

/*** Private method implementation ***/

/* Toggles program output. Redirects unwanted output to /dev/null */
void Simulator::allowOutput(bool allow) {
	if(this->output_handle_.is_open()) {
		this->output_handle_.close();
	}
	if(!allow) {
		this->output_handle_.open("/dev/null");
	} else {
		try {
			this->output_handle_.open(this->getOutputPath().c_str(),
									  ofstream::out | ofstream::app);
		} catch(const ofstream::failure &e) {
			throw runtime_error("Exception occured when opening a file for writing.\n\n");
		}
	}
}

/* Clears the text contents of the output file */
void Simulator::clearOutput() {
	if(this->output_handle_.is_open()) {
		this->output_handle_.close();
	}
	try {
		this->output_handle_.open(this->getOutputPath().c_str(),
								  ofstream::out | ofstream::trunc);
	} catch(const ofstream::failure &e) {
		throw runtime_error("Exception occured when opening a file for writing.\n\n");
	}
}

void Simulator::populateBoard() {
	//Populate the Board with Monopoly properties	
	this->board_.addProperty(*(new Property("Go")));
	this->board_.addProperty(*(new Property("Mediterranean Avenue")));
	this->board_.addProperty(*(new Property("Community Chest")));
	this->board_.addProperty(*(new Property("Baltic Avenue")));
	this->board_.addProperty(*(new Property("Income Tax")));
	this->board_.addProperty(*(new Property("Reading Railroad")));
	this->board_.addProperty(*(new Property("Oriental Avenue")));
	this->board_.addProperty(*(new Property("Chance")));
	this->board_.addProperty(*(new Property("Vermont Avenue")));
	this->board_.addProperty(*(new Property("Connecticut Avenue")));
	this->board_.addProperty(*(new Property("In Jail/Just Visiting")));
	this->board_.addProperty(*(new Property("St. Charles Place")));
	this->board_.addProperty(*(new Property("Electric Company")));
	this->board_.addProperty(*(new Property("States Avenue")));
	this->board_.addProperty(*(new Property("Virginia Avenue")));
	this->board_.addProperty(*(new Property("Pennsylvania Railroad")));
	this->board_.addProperty(*(new Property("St. James Place")));
	this->board_.addProperty(*(new Property("Community Chest")));
	this->board_.addProperty(*(new Property("Tennessee Avenue")));
	this->board_.addProperty(*(new Property("New York Avenue")));
	this->board_.addProperty(*(new Property("Free Parking")));
	this->board_.addProperty(*(new Property("Kentucky Avenue")));
	this->board_.addProperty(*(new Property("Chance")));
	this->board_.addProperty(*(new Property("Indiana Avenue")));
	this->board_.addProperty(*(new Property("Illinois Avenue")));
	this->board_.addProperty(*(new Property("B. & O. Railroad")));
	this->board_.addProperty(*(new Property("Alantic Avenue")));
	this->board_.addProperty(*(new Property("Ventnor Avenue")));
	this->board_.addProperty(*(new Property("Water Works")));
	this->board_.addProperty(*(new Property("Marvin Gardens")));
	this->board_.addProperty(*(new Property("Go To Jail")));
	this->board_.addProperty(*(new Property("Pacific Avenue")));
	this->board_.addProperty(*(new Property("North Carolina AVenue")));
	this->board_.addProperty(*(new Property("Community Chest")));
	this->board_.addProperty(*(new Property("Pennsylvania Avenue")));
	this->board_.addProperty(*(new Property("Short Line")));
	this->board_.addProperty(*(new Property("Chance")));
	this->board_.addProperty(*(new Property("Park Place")));
	this->board_.addProperty(*(new Property("Luxury Tax")));
	this->board_.addProperty(*(new Property("Boardwalk")));
}

void Simulator::populateChanceDeck() {
	this->chance_deck_.push(*(new Card("Advance to Go",
										CardActions::advanceToGo)));
	this->chance_deck_.push(*(new Card("Advance to Illinois Ave.",
										CardActions::advanceToIllinois)));
	this->chance_deck_.push(*(new Card("Advance to St. Charles Place",
										CardActions::advanceToStCharles)));
	this->chance_deck_.push(*(new Card("Advance token to nearest Utility",
										CardActions::advanceToNearestUtility)));
	this->chance_deck_.push(*(new Card("Advance to nearest Railroad",
										CardActions::advanceToNearestRailroad)));
	this->chance_deck_.push(*(new Card("Bank pays you divident of $50")));
	this->chance_deck_.push(*(new Card("Get Out of Jail Free")));
	this->chance_deck_.push(*(new Card("Go back 3 spaces",
										CardActions::retreatThreeSpaces)));
	this->chance_deck_.push(*(new Card("Go to Jail",
										CardActions::goToJail)));
	this->chance_deck_.push(*(new Card("Make general repairs on all your property")));
	this->chance_deck_.push(*(new Card("Pay poor tax of $15")));
	this->chance_deck_.push(*(new Card("Take a ride on the Reading Railroad",
										CardActions::advanceToReadingRailroad)));
	this->chance_deck_.push(*(new Card("Advance token to Boardwalk",
										CardActions::advanceToBoardwalk)));
	this->chance_deck_.push(*(new Card("You have been elected Charirman of the Board")));
	this->chance_deck_.push(*(new Card("Your building and loan matures")));
	this->chance_deck_.push(*(new Card("You have won a crossword competition")));
}

void Simulator::populateCommunityChestDeck() {
	this->community_chest_deck_.push(*(new Card("Advance to Go",
												CardActions::advanceToGo)));
	this->community_chest_deck_.push(*(new Card("Bank error in your favor")));
	this->community_chest_deck_.push(*(new Card("Doctor's fees")));
	this->community_chest_deck_.push(*(new Card("From sale of stock you get $50")));
	this->community_chest_deck_.push(*(new Card("Get Out of Jail Free")));
	this->community_chest_deck_.push(*(new Card("Go to Jail",
												CardActions::goToJail)));
	this->community_chest_deck_.push(*(new Card("Grand Opera opening")));
	this->community_chest_deck_.push(*(new Card("Xmas fund matures")));
	this->community_chest_deck_.push(*(new Card("Income tax refund")));
	this->community_chest_deck_.push(*(new Card("It is your birthday")));
	this->community_chest_deck_.push(*(new Card("Life insurance matures")));
	this->community_chest_deck_.push(*(new Card("Pay hospital fees of $100")));
	this->community_chest_deck_.push(*(new Card("Pay school fees of $150")));
	this->community_chest_deck_.push(*(new Card("Receive for Services $25")));
	this->community_chest_deck_.push(*(new Card("You are assessed for street repairs")));
	this->community_chest_deck_.push(*(new Card("You have won second prize in a beauty contest")));
	this->community_chest_deck_.push(*(new Card("You inherit $100")));
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
	
	//Check whether the Player is in Jail and may use a Get Out of Jail Free card
	if(player.isDetained()) {
		if(player.hasGetOutOfJailChance) {
 			//'Remove' the card from the Player's hand, and 'return' it to the deck
 			player.hasGetOutOfJailChance = false;
 			player.setDetention(false);
 			this->chance_deck_.push(*(new Card("Get Out of Jail Free")));
 			this->output_handle_ << "Player " << player.getId() << " uses his ";
 			this->output_handle_ << "'Get Out of Jail Free' card to leave Jail.\n";
 		} else
 		if(player.hasGetOutOfJailCommunityChest) {
 			//'Remove' the card from the Player's hand, and 'return' it to the deck
 			player.hasGetOutOfJailCommunityChest = false;
 			player.setDetention(false);
 			this->community_chest_deck_.push(*(new Card("Get Out of Jail Free")));
  			this->output_handle_ << "Player " << player.getId() << " uses his ";
 			this->output_handle_ << "'Get Out of Jail Free' card to leave Jail.\n";
 		}
	}

	//Simulate the Player's dice roll
	int die1, die2;
	bool doubles = ((die1 = this->getDiceRoll()) == (die2 = this->getDiceRoll()));
	//Report the dice roll
	this->output_handle_ << "Player " << player.getId() << " rolls " << die1 << "+" << die2 << "\n";

	/**
	 * Possible roll cases:
	 *
	 * 1. The player is not in jail, and rolls two different numbers - RETURN
	 * 2. The player is not in jail, and rolls doubles - RECURSIVE
	 *      - Must check that the Player didn't land in Jail after the first roll!
	 * 3. The player is not in jail, and rolls doubles for the third time - RETURN
	 * 4. The player is in jail, and rolls doubles - RECURSIVE
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
	 		//We must check again for Player::isDetained ... If they landed on
	 		//'Go To Jail', then this value will have changed, and landing in Jail
	 		//loses you your right to re-roll on doubles!
	 		if(!player.isDetained()) {
	 			return this->simulateTurn(player, r_depth + 1);
	 		} else {
				return;	 			
	 		}
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
	 	/* Cases 4 */
	 	if(doubles) {
			//Let the Player advance according to their roll
	 		this->releasePlayer(player);
	 		this->advancePlayerBy(player, die1 + die2);
	 		return this->simulateTurn(player, r_depth + 1);
	 	} else
	 	/* Case 5 */
	 	if(player.getTurnsInJail() >= Player::MAXIMUM_JAIL_SENTENCE) {
			//Let the Player advance according to their roll
	 		this->releasePlayer(player);
	 		this->advancePlayerBy(player, die1 + die2);
	 		return;
	 	} else {
	 	/* Case 6 */
	 		this->output_handle_ << " -> Player " << player.getId() << " spends another lonely night in Jail.\n";
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
	this->output_handle_ << "Player " << player.getId() << " landed on ";
	this->output_handle_ << destination.name() << "\n";
	//Increase the destination Property's counter
	destination.incrementCount();
	//Have the Property respond to the Player if necessary
	if(destination.name() == "Go To Jail") {
		this->arrestPlayer(player);
	} else
	if(destination.name() == "Chance") {
		this->drawChance(player);
	} else
	if(destination.name() == "Community Chest") {
		this->drawCommunityChest(player);
	}
}

/* Draws a Chance card and follows its description */
void Simulator::drawChance(Player& player) {
	//Copy the card from the front of the Chance deck and remove
	//the original from the deck
	Card card = this->chance_deck_.front();
	this->chance_deck_.pop();
	//Report the resulting card
	this->output_handle_ << " -> Chance - " << card.description() << "\n";
	//Determine whether this is a 'Get out of Jail Free' card
	if(card.description() == "Get Out of Jail Free") {
		//Set the appropriate flag for the Player
		player.hasGetOutOfJailChance = true;
	} else {
		//Follow the action labeled on the card
		card.performAction(this->board_, player, this->output_handle_);
		//Return the card to the back of the deck
		this->chance_deck_.push(card);
	}
}

/* Draws a Community Chest card and follows its description */
void Simulator::drawCommunityChest(Player& player) {
	//Copy the card from the front of the Community Chest deck and
	//remove the original from the deck
	Card card = this->community_chest_deck_.front();
	this->community_chest_deck_.pop();
	//Report the resulting card
	this->output_handle_ << "Player " << player.getId() << " drew a ";
	this->output_handle_ << "'" << card.description() << "'\n";
	//Determine whether this is a 'Get out of Jail Free' card
	if(card.description() == "Get Out of Jail Free") {
		//Set the appropriate flag for the Player
		player.hasGetOutOfJailCommunityChest = true;
	} else {
		//Follow the action labeled on the card
		card.performAction(this->board_, player, this->output_handle_);
		//Return the card to the back of the deck
		this->community_chest_deck_.push(card);
	}
}

/* Moves a Player to the Jail, updating that Player's state */
void Simulator::arrestPlayer(Player& player) {
	player.setLocation(Board::JAIL_LOCATION);
	this->board_.propertyAt(Board::JAIL_LOCATION).incrementCount();
	player.setDetention(true);
	//Report the arrest
	this->output_handle_ << " -> Player " << player.getId() << " is hauled off to Jail!\n";
}

/* Releases the Player from Jail, updating the Player's state */
void Simulator::releasePlayer(Player& player) {
	//Release the player
	player.setDetention(false);
	//Report the release
	this->output_handle_ << " -> Player " << player.getId() << " was released from Jail!\n";
}

//Private helper methods

/* Constructs a filepath string based on the current simulation */
string Simulator::getOutputPath() const {
	//Set up a dynamic filepath describing the simulation
	ostringstream output_path;
	output_path << this->config_.playerCount() << 'p';
	output_path << this->config_.turnCount() << 'r';
	if(this->config_.hasSeed()) { output_path << this->config_.seed() << 's'; }
	else { output_path << 'Rand';}
	if(this->config_.isVerbose()) { output_path << 'v'; }
	//Return a string copy of the path
	return string("output/" + output_path.str() + ".out");
}	

/* Outputs a boxed round label for a given round */
void Simulator::printRoundLabel(int n) {
	this->output_handle_ << "++++++++++++++++++++\n";
	this->output_handle_ << "Starting round " << (n + 1) << "\n";
	/*
	this->output_handle_ << "|================================|\n";
	this->output_handle_ << "|        Starting Round ";
	this->output_handle_.width(9);
	this->output_handle_ << left << n;
	this->output_handle_ << "|\n";
	this->output_handle_ << "|================================|\n\n";
	*/
}

/* Outputs starting configuration/settings */
void Simulator::printConfigSummary() {
	this->allowOutput(true);
	this->output_handle_ << "Num Players: " << this->config_.playerCount() << " ";
	this->output_handle_ << "Turns: " << this->config_.turnCount() << "\n";
	this->output_handle_ << "Verbose: " << this->config_.isVerbose() << "\n";
}

/* Outputs 'landed on' statistics for all Properties on the Board */
void Simulator::printPropertyStatistics() {
	this->allowOutput(true);
	this->output_handle_ << "\n";
	/*
	this->output_handle_ << "|================================|\n";
	this->output_handle_ << "|       Property Statistics      |\n";
	this->output_handle_ << "|================================|\n\n";
	*/
	for(unsigned int i = 0; i < Board::BOARD_SIZE; i++) {
		Property p = this->board_.propertyAt(i);
		/*
		this->output_handle_.width(22);
		this->output_handle_ << left << " " + p.name();
		this->output_handle_.width(11);
		this->output_handle_ << right << p.count() << "\n";
		*/
		this->output_handle_ << p.name() << " :: " << p.count() << "\n";
	}
}

