/**
 * @file Player.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Describes the public interface and private methods of the Player class. This
 * class is designed to store the state of a player in a game of Monopoly. A player's
 * state includes his position on the board (current location, as defined by a Board
 * Property index), his citizen status (in-jail or out-of-jail), as well as a small
 * Card queue to store any Get-Out-Of-Jail cards which the Player draws from either
 * deck ('Community Chest' or 'Chance').
 */

#ifndef PLAYER_H
#define PLAYER_H

//Protected includes
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include "lib/Queue.h"

#include <iostream>

//Class dependencies
#include "Board.h"

using namespace std;

class Player {

public:

	/*** Public interface implementation ***/

	/**
	 * Player class constructor. Takes a seed with which to seed the Player's own random
	 * number generator (which should stay in sync across all Players), as well as a
	 * reference to a shared ofstream object which a Player uses to record their turns.
	 *
	 * @param 	seed 			A seed provided by the Simulator object
	 * @param 	output_channel 	A reference to an ofstream provided by the Simulator object
	 */
	Player(unsigned int id, Board &board, int seed, ofstream &output_channel)
	: id_(id),
	  board_(board),
	  seed_(seed),
	  output_channel_(output_channel),
	  location_(0),
	  in_jail_(false),
	  doin_time_(0) {
		
		/**
		 * Seed the random number generator with the seed provided. Because all
		 * Players recieve an identical seed from the Simulator, we can rest assured
		 * that each player follows the same 'system of randomness'
		 */
		srand(seed);

	}

	/* Player class destructor */
	~Player() { }

	//Accessor methods

	unsigned int id() { return this->id_; }
	int location() { return this->location_; }
	bool inJail() { return this->in_jail_; }

	//Mutator methods

	void move() {
		//Execute private, recursive move method
		this->move(0);
	}

private:

	static const int MAXIMUM_JAIL_SENTENCE = 3;

	unsigned int id_;
	int location_;
	bool in_jail_;
	int doin_time_;
	
	Board &board_;
	int seed_;
	ofstream &output_channel_;

	/*** Private method implementation ***/

	void move(int r_depth) {
		
		int die1, die2;
		bool doubles = ((die1 = this->getDiceRoll()) == (die2 = this->getDiceRoll()));
		this->printRoll(die1, die2);

		/**
		 * Cases:
		 *
		 * 1. The player is not in jail, and rolls two different numbers - RETURN
		 * 2. The player is not in jail, and rolls doubles - RECURSIVE
		 * 3. The player is not in jail, and rolls doubles for the third time - RETURN
		 * 4. The player is in jail, and rolls doubles - RETURN
		 * 5. The player is in jail, has been in jail for 3 turns - RETURN / RECURSIVE
		 * 6. The player is in jail, and does not roll doubles - RETURN
		 */
		
		if(!this->in_jail_) {
			/* Case 1 */
			if(!doubles) {
				this->advanceBy(die1 + die2);
				return;
			} else
			/* Case 2 */
			if(doubles && r_depth < 2) {
				this->advanceBy(die1 * 2);
				return move(r_depth + 1);
			} else
			/* Case 3 */
			if(r_depth == 2) {
				//The player has rolled 'doubles' three times in a row. As per
				//Monopoly rules, they are sent to jail!
				this->output_channel_ << "You've rolled doubles three times! Go to jail!\n";
				Property& dest = this->board_.propertyAt(Board::JAIL_LOCATION).incrementCount();
				this->location_ = this->board_.indexOf(dest);
				this->in_jail_ = true;
				return;
			}
		} else {
			/* Case 4 & 5*/
			//You might have to rethink this ...
			//What if a player rolls doubles on their 4th try?
			if(doubles || this->doin_time_ >= Player::MAXIMUM_JAIL_SENTENCE) {
				//Let the poor guy go ...
				this->in_jail_ = false;
				this->doin_time_ = 0;
				this->advanceBy(die1 + die2);
				return;
			} else {
			/* Case 6 */
				this->doin_time_++;
				return;
			}
		}

	}

	void advanceBy(int sum) {
		//Determines the Player's destination
		//We're writing it this way so that the location index still 'wraps'
		Property& dest = this->board_.propertyAt(this->location_ + sum);
		this->location_ = this->board_.indexOf(dest);
		//Increase the 'occupation' count for the destination Property and have
		//the destination Property respond to the Player if necessary
		dest.incrementCount().respond(this->board_, *this);
		this->printMove(sum);
		
	}

	int getDiceRoll() const { return (rand() % 6) + 1; }

	void printRoll(int die1, int die2) {
		this->output_channel_ << " Player " << this->id_ << " rolled ";
		this->output_channel_ << "(" << die1 << ", " << die2 << ")\n";
	}

	void printMove(int sum) {
		this->output_channel_ << " Player " << this->id_ << " moved " << sum << " spaces to ";
		this->output_channel_ << this->board_.propertyAt(this->location_).name() << "\n"; 		
	}

};

#endif

