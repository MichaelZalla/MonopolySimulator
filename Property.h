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
#include <string>
#include <fstream>
#include "Player.h"

//Forward declaration
class Board;

using namespace std;

class Property {

public:

	//Class constructor
	Property(string name) : name_(name) { }

	//Accessors methods
	string name() { return this->name_; }
	int count() { return this->count_; }
	
	//Mutator methods
	void incrementCount() { this->count_ += 1; }

private:

	string name_;
	int count_;
	
};

#endif

