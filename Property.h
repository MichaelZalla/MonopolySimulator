/**
 * @file Property.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Describes the public interface and private methods of the Property class. This
 * class is designed to store the state of a single Property in a game of Monopoly.
 * A property has a numeric id, a name, and a counter that tracks the numer of times
 * that a player has landed on the property.
 */

#ifndef PROPERTY_H
#define PROPERTY_H

//Protected includes
#include <iostream>
#include <string>

//Forward declaration of the Board and Player classes included
class Board;
class Player;

using namespace std;

class Property {

public:

	//Typedef for a Property action function
	typedef Property& (*ActionFn) (Board& board, Player& player);

	//Class constructor
	Property(string name, ActionFn action = NULL)
	: name_(name), action_(action), count_(0) { }

	//Accessors methods
	
	string name() { return this->name_; }
	int count() { return this->count_; }
	
	//Mutator methods
	
	/* Returns a self-reference to allow for method chaining */
	Property& incrementCount() {
		this->count_ += 1;
		return *this;
	}

	/**
	 * Executes the action assigned to the Property at its instantiation.
	 *
	 * @param 	board 	A reference to a Board object
	 * @param 	player 	A reference to a Player object
	 */
	void respond(Board& board, Player& player) {
		if(this->action_ != NULL) {
			this->action_(board, player);
		}
	}

private:

	string name_;
	int count_;
	ActionFn action_;

};

#endif

