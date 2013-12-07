/**
 * @file Card.h
 * @author Michael Zalla
 * @date 12-7-2013
 *
 * Describes the protected methods and private methods of the Card class.
 * This class is used to represent a single stateless Card which has a
 * description and an action function.
 */

//Protected includes
#include <string>

//Forward declarations of class dependencies
class Player;
class Board;

#ifndef CARD_H
#define CARD_H

class Card {

public:

	typedef void (*CardAction) (Board& board, Player& player, ofstream& output);

	//Card class construtor
	Card(string description, CardAction action = NULL)
	: description_(description), action_(action) { }

	//Accessors methods
	string description() { return this->description_; }

	void performAction(Board& board, Player& player, ofstream& output) {
		if(this->action_ != NULL) {
			this->action_(board, player, output);
		}
	}

private:

	string description_;
	CardAction action_;

};

#endif

