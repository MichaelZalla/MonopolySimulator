/**
 * @file BoardTest.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Contains unit tests for the Monopoly Board class.
 */

#ifndef BOARD_TEST_H
#define BOARD_TEST_H

//Protected includes
#include <iostream>
#include <string>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

//Class dependencies
#include "../Property.h"

//Class header include
#include "../Board.h"

using namespace std;

class BoardTest : public CxxTest::TestSuite {

public:

	void testWrapIndex() {
		TS_ASSERT_EQUALS(Board::wrapIndex(40), 0);
		TS_ASSERT_EQUALS(Board::wrapIndex(41), 1);
		TS_ASSERT_EQUALS(Board::wrapIndex(-1), 39);
		TS_ASSERT_EQUALS(Board::wrapIndex(-2), 38);
		TS_ASSERT_EQUALS(Board::wrapIndex(-40), 0);
	}

	void testPropertyAt() {
		Board b;
		this->populateBoard(b);
		TS_ASSERT_EQUALS(b.propertyAt(0).name(), "Go");
		TS_ASSERT_EQUALS(b.propertyAt(1).name(), "Mediterranean Avenue");
		TS_ASSERT_EQUALS(b.propertyAt(2).name(), "Community Chest");
		TS_ASSERT_EQUALS(b.propertyAt(-1).name(), b.propertyAt(39).name());
		TS_ASSERT_EQUALS(b.propertyAt(-2).name(), b.propertyAt(38).name());
	}

	void testIndexOf() {
		Board b;
		this->populateBoard(b);
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(0)), 0);
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(1)), 1);
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(2)), 2);
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(-1)), 39);
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(-2)), 38);
	}

	void testPropertyAtRelative() {
		Board b;
		this->populateBoard(b);
		Property& first = b.propertyAt(0);
		Property& next = b.propertyAt(1);
		TS_ASSERT_EQUALS(&(b.propertyAt(first, 1)), &(next));
	}

private:

	void populateBoard(Board& b) {
		//Populate the Board with Monopoly properties - MEMORY LEAK!
		b.addProperty(*(new Property("Go")));
		b.addProperty(*(new Property("Mediterranean Avenue")));
		b.addProperty(*(new Property("Community Chest")));
		b.addProperty(*(new Property("Baltic Avenue")));
		b.addProperty(*(new Property("Income Tax")));
		b.addProperty(*(new Property("Reading Railroad")));
		b.addProperty(*(new Property("Oriental Avenue")));
		b.addProperty(*(new Property("Chance")));
		b.addProperty(*(new Property("Vermont Avenue")));
		b.addProperty(*(new Property("Connecticut Avenue")));
		b.addProperty(*(new Property("In Jail/Just Visiting")));
		b.addProperty(*(new Property("St. Charles Place")));
		b.addProperty(*(new Property("Electric Company")));
		b.addProperty(*(new Property("States Avenue")));
		b.addProperty(*(new Property("Virginia Avenue")));
		b.addProperty(*(new Property("Pennsylvania Railroad")));
		b.addProperty(*(new Property("St. James Place")));
		b.addProperty(*(new Property("Community Chest")));
		b.addProperty(*(new Property("Tennessee Avenue")));
		b.addProperty(*(new Property("New York Avenue")));
		b.addProperty(*(new Property("Free Parking")));
		b.addProperty(*(new Property("Kentucky Avenue")));
		b.addProperty(*(new Property("Chance")));
		b.addProperty(*(new Property("Indiana Avenue")));
		b.addProperty(*(new Property("Illinois Avenue")));
		b.addProperty(*(new Property("B. & O. Railroad")));
		b.addProperty(*(new Property("Alantic Avenue")));
		b.addProperty(*(new Property("Ventnor Avenue")));
		b.addProperty(*(new Property("Water Works")));
		b.addProperty(*(new Property("Marvin Gardens")));
		b.addProperty(*(new Property("Go To Jail")));
		b.addProperty(*(new Property("Pacific Avenue")));
		b.addProperty(*(new Property("North Carolina AVenue")));
		b.addProperty(*(new Property("Community Chest")));
		b.addProperty(*(new Property("Pennsylvania Avenue")));
		b.addProperty(*(new Property("Short Line")));
		b.addProperty(*(new Property("Chance")));
		b.addProperty(*(new Property("Park Place")));
		b.addProperty(*(new Property("Luxury Tax")));
		b.addProperty(*(new Property("Boardwalk")));		
	}

};

#endif

