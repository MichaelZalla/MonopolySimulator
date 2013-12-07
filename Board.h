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

//Protected includes (for arguments and return types)
#include "lib/Queue.h"
#include "Property.h"

class Board {

public:

	static const int BOARD_SIZE = 40;
	static const int JAIL_LOCATION = 10;
	
	static int wrapIndex(int n, int lower_bound = 0, int upper_bound = Board::BOARD_SIZE - 1 );

	Board();
	~Board();

 	//Accessor methods
	int indexOf(Property& property) const;
	Property& propertyAt(int n) const;
	Property& propertyAt(Property& property, int n) const;

	//Mutator methods
	void addProperty(Property& property);

private:

	Queue<Property*> board_;
	
};

#endif

