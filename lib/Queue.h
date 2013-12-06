/**
 * @file Queue.h
 * @author Michael Zalla
 * @date 12-1-2013
 * 
 * Describes the public interface and private methods of the Queue class.
 * This class layers a simpler and more strict interface on top of the List
 * class. The Queue is a first-in-first-out data structure.
 */

#ifndef QUEUE_H
#define QUEUE_H

//Protected includes
#include <iostream>
#include <stdexcept>
#include "List.h"

using namespace std;

template<class T> class Queue {

public:

	/*** Public interface implementation ***/

	//Class constructors and destructor
	
	/* Default Queue constructor */
	Queue() { }

	/* Queue copy constructor */
	Queue(const Queue<T>& other) {
		for(unsigned int i = 0; i < other.size(); i++) {
			this->push(other.at(i));
		}
	}

	/* Queue destructor */
	~Queue() { }

	//Accessor methods

	/* Returns the size (length) of the Queue */
	int size() const {
		return this->list.size();
	}
	
	/**
	 * Returns the value of the Queue item specified by the index 'n'. Performs
	 * basic index bounds checking. Throws a length_error exception when called
	 * on an empty Queue.
	 *
	 * @param 	n 	The index of an item in the Queue
	 */
 	T at(unsigned int n) const {
		if(this->size() == 0) {
			throw length_error("The Queue is empty!");
		} else if(n < 0 || n >= this->size()) {
			throw length_error("The given index is out-of-bounds!");
		} else {
			return this->list.at(n);
		}
	}

	/* Returns the value at the front of the Queue. Throws a length_error
	 * exception when called on an empty Queue.
	 */
	T front() const {
		/*
		if(this->size() == 0) {
			throw length_error("The Queue is empty!");
		} else {
			return this->list.at(0);
		}
		*/
		return this->at(0);
	}
	
	/* Returns the value at the back of the Queue. Throws a length_error
	 * exception when called on an empty Queue.
	 */
	T back() const {
		/*
		if(this->size() == 0) {
			throw length_error("The Queue is empty!");			
		} else {
			return this->list.at(-1);
		}
		*/
		return this->at(this->size() - 1);
	}

	/* Prints the items in the Queue in order. Begins with an opening bracket,
	 * followed by the series of values delimited by a comma, and ends with
	 * a closing bracket. The front of the Queue is printed on the left.
	 */
	void print() {
		cout << "\n[";
		for(unsigned int i = 0; i < this->size(); i++) {
			cout << this->list.at(i);
			if(i != (this->size() - 1)) {
				cout << ", ";
			}
		}
		cout << "]\n";
	}

	//Mutator methods

	/**
	 * Places a new value at the end of the Queue.
	 *
	 * @param  	value 	A value of type T
	 */
 	void push(T value) {
 		this->list.pushEnd(value);
	}
	
	/* Removes the item at the front of the Queue. Throws a length_error
	 * when called on an empty Queue.
	 */
	void pop() {
		if(this->size() == 0) {
			throw length_error("The Queue is empty!");
		} else {
			this->list.popFront();
		}
	}

private:
	
	List<T> list;

	/*** Private method implementation ***/

};

#endif

