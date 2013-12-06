/**
 * @file ChanceDeck.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Contains implementations for the public interface and private methods of the
 * ChanceDeck class. This class is designed to hold a queue of 'Chance' cards
 * from the game Monopoly. Each Card object in the Deck contains a description
 * and a pointer to a 'card action' function.
 */

#ifndef CHANCE_DECK_H
#define CHANCE_DECK_H

#include <iostream>

//Protected includes
//#include "Card.h"
#include "Deck.h"

using namespace std;

class ChanceDeck : public Deck {

public:

	ChanceDeck() {
		
		/* Construct the deck of 'Chance' cards */
		this->addCard(*(new Card("Advance to Go", this->gotoGo)));
/*
		this->addCard(*(new Card("Advance to Illinois Ave.", this->gotoIllinoisAve)));
		this->addCard(*(new Card("Advance to St. Charles Place", this->gotoStCharlesPlace)));
		this->addCard(*(new Card("Advance token to nearest Utility", this->gotoNearestUtility)));
		this->addCard(*(new Card("Advance to nearest Railroad", this->gotoNearestRailroad)));
		this->addCard(*(new Card("Bank pays you divident of $50", this->noAction)));
		this->addCard(*(new Card("Get Out of Jail Free", this->getOutOfJail)));
		this->addCard(*(new Card("Go back 3 spaces", this->backThreeSpaces)));
		this->addCard(*(new Card("Go to Jail", this->gotoJail)));
		this->addCard(*(new Card("Make general repairs on all your property", this->noAction)));
		this->addCard(*(new Card("Pay poor tax of $15", this->noAction)));
		this->addCard(*(new Card("Take a ride on the Reading Railroad", this->gotoReadingRailroad)));
		this->addCard(*(new Card("Advance token to Boardwalk", this->gotoBoardwalk)));
		this->addCard(*(new Card("You have been elected Charirman of the Board", this->noAction)));
		this->addCard(*(new Card("Your building and loan matures", this->noAction)));
		this->addCard(*(new Card("You have won a crossword competition", this->noAction)));
*/		
		//No support for lambda function in C++10 :(
		//this->addCard(*(new Card("Advance to Illinois Ave.", [](Board& board, Player& player) -> void { ChanceDeck::gotoPropertyByIndex(board, player, 14); } )));

	}

private:

};

#endif

