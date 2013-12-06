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

//Class header include
#include "../Board.h"

using namespace std;

class BoardTest : public CxxTest::TestSuite {

public:

	void testDefaultConstructor() {
		Board b;
		TS_ASSERT_EQUALS(b.propertyAt(0).name(), "Go");
		TS_ASSERT_EQUALS(b.propertyAt(39).name(), "Boardwalk");
	}

	void testIndexOf() {
		Board b;
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(0)), 0);
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(39)), 39);
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(12)), 12);
		TS_ASSERT_EQUALS(b.indexOf(b.propertyAt(39)), 39);
		Property fake_property("Wall Street");
		TS_ASSERT_THROWS(b.indexOf(fake_property), invalid_argument);
	}

	void testPropertyAt() {
		Board b;
		TS_ASSERT_EQUALS(b.propertyAt(8).name(), "Vermont Avenue");
		TS_ASSERT_EQUALS(b.propertyAt(-8).name(), "North Carolina Avenue");
		TS_ASSERT_EQUALS(b.propertyAt(0).name(), b.propertyAt(40).name());
		TS_ASSERT_EQUALS(b.propertyAt(0).name(), b.propertyAt(-40).name());
	}

	void testPropertyAtRelative() {
		Board b;
		Property p_go = b.propertyAt(0);
		Property p_mediterranean_ave = b.propertyAt(1);
		TS_ASSERT( b.propertyAt(p_go, 1).is(p_mediterranean_ave) );
	}

	void testIncrementCount() {
		Board b;
		TS_ASSERT_EQUALS(b.propertyAt(0).count(), 0);
		b.incrementCount(0);
		TS_ASSERT_EQUALS(b.propertyAt(0).count(), 1);
		b.incrementCount(0);
		TS_ASSERT_EQUALS(b.propertyAt(0).count(), 2);
		b.incrementCount(0);
		TS_ASSERT_EQUALS(b.propertyAt(0).count(), 3);
	}

};

#endif

