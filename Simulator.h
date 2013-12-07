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

//Protected includes (for arguments and return types)
#include <fstream>
#include <string>
#include <vector>
#include "SimulatorConfig.h"
#include "Board.h"
#include "Player.h"
#include "lib/Queue.h"
#include "Card.h"

class Simulator {

public:
	
	//Simulation class constructor
 	Simulator(SimulatorConfig config);
	//Simulation class destructor
	~Simulator();

	void runSimulation();

private:

	/*** Private member variables ***/

	//Configuration and output
	SimulatorConfig &config_;
	ofstream output_handle_;

	//Internal simulation model
	Board board_;
	vector<Player*> players_;

	Queue<Card> chance_deck_;
	Queue<Card> community_chest_deck_;

	/*** Private method implementation ***/

	void allowOutput(bool allow);
	void clearOutput();

	void populateBoard();
	void populateChanceDeck();
	void populateCommunityChestDeck();

	void simulateTurn(Player& player, int r_depth = 0);
	int getDiceRoll();

	void advancePlayerBy(Player& player, int roll);
	
	void drawChance(Player& player);
	void drawCommunityChest(Player& player);
	void arrestPlayer(Player& player);
	void releasePlayer(Player& player);

	//Helper methods

	string getOutputPath() const;	
	
	void printRoundLabel(int n);
	void printConfigSummary();
	void printPropertyStatistics();

};

#endif
