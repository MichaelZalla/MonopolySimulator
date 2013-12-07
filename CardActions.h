/**
 * @file CardActions.h
 * @author Michael Zalla
 * @date 12-6-2013
 *
 * Describes the action functions needed by the Board class to instantiate
 * each Property object on the Board.
 */

#include <fstream>

//Forward declaration of class dependencies
class Player;

namespace CardActions {
	
	/* Sends the Player to Jail */
	void goToJail(Board& board, Player& player, ofstream& output) {
		player.setLocation(Board::JAIL_LOCATION);
		board.propertyAt(Board::JAIL_LOCATION).incrementCount();
		player.setDetention(true);
		//Report the arrest
		output << "Player " << player.getId() << " is hauled off to Jail!\n";
	}

	/* Generic movement action */
	void advanceToNthProperty(Board& board, Player& player, ofstream& output, int n) {
		player.setLocation(n);
		Property& property = board.propertyAt(n);
		property.incrementCount();
		//Report the move
		output << "Player " << player.getId() << " moves to " << property.name() << "\n";
	}
	
	void advanceToGo(Board& board, Player& player, ofstream& output) {
		advanceToNthProperty(board, player, output, 0);
	}

	void advanceToIllinois(Board& board, Player& player, ofstream& output) {
		advanceToNthProperty(board, player, output, 24);
	}

	void advanceToStCharles(Board& board, Player& player, ofstream& output) {
		advanceToNthProperty(board, player, output, 11);
	}

	void advanceToNearestUtility(Board& board, Player& player, ofstream& output) {	
		int l = player.getLocation();
		if(l > 12 && l < 28) {
			//Move the Player to Water Works
			advanceToNthProperty(board, player, output, 28);
		} else {
			//Move the Player to Electric Company
			advanceToNthProperty(board, player, output, 12);
		}
	}

	void advanceToNearestRailroad(Board& board, Player& player, ofstream& output) {
		int l = player.getLocation();
		if(l > 36 || l < 5) {
			//Move the Player to Reading Railroad
			advanceToNthProperty(board, player, output, 5);
		}
		if(l > 5 && l < 15) {
			//Move the Player to Pennsylvania Railroad
			advanceToNthProperty(board, player, output, 15);
		}
		if(l > 15 && l < 25) {
			//Move the Player to B. & O. Railroad
			advanceToNthProperty(board, player, output, 25);
		}
		if(l > 25 && l < 36) {
			//Move the Player to Short Line
			advanceToNthProperty(board, player, output, 35);
		}
	}

	void advanceToReadingRailroad(Board& board, Player& player, ofstream& output) {
		advanceToNthProperty(board, player, output, 5);
	}

	void advanceToBoardwalk(Board& board, Player& player, ofstream& output) {
		advanceToNthProperty(board, player, output, 39);
	}

	void retreatThreeSpaces(Board& board, Player& player, ofstream& output) {
		Property& current = board.propertyAt(player.getLocation());
		int n = board.indexOf(board.propertyAt(current, -3));
		advanceToNthProperty(board, player, output, n);
	}
	
	void getOutOfJail(Board& board, Player& player, ofstream& output) {
		if(!player.hasGetOutOfJailChance) {
			//Acquire a 'Get out of Jail Free' card from the 'Chance' deck
			player.hasGetOutOfJailChance = true;
		} else {
			//Acquire a 'Get out of Jail Free' card from the 'Community Chest' deck
			player.hasGetOutOfJailCommunityChest = true;
		}
	}

};

