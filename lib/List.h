/**
 * @file List.h
 * @author Michael Zalla
 * @date 12-1-2013
 * 
 * Describes the public interface and private methods of the templated List class.
 * This class is designed to be initialized as a List of a particular data type
 * (or class). The List class is a singly linked list of nodes that each hold a
 * value or object of that data type (or class), as well as a pointer to the 'next'
 * node. The end of the List is denoted by a NULL 'next' pointer.
 */

#ifndef LIST_H
#define LIST_H

//Protected includes
#include <iostream>
#include <stdexcept>

using namespace std;

template<class T> class List {

private:

	/**
	 * Implementation of a templated Node class used by the List class. Each Node
	 * must be instantiated with a specific data type (or class) which we will
	 * reference with 'NT' ('Node type'). Each List object may only hold Nodes of
	 * a single data type.
	 */
	template<class NT> class Node {
	private:
		//Node constructors
		Node (NT initial_value) : value(initial_value), next(NULL) { }
		//Node (NT initial_value, Node<NT>* prev, Node<NT>* next)
		Node (NT initial_value, Node<NT>* next) : value(initial_value), next(next) { }
		virtual ~Node() { }
		//Member variables
		NT value;
		//Node<NT>* prev;
		Node<NT>* next;
		//Establish a friend relationship so that any List may access the Node's
		//value (this is useful for our List's copy constructor, as well as for
		//accessors such as List::contains() and List::equals())
		friend class List<NT>;
	};

public:

	/*** Public interface implementation ***/

	//Class constructors and destructor

	/* Default List constructor; uses an initialization list */
	List() : size_(0), head_(NULL), tail_(NULL) { }

	/**
	 * List copy constructor. Accepts an existing List object and creates a new
	 * List which contains an identical set of nodes and associated node values
	 * that follow the same order.
	 *
	 * @param 	other 	A const reference to an existing List object
	 */
	List(const List<T>& other) : size_(0), head_(NULL), tail_(NULL) {
		//Iterate over each Node inside 'other'
		for(unsigned int i = 0; i < other.size(); i++) {
			//Retrieve that Node's value and use it to push a new Node
			//into our List
			this->pushEnd(other.at(i));
		}
	}

	/**
	 * List fill constructor. Creates a new List object of size 'size' in which
	 * every node holds a value of 'node_value'.
	 *
	 * @param 	size 	The desired size (length) of the new List
	 * @param 	node 	An existing Node from which to copy all new Nodes in the List
	 */
	List(int size, const T value) : size_(0), head_(NULL), tail_(NULL) {
		for(unsigned int i = 0; i < size; i++) {
			this->pushEnd(value);
		}
	}

	/* List destructor */
	virtual ~List() {
		for(unsigned int i = this->size_ - 1; i > -1; i--) {
			//Release any Node objects allocated in heap memory using
			//List::deleteNth()
			this->deleteNth(i);
		}
	}
	
	//Accessor methods
	
	/* Returns the size (length) of the List */
	int size() const {
		return this->size_;
	}

	/* Returns the value of the first Node in the List. Throws a length_error
	 * exception if called on an empty List object. */
	T getFirst() const {
		if(this->head_ == NULL) {
			throw length_error("The List is empty, and has no first Node.");
		} else {
			return this->head_->value;
		}
	}

	/* Returns the value of the last Node in the List. Throws a length_error
	 * exception if called on an empty List object. */
	int getLast() const {
		if(this->tail_ == NULL) {
			throw length_error("The List is empty, and has no last Node.");
		} else {
			return this->tail_->value;
		}
	}

	/**
	 * Returns the value of the n-th Node in the List. Throws a length_error exception
	 * if the given index is out-of-bounds. Supplying the method with a negative
	 * index should count Nodes backwards from the last Node in the List (in this
	 * case, an index of -1 refers to the last Node in the List)
	 *
	 * @param 	n 	A Node index
	 */
 	T at(int n) const {
 		Node<T>* node = this->nodeAt(n);
 		if(node == NULL) {
 			throw length_error("The given index is out-of-bounds!");
 		} else {
 			return node->value;
 		}
 	}

	/**
	 * Returns a boolean value indicating whehter any of the List's Nodes holds
	 * a given value of type T.
	 *
	 * @param 	value 	A value (or object) of type T
	 */
 	bool contains(const T value) const {
		for(unsigned int i = 0; i < this->size_; i++) {
			if(this->at(i) == value) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Returns a boolean value indicating whether the Node values contained within
	 * a provided List are also contained within the callee. The order of the Node
	 * values do not need to match. Returns false if the provided List is larger
	 * than the callee.
	 *
	 * @param 	other 	A const reference to an existing List object
	 */
 	bool containsAll(const List<T>& other) const {
		if(other.size() > this->size_) {
			return false;
		} else {
			for(unsigned int i = 0; i < other.size(); i++) {
				if(!this->contains(other.at(i))) {
					return false;
				}
			}
		}
		return true;
	}

	/**
	 * Returns a boolean value indicating whether the values contained within
	 * a provided List are also contained within the callee, and occur in the
	 * same order. Returns false if the provided List is larger than the callee.
	 *
	 * @param 	other 	A const reference to an existing List object
	 */
 	bool equals(const List<T>& other) const {
 		if(other.size() != this->size_) {
 			return false;
 		} else {
 			for(unsigned int i = 0; i < other.size(); i++) {
 				if(this->at(i) != other.at(i)) {
 					return false;
 				}
 			}
 		}
 		return true;
	}

	//Mutator methods

	/**
	 * Creates a new Node, assigning its value to a given value (or object)
	 * of type T, and places the Node at the front of the List (where it becomes
	 * the new head).
	 *
	 * @param 	value 	A value to assign to the new Node
	 */
 	void pushFront(T value) {
 		this->head_ = this->createNode(value, this->head_);
 		//Update the 'tail' pointer if still set to NULL
 		if(this->size_ == 0) {
 			this->tail_ = this->head_;
 		}
 		this->size_++;
	}

	/**
	 * Creates a new Node, assigning its value to a given value (or object)
	 * of type T, and places the Node at the end of the List (where it becomes
	 * the new tail).
	 *
	 * @param 	value 	A value to assign to the new Node
	 */
 	void pushEnd(T value) {
 		if(this->size_ == 0) {
 			this->pushFront(value);
 		} else {
 			//Add a new Node to the List, and update the 'tail' pointer
 			this->tail_->next = this->createNode(value, NULL);
 			this->tail_ = this->tail_->next;
 			this->size_++;
 		}
	}

	/**
	 * Removes the Node at the head of the List, and returns that Node's value.
	 * Reassings the List's head to next Node, or to NULL. Throws a length_error
	 * exception if called on an empty List object.
	 */
 	T popFront() {
 		if(this->size_ == 0) {
			throw length_error("The List is empty, and has no first Node.");
 		} else {
 			T value = this->head_->value;
 			Node<T>* new_head = this->nodeAt(1); //May be NULL!
 			//Deallocate the current head Node and reassign the 'head' pointer
 			delete this->head_;
 			//Decrement the List's size
 			this->size_--;
 			//Update the List's 'head' and 'tail' pointers
 			this->head_ = new_head;
 			if(this->size_ == 0) {
 				this->tail_ = NULL; //Sets a new end of the List
 			}
 			return value;
 		}
	}

	/**
	 * Removes the Node at the tail of the List, and returns that Node's value.
	 * Reassigns the List's tail to the previous Node, or to NULL. Throws a
	 * length_error exception if called on an empty List object.
	 */
 	T popEnd() {
 		if(this->size_ == 0) {
 			throw length_error("The List is empty, and has no last Node.");
 		} else if(this->size_ == 1) {
 			return this->popFront();
 		} else {
 			T value = this->tail_->value;
 			Node<T>* new_tail = this->nodeAt(this->size_ - 2);
 			new_tail->next = NULL;
 			//Deallocate the current tail Node and reassign the 'tail' pointer
 			delete this->tail_;
 			this->tail_ = new_tail;
 			//Decrement the List's size
 			this->size_--;
 			return value;
 		}
	}

	/**
	 * Sets the value of the Node specified by the index 'n'. Returns true on success;
	 * returns false if the given index is out-of-bounds. Supplying the method with
	 * negative index should count Nodes backwards from the last Node in the List
	 * (in this case, an index of -1 refers to the last Node in the List).
	 *
	 * @param 	n 		A Node index
	 * @param 	value 	A value (of type T) to assign to a Node
	 */
 	bool setNth(int n, T value) {
 		Node<T>* node = this->nodeAt(n);
 		if(node != NULL) {
 			node->value = value;
 			return true;
 		} else {
 			return false;
 		}
	}

	/**
	 * Inserts a new Node with a specified value at the n-th position in the List.
	 * Returns true on success; rerturns false if the given index is out-of-bounds.
	 * Updates the List's size. Supplying the method with negative index should
	 * count Nodes backwards from the last Node in the List (in this case, an
	 * index of -1 refers to the last Node in the List).
	 *
	 * @param 	n 		A Node index
	 * @param 	value 	A value (of type T) to assign to a Node
	 */
 	bool insertNth(int n, T value) {

		//The following cases could occur when this method is called:
		// a. The List has no nodes, in which case 0 is the only valid index to pass
		// b. The List has nodes, and the given index is zero (new node becomes the head)
		// c. The given index equals the List's size (new node becomes the tail)
		// d. The index lies between (0, size), in which case the new node will be
		//    inserted between two existing nodes

 		//First, check that the index is within a valid range
 		//As we are storing size_ as an unsigned int, we'll need to perform a conversion
		signed int size = this->size_;
 		if(n < (-size) || n > size) {
 			return false;
 		}

 		//Check for an insert at the end of the List
 		if(n == this->size_) {
 			this->pushEnd(value);
 			return true;
 		}
 		//Check for an insert at the beginning of the List
 		int index = this->resolveIndex(n); //Map 'n' into the positive range [0, size)
 		if(index == 0) {
 			this->pushFront(value);
 			return true;
 		}

 		//At this point, we can assume that a Node exists before and after the
 		//specified Node. Allocate a new Node and slip it between the previous
 		//and next Nodes
 		Node<T>* prev = this->nodeAt(index - 1);
 		Node<T>* next = this->nodeAt(index);
 		Node<T>* new_node = this->createNode(value, next);
 		prev->next = new_node;

 		//Increment the List's size property
 		this->size_++;
 		
 		return true;

	}

	/**
	 * Removes the n-th Node from the List, and returns the value of the removed
	 * Node. Throws a length_error exception if the given index is out-of-bounds.
	 * Updates the List's head and tail if necessary. Updates the List's size.
	 * Supplying the method with negative index should count Nodes backwards from
	 * the last Node in the List (in this case, an index of -1 refers to the last
	 * Node in the List).
	 * 
	 * @param 	n 		A Node index
	 */
 	T deleteNth(int n) {
 		Node<T>* node = this->nodeAt(n);
 		if(node == NULL) {
 			throw length_error("The given index is out-of-bounds!");
 		} else {
 			//Check for a 'popFront' or 'popEnd' case
 			if(n == 0) {
 				return this->popFront();
 			} else if(n == this->size_ - 1) {
 				return this->popEnd();
 			}

 			//Map the index into the positive range [0, size]
 			int index = this->resolveIndex(n);

 			//We'll need to determine the Node's previous and next Nodes, if present
 			//We'll have to be extra careful finding 'prev', due to our class's support
 			//for negative indices
 			Node<T>* prev = (index == 0) ? NULL : this->nodeAt(index - 1);
 			Node<T>* next = node->next; //May be NULL!

 			if(prev == NULL) {
 				this->head_ = node->next;
 			} else {
 				//Looping previous Node's 'next' to point to next
 				prev->next = next;
 			}

 			//Decrement the List's size
 			this->size_--;

 			//Delete the specified Node and return its value
 			T value = node->value;
 			delete node;
 			return value;
 		}
	}

	/**
	 * Reads all Node values from a provided List and adds them (as new Nodes)
	 * to the end of the callee List. Creates a copy of each Node value.
	 *
	 * @param 	other 	A const reference to an existing List object
	 */
 	void append(const List<T>& other) {
 		for(int i = 0; i < other.size(); i++) {
 			this->pushEnd(other.at(i));
 		}
	}

	/**
	 * Creates a new List object. Copies the Nodes from the callee List and 'other',
	 * and inserts the copies in every-other order (C[0],O[0],C[1],O[1], ... C[cn] ... O[on]) into the new List.
	 * Returns the resulting List. This method does not modify the callee List.
	 *
	 * @param 	other 	A const reference to an existing List object
	 */
	List<T> mesh(const List<T>& other) const {
		List<T> ret;
		int i1 = 0,
			i2 = 0;
		while(ret.size() < (this->size_ + other.size())) {
			if(i1 < this->size_) {
				ret.pushEnd(this->at(i1));
				i1++;
			}
			if(i2 < other.size()) {
				ret.pushEnd(other.at(i2));
				i2++;
			}
		}
		return ret;
	}
	
	void print() {
		for(unsigned int i = 0; i < this->size_; i++) {
			cout << this->at(i) << " -> ";
		}
		cout << "NULL\n";
		cout << "(" << this->size_ << " items)\n";
	}

private:

	unsigned int size_;
	Node<T>* head_;
	Node<T>* tail_;

	/*** Private method implementation ***/

	/**
	 * Returns a boolean value indicating whther a given integer is a valid Node
	 * index in the List. This includes both positive and negative indeces. The
	 * valid range for List indices is [(-size), (size - 1)].
	 *
	 * @param 	n 	A Node index
	 */
 	bool isValidIndex(int n) const {
		//As we are storing size_ as an unsigned int, we'll need to perform a conversion
		signed int size = this->size_;
		if(n < (-size) || n > (size - 1)) {
			return false;
		}
		return true;
	}

	/**
	 * Returns an index referencing a Node in the List, mapped into a positive
	 * range. The method assumes that the given index is valid (no bounds checking).
	 * This method is designed to be used in conjunction with isValidIndex
	 *
	 * @param 	n 	A Node index
	 */
 	int resolveIndex(int n) const {
 		if(n >= 0) {
 			return n;
 		} else {
 			//A negative index was provided, so this will actually result in an
 			//index that is in the range [0, size)
 			return this->size_ + n;
 		}
	}

	/**
	 * Returns a new Node object with a given value of type T and a pointer to its
	 * following Node in the List.
	 *
	 * @param 	value 	A value (of type T) to assign to a Node
	 * @param 	next 	A pointer to a Node
	 */
 	Node<T>* createNode(T value, Node<T>* next) {
 		return new Node<T>(value, next);
	}

	/**
	 * Returns a pointer to the Node specified by the index 'n'. Returns NULL if
	 * the given index is out-of-bounds.
	 *
	 * @param 	n 	A Node index
	 */
 	Node<T>* nodeAt(unsigned int n) const {
 		if(this->isValidIndex(n)) {
			int index = this->resolveIndex(n);
 			Node<T>* current = this->head_;
 			for(unsigned int i = 0; i < index; i++) {
 				current = current->next;
 			}
 			return current;
 		} else {
 			return NULL;
 		}
	}

};

#endif

