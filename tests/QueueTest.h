#ifndef QUEUE_TEST_H
#define QUEUE_TEST_H

//Protected includes
#include <iostream>
#include <string>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

//Class header include
#include "../lib/Queue.h"

using namespace std;

class QueueTest : public CxxTest::TestSuite {

public:

	/* Constructor Tests */

	void testDefaultConstructor() {
		Queue<int> q;
		TS_ASSERT_EQUALS(q.size(), 0);
		TS_ASSERT_THROWS(q.front(), length_error);
		TS_ASSERT_THROWS(q.back(), length_error);
	}

	void testCopyConstructorWithEmptyQueue() {
		Queue<int> q1;
		Queue<int> q2(q1);
		TS_ASSERT_EQUALS(q2.size(), 0);
	}

	void testCopyConstructorWithPopulatedQueue() {
		Queue<int> q1;
		q1.push(1);
		q1.push(2);
		q1.push(3);
		Queue<int> q2(q1);
		TS_ASSERT_EQUALS(q2.size(), 3);
		TS_ASSERT_EQUALS(q2.front(), 1);
		TS_ASSERT_EQUALS(q2.back(), 3);
	}

	/* Accessor Tests */

	void testSize() {
		Queue<string> q;
		TS_ASSERT_EQUALS(q.size(), 0);
		q.push("Larry");
		q.push("Curly");
		q.push("Moe");
		TS_ASSERT_EQUALS(q.size(), 3);
		q.pop();
		q.pop();
		TS_ASSERT_EQUALS(q.size(), 1);
	}

	void testAtOnEmptyQueue() {
		Queue<int> q;
		TS_ASSERT_THROWS(q.at(0), length_error);
	}

	void testAtOnPopulatedQueue() {
		Queue<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		TS_ASSERT_THROWS(q.at(-1), length_error);
		TS_ASSERT_EQUALS(q.at(0), 1);
		TS_ASSERT_EQUALS(q.at(1), 2);
		TS_ASSERT_EQUALS(q.at(2), 3);
		TS_ASSERT_THROWS(q.at(3), length_error);
	}

	void testFront() {
		Queue<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		TS_ASSERT_EQUALS(q.front(), 1);
		q.pop();
		TS_ASSERT_EQUALS(q.front(), 2);
		q.pop();
		TS_ASSERT_EQUALS(q.front(), 3);
		q.pop();
		TS_ASSERT_THROWS(q.front(), length_error);
	}

	void testBack() {
		Queue<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		TS_ASSERT_EQUALS(q.back(), 3);
		q.pop();
		TS_ASSERT_EQUALS(q.back(), 3);
		q.pop();
		TS_ASSERT_EQUALS(q.back(), 3);
		q.pop();
		TS_ASSERT_THROWS(q.back(), length_error);
	}

	/* Mutator Tests */

	void testPushOnEmptyQueue() {
		Queue<string> q;
		q.push("I'm first!");
		TS_ASSERT_EQUALS(q.size(), 1);
		TS_ASSERT_EQUALS(q.front(), "I'm first!");
		TS_ASSERT_EQUALS(q.back(), "I'm first!");
	}	

	void testPushOnPopulatedQueue() {
		Queue<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		TS_ASSERT_EQUALS(q.size(), 3);
		TS_ASSERT_EQUALS(q.front(), 1);
		TS_ASSERT_EQUALS(q.back(), 3);
	}

	void testPopOnEmptyQueue() {
		Queue<int> q;
		TS_ASSERT_THROWS(q.pop(), length_error);
	}

	void testPopOnPopulatedQueue() {
		Queue<string> q;
		q.push("Spongebob Squarepants");
		q.push("Patrick Star");
		q.push("Squidward Tentacles");
		TS_ASSERT_EQUALS(q.size(), 3);
		TS_ASSERT_EQUALS(q.front(), "Spongebob Squarepants");
		TS_ASSERT_EQUALS(q.back(), "Squidward Tentacles");
		q.pop();
		q.pop();
		TS_ASSERT_EQUALS(q.size(), 1);
		TS_ASSERT_EQUALS(q.front(), "Squidward Tentacles");
		TS_ASSERT_EQUALS(q.back(), "Squidward Tentacles");
	}
	  
};

#endif