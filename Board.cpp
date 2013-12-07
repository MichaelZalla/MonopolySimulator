/**
 * @file Board.cpp
 * @author Michael Zalla
 * @date 12-5-2013
 *
 * Contains implementation of the public interface and private methods of
 * the Board class. For details about this class, see 'Board.h'.
 */

//Protected includes
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "lib/Queue.h"
#include "Property.h"

//Header include
#include "Board.h"

/*** Public interface implementation ***/

/**
 * Takes a Property index that may reside outside of the valid index range
 * and returns a valid index. Invali"d indices will be 'wrapped' around
 * into a valid range (supports forward wrapping and backward wrapping).
 * 
 * See http://stackoverflow.com/questions/707370
 *	
 * @param 	n 	A board index
 */
int Board::wrapIndex(int n, int lower_bound, int upper_bound) {
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

//Board class constructor
Board::Board() { }

//Board class destructor
Board::~Board() {
	for(unsigned int i = 0; i < this->board_.size(); i++) {
		delete this->board_.at(i);
	}
}

/**
 * Returns the board_ index of a given Property. Throws an invalid_argument
 * exception if no match is found in the Board.
 *
 * @param 	property 	A reference to a Property object
 */
int Board::indexOf(Property& property) const {
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
Property& Board::propertyAt(int n) const {
	return *(this->board_.at(Board::wrapIndex(n)));
} 	

/**
 * Alternate implementation of propertyAt which allows the user to specify
 * a Property relative to a given Property. The offset value may be either
 * positive or negative.
 *
 * @param 	property A reference to a Property object
 * @param 	offset 	 An offset value
 */
Property& Board::propertyAt(Property& property, int offset) const {
	int index = this->indexOf(property); //May throw an exception
	return *(this->board_.at(Board::wrapIndex(index + offset)));
}

void Board::addProperty(Property& property) {
	//Push a pointer to the referenced Property object
	this->board_.push(&property);
}

/*** Private method implementation ***/

