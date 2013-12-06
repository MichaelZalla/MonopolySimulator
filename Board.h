/**
 * @file Board.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Describes the public interface and private methods of the Monopoly Board class.
 * This class is designed to hold a series of Properties present on a classic, pre-
 * 2008 Monopoly board. Each Property stores a name, a counter for the number of times
 * that the property has been landed on, and an action (response) to fire each time
 * that a player lands on the Property.
 */

#ifndef BOARD_H
#define BOARD_H

//Protected includes
//#include "lib/List.h";
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "lib/Queue.h"
#include "Property.h"

//Forward declaration of Player class included in "Simulator.h"
class Player;

//Includes the namespace where our Property actions are defined
#include "Actions.h";

class Board {

public:

	static const int BOARD_SIZE = 40;
	static const int JAIL_LOCATION = 10;

	/*** Public interface implementation ***/

	//Board class constructor
	Board() {

		vector<string> property_names;
		property_names.push_back("Go");
		property_names.push_back("Mediterranean Avenue");
		property_names.push_back("Community Chest");
		property_names.push_back("Baltic Avenue");
		property_names.push_back("Income Tax");
		property_names.push_back("Reading Railroad");
		property_names.push_back("Oriental Avenue");
		property_names.push_back("Chance");
		property_names.push_back("Vermont Avenue");
		property_names.push_back("Connecticut Avenue");
		property_names.push_back("In Jail/Just Visiting");
		property_names.push_back("St. Charles Place");
		property_names.push_back("Electric Company");
		property_names.push_back("States Avenue");
		property_names.push_back("Virginia Avenue");
		property_names.push_back("Pennsylvania Railroad");
		property_names.push_back("St. James Place");
		property_names.push_back("Community Chest");
		property_names.push_back("Tennessee Avenue");
		property_names.push_back("New York Avenue");
		property_names.push_back("Free Parking");
		property_names.push_back("Kentucky Avenue");
		property_names.push_back("Chance");
		property_names.push_back("Indiana Avenue");
		property_names.push_back("Illinois Avenue");
		property_names.push_back("B. & O. Railroad");
		property_names.push_back("Alantic Avenue");
		property_names.push_back("Ventnor Avenue");
		property_names.push_back("Water Works");
		property_names.push_back("Marvin Gardens");
		property_names.push_back("Go To Jail");
		property_names.push_back("Pacific Avenue");
		property_names.push_back("North Carolina Avenue");
		property_names.push_back("Community Chest");
		property_names.push_back("Pennsylvania Avenue");
		property_names.push_back("Short Line");
		property_names.push_back("Chance");
		property_names.push_back("Park Place");
		property_names.push_back("Luxury Tax");
		property_names.push_back("Boardwalk");
		
		//Construct the Properties list in dynamic memory
		for(unsigned int i = 0; i < BOARD_SIZE; i++) {
			Property* p_ptr = new Property(property_names[i]);
			this->board_.push(p_ptr);
		}
		
	}
	
	//Board class destructor
	~Board() {
		for(unsigned int i = 0; i < this->board_.size(); i++) {
			delete this->board_.at(i);
		}
	}

 	//Accessor methods

	/**
	 * Returns the board_ index of a given Property. Throws an invalid_argument
	 * exception if no match is found in the Board.
	 *
	 * @param 	property 	A reference to a Property object
	 */
	int indexOf(Property& property) const {
		for(unsigned int i = 0; i < this->board_.size(); i++) {
			//Because certain properties can hold the same name (e.g. - "Chance"),
			//and we aren't giving each Property a unique id property, we'll just
			//test for identity (location in memory)
			if(&property == this->board_.at(i)) {
				return i;
			}
		}
		throw invalid_argument("This Property does no exist on the Board!");
	}

	/**
	 * Returns a reference to the Property object that corresponds with a
	 * give index. Supports 'wrapping' of all out-of-bounds indices, including
	 * negative indices.
	 *
	 * @param 	n 	A Property index
	 */
	Property& propertyAt(int n) const {
		return *(this->board_.at(this->wrapIndex(n)));
	} 	

	/**
	 * Alternate implementation of propertyAt which allows the user to specify
	 * a Property relative to a given Property. The offset value may be either
	 * positive or negative.
	 *
	 * @param 	property A reference to a Property object
	 * @param 	offset 	 An offset value
	 */
 	Property& propertyAt(Property& property, int offset) const {
 		int index = this->indexOf(property); //May throw an exception
 		return *(this->board_.at(this->wrapIndex(index + offset)));
	}

 	//Mutator methods

private:

	Queue<Property*> board_;

	/*** Private method implementation ***/

	/**
	 * Takes a Property index that may reside outside of the valid index range
	 * and returns a valid index. Invali"d indices will be 'wrapped' around
	 * into a valid range (supports forward wrapping and backward wrapping).
	 * 
 	 * See http://stackoverflow.com/questions/707370
 	 *	
	 * @param 	n 	A board index
	 */
 	int wrapIndex(int n, int lower_bound = 0, int upper_bound = BOARD_SIZE - 1) const {
 		//return n % this->BOARD_SIZE; //WILL NOT WORK in C++!
 		int range_size = upper_bound - lower_bound + 1; //40, by default
 		if(n < lower_bound) {
 			//If the provided index falls below the lower_bound, bump it forward by
 			//range_size until it falls within the valid range
 			int lower_delta = lower_bound - n;
 			//Integer division (if the index is between (lower_bound - lower_bound,
 			//lower_bound], it will return zero. That's why we add 1 afterward
 			int ranges_between = lower_delta / range_size + 1;
 			n += range_size * ranges_between;
 		}
 		return lower_bound + (n - lower_bound) % range_size;
	}

};

#endif

