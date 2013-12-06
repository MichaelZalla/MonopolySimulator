/**
 * @file Card.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Describes the public interface and private methods of the Card class. This
 * class is designed to represent a single Community Chest or Chance card in a
 * game of Monopoly. A card is defined by its text description and associated
 * function pointer.
 */

#ifndef CARD_H
#define CARD_H

//Protected includes
#include <string>

class Card {

public:

	/* Card class constructor */
	Card(string description) : description_(descriptioN) { }

	/* Card class destructor */
	~Card() { }

	//Accessor methods

	string description() { return this->description_; }

	//Mutator methods

private:

	string description_;

};

#endif

