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

	void testDefaultConstructor() {
		Property p("Somewhere Over The Rainbow");
		TS_ASSERT_EQUALS(p.count(), 0);
	}

	void testIs() {
		Property p1("Somewhere Over The Rainbow");
		Property p2("Somewhere Over The Rainbow");
		Property p3("Sesame Street");
		TS_ASSERT(p1.is(p1));
		TS_ASSERT(p1.is(p2));
		TS_ASSERT(!p1.is(p3));
	}

	void testIncrementCount() {
		Property p("Sesame Street");
		p.incrementCount();
		TS_ASSERT_EQUALS(p.count(), 1);
		p.incrementCount();
		p.incrementCount();
		p.incrementCount();
		TS_ASSERT_EQUALS(p.count(), 4);
	}

};

#endif