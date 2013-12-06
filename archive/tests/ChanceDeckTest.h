/**
 * @file ChanceDeckTest.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Contains unit tests for the Monopoly ChanceDeck class.
 */

#ifndef CHANCE_DECK_TEST_H
#define CHANCE_DECK_TEST_H

//Protected includes
#include <iostream>
#include <string>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

#include "../Board.h"
#include "../Player.h"

#include "../Card.h"

//Class header include
#include "../ChanceDeck.h"

using namespace std;

class ChanceDeckTest : public CxxTest::TestSuite {

public:

	void testDefaultConstructor() {
		ChanceDeck cd;
		//The first card drawn should be an 'Advance to Go' card
		Card drawn_card = cd.drawCard();
		TS_ASSERT_EQUALS(drawn_card.description(), "Advance to Go");
	}

	void testCardActions() {
		/*
		Board b;
		Player p;
		ChanceDeck cd;
		//Move the Player to an arbitrary location 'on the board'
		p.moveTo(18);
		TS_ASSERT_EQUALS(p.location(), 18);
		//Draw an 'Advance to Go' Chance card
		Card drawn_card = cd.drawCard();
		//Perform the Card's action on the Player
		drawn_card.performAction(b, p);
		//The Player should have been moved back to 'Go' (index zero)
		TS_ASSERT_EQUALS(p.location(), 0);
		*/
	}

private:

	Board b;
	Player p;

};

#endif

