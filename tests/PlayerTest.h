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

	void testIdConstructor() {
		Player p(0);
		TS_ASSERT_EQUALS(p.getId(), 0);
		TS_ASSERT_EQUALS(p.getsLocation(), 0);
		TS_ASSERT(!p.isDetained());
	}

	void testSetLocation() {
		Player p(0);
		p.setLocation(15);
		TS_ASSERT_EQUALS(p.getLocation(), 15);
	}

	void testSetDetention() {
		Player p(0);
		p.setDetention(true);
		TS_ASSERT(p.isDetained());
		TS_ASSERT_EQUALS(p.getTurnsInJail(), 0);
		p.incrementTurnsInJail();
		p.incrementTurnsInJail();
		p.incrementTurnsInJail();
		TS_ASSERT(p.isDetained());
		TS_ASSERT_EQUALS(p.getTurnsInJail(), 3);
	}

};

#endif

