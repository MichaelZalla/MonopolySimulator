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
class Simulator;
class Player;
class Board;

#ifndef CARD_H
#define CARD_H

class Card {

public:

	typedef void (*CardAction) (Simulator& simulator, Player& player);

	//Card class construtor
	Card(string description, CardAction action = NULL)
	: description_(description), action_(action) { }

	//Accessors methods
	string description() { return this->description_; }

	void performAction(Simulator& simulator, Player& player) {
		if(this->action_ != NULL) {
			this->action_(simulator, player);
		}
	}

private:

	string description_;
	CardAction action_;

};

#endif

