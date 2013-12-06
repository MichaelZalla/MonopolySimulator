/**
 * @file Deck.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Describes the protected methods and private methods of the Deck class.
 * This class serves as the abstract base class for ChanceDeck and CChestDeck
 * objects. A deck is simply a wrapper for a basic Queue. This base class
 * implements some generalized card action functions for moving players between
 * properties, and to the jail. The queue holds pointers to Cards on the heap.
 */

#ifndef DECK_H
#define DECK_H

#include <iostream>

//Protected includes
#include "lib/Queue.h"
#include "Card.h"

#include "Board.h"
#include "Player.h"

class Deck {

public:

	/* Deck class constructor */
	//No constructor implementation for an (abstract) base class
	//See http://stackoverflow.com/questions/8513408
	//See http://www.parashift.com/c++-faq-lite/virtual-ctors.html
	//See http://stackoverflow.com/questions/4471780

	/* Deck class destructor */
	~Deck() {
		for(unsigned int i = 0; i < this->deck_.size(); i++) {
			//cout << "\nThis should print before segfault\n";
			delete this->deck_.at(i);
		}
	}

	//Accessor methods

	//Mutator methods

	Card drawCard() {
		Card* front_ptr = this->deck_.front();
		this->deck_.pop();
		return *front_ptr;
	}

	void addCard(Card& card) {
		this->deck_.push(&card);
	}

protected:

	/* Action helper functions */
	
	//static void gotoPropertyByIndex(Board& board, Player& player, int n) {
	void gotoPropertyByIndex(Board& board, Player& player, int n) {
		Property destination_p = board.propertyAt(n);
		int destination = board.indexOf(destination_p);
		player.moveTo(destination);
	}
	
	//static void advancePlayerBy(Board& board, Player& player, int n) {
	void advancePlayerBy(Board& board, Player& player, int n) {
		Property current_p = board.propertyAt(player.location());
		Property destination_p = board.propertyAt(current_p, n);
		int destination = board.indexOf(destination_p);
		player.moveTo(destination);
	}

	/* Card-specific action functions */

	//static void noAction(Board& board, Player& player) { /* Do nothing! */ }
	void noAction(Board& board, Player& player) { /* Do nothing! */ }

	void gotoGo(Board& board, Player& player) {
		this->gotoPropertyByIndex(board, player, 0);
	}

	void gotoJail(Board& board, Player& player) {
		//The Player's state will automatically be updated to 'in Jail'
		this->gotoPropertyByIndex(board, player, 10);
	}

	void getOutOfJailFree(Board& board, Player& player) {
		//The player is not moved, but holds the card for later
		player.takeJailCard(*(this));
	}
	
	void gotoNearestUtility(Board& board, Player& player) { }
	void gotoNearestRailroad(Board& board, Player& player) { }
	void gotoIllinoisAve(Board& board, Player& player) { }
	void gotoStCharlesPlace(Board& board, Player& player) { }
	void backThreeSpaces(Board& board, Player& player) { }
	void gotoReadingRailroad(Board& board, Player& player) { }
	void gotoBoardwalk(Board& board, Player& player) { }

private:
	
	Queue<Card*> deck_;

};

#endif

