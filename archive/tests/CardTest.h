/**
 * @file CardTest.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Contains unit tests for the Monopoly Card class.
 */

#ifndef CARD_TEST_H
#define CARD_TEST_H

//Protected includes
#include <iostream>
#include <string>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

#include "../Property.h"
#include "../Board.h"
#include "../Player.h"

//Class header include
//#include "../Card.h"

using namespace std;

class CardTest : public CxxTest::TestSuite {

public:

	void testDefaultConstructor() {
		string desc = "I am a Card!";
		//Card c(desc, advanceThree);
		//TS_ASSERT_EQUALS(c.description(), "I am a Card!");
	}

	void testPerformAction() {
		string desc = "Approached by Mormons. Advance three spaces.";
		//Card c(desc, advanceThree);
		//c.performAction(board_, player_);
		//TS_ASSERT_EQUALS(player_.location(), 3);
	}

private:

	Board board_;
	Player player_;

	static void advanceThree(Board& board, Player& player) {
		//Move the Player forward by three Property spaces
		Property current_p = board.propertyAt(player.location());
		Property destination_p = board.propertyAt(current_p, 3);
		int destination = board.indexOf(destination_p);
		player.moveTo(destination);
	}

};

#endif

