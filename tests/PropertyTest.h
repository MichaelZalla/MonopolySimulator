/**
 * @file PropertyTest.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Contains unit tests for the Monopoly Property class.
 */

#ifndef PROPERTY_TEST_H
#define PROPERTY_TEST_H

//Protected includes
#include <iostream>
#include <string>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

//Class header include
#include "../Property.h"

using namespace std;

class PropertyTest : public CxxTest::TestSuite {

public:

	void testName() {
		Property p("Somewhere over the Rainbow");
		TS_ASSERT_EQUALS(p.name(), "Somewhere over the Rainbow");
	}

	void testIncrementCount() {
		Property p("Somewhere over the Rainbow");
		TS_ASSERT_EQUALS(p.count(), 0);
		p.incrementCount();
		p.incrementCount();
		p.incrementCount();
		TS_ASSERT_EQUALS(p.count(), 3);
	}

};

#endif