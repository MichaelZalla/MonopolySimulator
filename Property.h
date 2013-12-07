/**
 * @file Property.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Describes the public interface and private methods of the Property class. This
 * class is designed to store the state of a single Property in a game of Monopoly.
 * A property has a name and a counter that tracks the numer of times that a player
 * has landed on the property.
 */

#ifndef PROPERTY_H
#define PROPERTY_H

//Protected includes
#include <fstream>
#include <string>
#include "Player.h"

//Forward declaration
class Board;

using namespace std;

class Property {

public:

	typedef void (*ActionFn) (Board& board, Player& player, ofstream& output);

	//Class constructor
	Property(string name, ActionFn action = NULL)
	: name_(name), count_(0), action_(action) { }

	//Accessors methods
	string name() { return this->name_; }
	int count() { return this->count_; }
	
	//Mutator methods
	void incrementCount() { this->count_ += 1; }

	void respond(Board& board, Player& player, ofstream& output) {
		if(this->action_ != NULL) {
			this->action_(board, player, output);
		}
	}

private:

	string name_;
	int count_;
	ActionFn action_;
	
};

#endif

