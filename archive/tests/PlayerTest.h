/**
 * @file PlayerTest.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Contains unit tests for the Monopoly Player class.
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

//Protected includes
#include <iostream>
#include <string>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

//Class header include
#include "../Player.h"

using namespace std;

class PlayerTest : public CxxTest::TestSuite {

public:

	void testDefaultConstructor() {
		Player p;
		TS_ASSERT_EQUALS(p.location(), 0);
		TS_ASSERT(!p.inJail());
	}

	void testMoveTo() {
		Player p;
		p.moveTo(3);
		TS_ASSERT_EQUALS(p.location(), 3);
		p.moveTo(10);
		TS_ASSERT_EQUALS(p.location(), 10);
		TS_ASSERT_THROWS(p.moveTo(-5), invalid_argument);
	}

};

#endif

