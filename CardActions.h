/**
 * @file CardActions.h
 * @author Michael Zalla
 * @date 12-6-2013
 *
 * Describes the action functions needed by the Board class to instantiate
 * each Property object on the Board.
 */

//Forward declaration of class dependencies
class Simulator;
class Board;
class Player;

namespace CardActions {
	
	/* Sends the Player to Jail */
	void goToJail(Simulator& simulator, Player& player) {
		simulator.arrestPlayer(player);
	}

	/* Generic movement action */
	void advanceToNthProperty(Simulator& simulator, Player& player, int n) {
		simulator.advancePlayerTo(player, n);
	}
	
	void advanceToGo(Simulator& simulator, Player& player) {
		advanceToNthProperty(simulator, player, 0);
	}

	void advanceToIllinois(Simulator& simulator, Player& player) {
		advanceToNthProperty(simulator, player, 24);
	}

	void advanceToStCharles(Simulator& simulator, Player& player) {
		advanceToNthProperty(simulator, player, 11);
	}

	void advanceToNearestUtility(Simulator& simulator, Player& player) {	
		int l = player.getLocation();
		if(l > 12 && l < 28) {
			//Move the Player to Water Works
			advanceToNthProperty(simulator, player, 28);
		} else {
			//Move the Player to Electric Company
			advanceToNthProperty(simulator, player, 12);
		}
	}

	void advanceToNearestRailroad(Simulator& simulator, Player& player) {
		int l = player.getLocation();
		if(l > 35 || l < 5) {
			//Move the Player to Reading Railroad
			advanceToNthProperty(simulator, player, 5);
		}
		if(l > 5 && l < 15) {
			//Move the Player to Pennsylvania Railroad
			advanceToNthProperty(simulator, player, 15);
		}
		if(l > 15 && l < 25) {
			//Move the Player to B. & O. Railroad
			advanceToNthProperty(simulator, player, 25);
		}
		if(l > 25 && l < 35) {
			//Move the Player to Short Line
			advanceToNthProperty(simulator, player, 35);
		}
	}

	void advanceToReadingRailroad(Simulator& simulator, Player& player) {
		advanceToNthProperty(simulator, player, 5);
	}

	void advanceToBoardwalk(Simulator& simulator, Player& player) {
		advanceToNthProperty(simulator, player, 39);
	}

	void retreatThreeSpaces(Simulator& simulator, Player& player) {
		int current = player.getLocation();
		advanceToNthProperty(simulator, player, Board::wrapIndex(current - 3));
	}
	
	void getOutOfJail(Simulator& simulator, Player& player) {
		if(!player.hasGetOutOfJailChance) {
			//Acquire a 'Get out of Jail Free' card from the 'Chance' deck
			player.hasGetOutOfJailChance = true;
		} else {
			//Acquire a 'Get out of Jail Free' card from the 'Community Chest' deck
			player.hasGetOutOfJailCommunityChest = true;
		}
	}

};

