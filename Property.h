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

using namespace std;

class Property {

public:

	//typedef void (*responseFn) (Player& player)

	//Class constructor
	Property(string name) : count_(0) {
		this->name_ = name;
	}

	//Accessors methods
	
	/* Returns the Property's name */
	string name() { return this->name_; }
	
	/* Returns the number of times a Player has landed on a Property */
	int count() { return this->count_; }
	
	/* Allows for comparison between two Properties */
	bool is(Property other) {
		return (this->name_ == other.name());
	}

	//Mutator methods
	
	/* Returns a self-reference to allow for method chaining */
	Property& incrementCount() {
		this->count_ += 1;
		return *this;
	}

private:

	string name_;
	int count_;

};

#endif

