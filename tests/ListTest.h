#ifndef LIST_TEST_H
#define LIST_TEST_H

//Protected includes
#include <iostream>
#include <cxxtest/TestSuite.h>

//Class header include
#include "../lib/List.h"

using namespace std;

class ListTest : public CxxTest::TestSuite {

public:

	/* Constructor Tests */
	
	void testDefaultConstructor() {
		List<int> li;
		List<float> lf;
		List<string> ls;
		//Assert zero size
		TS_ASSERT_EQUALS(li.size(), 0);
		TS_ASSERT_EQUALS(lf.size(), 0);
		TS_ASSERT_EQUALS(ls.size(), 0);
		//Assert zero items
		TS_ASSERT_THROWS(li.getFirst(), length_error);
		TS_ASSERT_THROWS(li.getLast(), length_error);
	}

	void testCopyConstructorWithEmptyList() {
		List<int> l1;
		List<int> l2(l1);
		//Assert zero size
		TS_ASSERT_EQUALS(l2.size(), 0);
	}

	void testCopyConstructorWithPopulatedList() {
		//Populate a List with strings
		List<string> l1;
		l1.pushEnd("foo");
		l1.pushEnd("bar");
		l1.pushEnd("baz");	
		//Assets three items in l1
		TS_ASSERT_EQUALS(l1.size(), 3);
		//Call a copy constructor
		List<string> l2(l1);
		//Assert three items l2
		//TS_ASSERT_EQUALS(l2.size(), 3);
	}

	void testFillConstructor() {
		List<float> lf(10, 3.14);
		//Assert size 10
		TS_ASSERT_EQUALS(lf.size(), 10);
		//Assert item value
		for(unsigned int i = 0; i < lf.size(); i++) {
			//Fuzzy (delta) comparison for floating-point values
			TS_ASSERT_DELTA(lf.at(i), 3.14, 0.001);
		}
	}

	/* Accessor Tests */

	void testSize() {
		List<string> l1;
		TS_ASSERT_EQUALS(l1.size(), 0);
		List<string> bacon(10, "BaconStrips&");
		TS_ASSERT_EQUALS(bacon.size(), 10);
	}

	void testGetFirst() {
		List<int> l1;
		TS_ASSERT_THROWS(l1.getFirst(), length_error);
		List<int> l2(1, 1);
		TS_ASSERT_EQUALS(l2.getFirst(), 1);
		List<int> l3;
		l3.pushEnd(1);
		l3.pushEnd(2);
		l3.pushEnd(3);
		TS_ASSERT_EQUALS(l3.getFirst(), 1);
	}

	void testGetLast() {
		List<int> l1;
		TS_ASSERT_THROWS(l1.getLast(), length_error);
		List<int> l2(1,1);
		TS_ASSERT_EQUALS(l2.getLast(), 1);
		List<int> l3;
		l3.pushEnd(1);
		l3.pushEnd(2);
		l3.pushEnd(3);
		TS_ASSERT_EQUALS(l3.getLast(), 3);
	}

	void testAt() {
		List<string> ls;
		TS_ASSERT_THROWS(ls.at(0), length_error);
		ls.pushEnd("foo");
		ls.pushEnd("bar");
		ls.pushEnd("baz");
		TS_ASSERT_EQUALS(ls.at(0), "foo");
		TS_ASSERT_EQUALS(ls.at(1), "bar");
		TS_ASSERT_EQUALS(ls.at(2), "baz");
		TS_ASSERT_THROWS(ls.at(3), length_error);
	}

	void testAtWithNegativeIndices() {
		List<string> ls;
		TS_ASSERT_THROWS(ls.at(-1), length_error);
		ls.pushEnd("foo");
		ls.pushEnd("bar");
		ls.pushEnd("baz");
		TS_ASSERT_EQUALS(ls.at(-1), "baz");
		TS_ASSERT_EQUALS(ls.at(-2), "bar");
		TS_ASSERT_EQUALS(ls.at(-3), "foo");
	}

	void testContains() {
		List<int> li;
		TS_ASSERT(!li.contains(123));
		li.pushEnd(100);
		li.pushEnd(125);
		li.pushEnd(150);
		TS_ASSERT(li.contains(150));
		TS_ASSERT(!li.contains(0));
		TS_ASSERT(!li.contains(175));
	}

	void testContainsAllFromIdenticalList() {
		List<int> l1;
		l1.pushEnd(1);
		l1.pushEnd(2);
		l1.pushEnd(3);
		List<int> l2(l1);
		TS_ASSERT(l1.containsAll(l2));
	}

	void testContainsAllFromSmallerList() {
		List<int> l1;
		l1.pushEnd(1);
		l1.pushEnd(2);
		l1.pushEnd(3);
		List<int> l2;
		l2.pushEnd(1);
		l2.pushEnd(2);
		TS_ASSERT(l1.containsAll(l2));
	}

	void testContainsAllFromLargerList() {
		List<int> l1;
		l1.pushEnd(1);
		l1.pushEnd(2);
		List<int> l2;
		l2.pushEnd(1);
		l2.pushEnd(2);
		l2.pushEnd(3);
		TS_ASSERT(!l1.containsAll(l2));
	}

	void testEqualsIdenticalList() {
		List<string> l1;
		l1.pushEnd("uno");
		l1.pushEnd("dos");
		l1.pushEnd("tres");
		List<string> l2(l1);
		TS_ASSERT(l1.equals(l2));
	}

	void testEqualsNonIdenticalList() {
		List<string> l1;
		l1.pushEnd("uno");
		l1.pushEnd("dos");
		l1.pushEnd("tres");
		List<string> l2;
		l2.pushEnd("not");
		l2.pushEnd("the");
		l2.pushEnd("same");
		TS_ASSERT(!l1.equals(l2));
	}

	/* Mutator Tests - Node Operations) */

	void testPushFront() {
		List<int> li;
		li.pushFront(20);
		TS_ASSERT_EQUALS(li.size(), 1);
		TS_ASSERT_EQUALS(li.at(0), 20);
		li.pushFront(25);
		TS_ASSERT_EQUALS(li.size(), 2);
		TS_ASSERT_EQUALS(li.at(0), 25);
	}

	void testPushEnd() {
		List<string> ls;
		ls.pushEnd("zerg");
		TS_ASSERT_EQUALS(ls.size(), 1);
		TS_ASSERT_EQUALS(ls.at(0), "zerg");
		ls.pushEnd("rush");
		TS_ASSERT_EQUALS(ls.size(), 2);
		TS_ASSERT_EQUALS(ls.at(1), "rush");
	}

	void testPopFront() {
		List<string> ls;
		ls.pushEnd("let");
		ls.pushEnd("me");
		ls.pushEnd("out!");
		TS_ASSERT_EQUALS(ls.popFront(), "let");
		TS_ASSERT_EQUALS(ls.popFront(), "me");
		TS_ASSERT_EQUALS(ls.popFront(), "out!");
	}

	void testPopEnd() {
		List<string> ls;
		ls.pushEnd("let");
		ls.pushEnd("me");
		ls.pushEnd("out!");
		TS_ASSERT_EQUALS(ls.popEnd(), "out!");
		TS_ASSERT_EQUALS(ls.popEnd(), "me");
		TS_ASSERT_EQUALS(ls.popEnd(), "let");
	}

	void testSetNth() {
		List<bool> lb(3, false);
		lb.setNth(0, true);
		lb.setNth(2, true);
		TS_ASSERT(lb.at(0));
		TS_ASSERT(!lb.at(1));
		TS_ASSERT(lb.at(2));
	}

	void testSetNthWithNegativeIndex() {
		List<bool> lb(5, true);
		lb.setNth(-1, false);
		lb.setNth(-3, false);
		lb.setNth(-5, false);
		TS_ASSERT(!lb.at(0));
		TS_ASSERT(!lb.at(2));
		TS_ASSERT(!lb.at(4));
	}

	void testSetNthWithInvalidIndex() {
		List<bool> lb(10, true);
		TS_ASSERT(!lb.setNth(-11, false));
		TS_ASSERT(!lb.setNth(10, false));
	}

	void testInsertNth() {
		List<string> ls;
		ls.pushEnd("Somebody");
		ls.pushEnd("up");
		ls.pushEnd("the");
		//Item inserts
		ls.insertNth(1, "set");
		ls.insertNth(3, "us");
		ls.insertNth(5, "bomb.");
		TS_ASSERT_EQUALS(ls.size(), 6);
		TS_ASSERT_EQUALS(ls.at(0), "Somebody");
		TS_ASSERT_EQUALS(ls.at(1), "set");
		TS_ASSERT_EQUALS(ls.at(2), "up");
		TS_ASSERT_EQUALS(ls.at(3), "us");
		TS_ASSERT_EQUALS(ls.at(4), "the");
		TS_ASSERT_EQUALS(ls.at(5), "bomb.");
	}

	void testInsertNthWithNegativeIndex() {
		List<int> li;
		li.pushEnd(1);
		li.pushEnd(3);
		li.pushEnd(5);
		li.insertNth(-2, 2);
		li.insertNth(-1, 4);
		TS_ASSERT_EQUALS(li.size(), 5);
		TS_ASSERT_EQUALS(li.at(1), 2);
		TS_ASSERT_EQUALS(li.at(3), 4);
	}

	void testInsertNthWithInvalidIndex() {
		List<bool> lb(10, true);
		TS_ASSERT(!lb.insertNth(-11, false));
		TS_ASSERT(!lb.insertNth(11, false));
	}

	void testInsertNthWithEmptyList() {
		List<int> li;
		TS_ASSERT(!li.insertNth(1, 5));
		TS_ASSERT(li.insertNth(0, 5));
	}

	void testInsertNthAtBoundaries() {
		List<string> ls;
		ls.pushEnd("upon");
		ls.pushEnd("a");
		ls.insertNth(0, "Once");
		TS_ASSERT_EQUALS(ls.size(), 3);
		TS_ASSERT_EQUALS(ls.at(0), "Once");
		TS_ASSERT_EQUALS(ls.at(1), "upon");
		ls.insertNth(3, "time");
		TS_ASSERT_EQUALS(ls.at(-2), "a");
		TS_ASSERT_EQUALS(ls.at(-1), "time");
	}

	void testDeleteNth() {
		List<int> li;
		li.pushEnd(1);
		li.pushEnd(2);
		li.pushEnd(3);
		//Remove first item
		TS_ASSERT_EQUALS(li.deleteNth(0), 1);
		TS_ASSERT_EQUALS(li.size(), 2);
		//Remove first item (again)
		TS_ASSERT_EQUALS(li.deleteNth(0), 2);
		TS_ASSERT_EQUALS(li.size(), 1);
	}

	void testDeleteNthWithNegativeIndex() {
		List<int> li;
		li.pushEnd(1);
		li.pushEnd(2);
		li.pushEnd(3);
		//Remove the last item
		TS_ASSERT_EQUALS(li.deleteNth(-1), 3);
		//Remove the last item (again)
		TS_ASSERT_EQUALS(li.deleteNth(-1), 2);
	}

	void testDeleteWithInvalidIndex() {
		List<int> li(15, 3);
		TS_ASSERT_THROWS(li.deleteNth(-16), length_error);
		TS_ASSERT_THROWS(li.deleteNth(15), length_error);
	}

	void testDeleteNthWithEmptyList() {
		List<int> li;
		TS_ASSERT_THROWS(li.deleteNth(0), length_error);
		TS_ASSERT_THROWS(li.deleteNth(1), length_error);
		TS_ASSERT_THROWS(li.deleteNth(-1), length_error);
	}

	/* Mutator Test - (Set-like Operations) */
	
	void testAppend() {
		List<string> l1;
		l1.pushEnd("Let");
		l1.pushEnd("them");
		List<string> l2;
		l2.pushEnd("eat");
		l2.pushEnd("cake.");
		l1.append(l2);
		TS_ASSERT_EQUALS(l1.size(), 4);
		TS_ASSERT_EQUALS(l1.at(0), "Let");
		TS_ASSERT_EQUALS(l1.at(-1), "cake.");
	}

	void testMeshWithIdenticalSizes() {
		List<string> l1;
		l1.pushEnd("Let");
		l1.pushEnd("eat");
		List<string> l2;
		l2.pushEnd("them");
		l2.pushEnd("cake.");
		List<string> l3 = l1.mesh(l2);
		TS_ASSERT_EQUALS(l3.size(), 4);
		TS_ASSERT_EQUALS(l3.at(0), "Let");
		TS_ASSERT_EQUALS(l3.at(3), "cake.");
	}

	void testMeshWithNonIdenticalSizes() {
		List<string> l1(3, "Duck season!");
		List<string> l2(3, "Rabbit season!");
		l1.pushEnd("Rabbit season!"); //Classic Bugs ...
		List<string> l3 = l1.mesh(l2);
		TS_ASSERT_EQUALS(l3.size(), 7);
		TS_ASSERT_EQUALS(l3.at(0), "Duck season!");
		TS_ASSERT_EQUALS(l3.at(1), "Rabbit season!");
		TS_ASSERT_EQUALS(l3.at(6), "Rabbit season!");
	}
	  
	void testPrint() {
		cout << "\n";
		List<int> li;
		li.pushEnd(1);
		li.pushEnd(2);
		li.pushEnd(3);
		li.pushEnd(4);
		li.pushEnd(5);
		li.print();
		List<string> ls;
		ls.pushEnd("Beam");
		ls.pushEnd("me");
		ls.pushEnd("up");
		ls.pushEnd("Scotty");
		ls.print();
	}

};

#endif

