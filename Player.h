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

class Player {

public:

	static const int MAXIMUM_JAIL_SENTENCE = 2;

	bool hasGetOutOfJailChance;
	bool hasGetOutOfJailCommunityChest;

	/**
	 * Player class constructor. Takes a seed with which to seed the Player's own random
	 * number generator (which should stay in sync across all Players), as well as a
	 * reference to a shared ofstream object which a Player uses to record their turns.
	 *
	 * @param 	seed 			A seed provided by the Simulator object
	 * @param 	output_channel 	A reference to an ofstream provided by the Simulator object
	 */
	Player(unsigned int id)
	: id_(id),
	  location_(0),
	  detained_(false),
	  turns_in_jail_(0),
	  hasGetOutOfJailChance(false),
	  hasGetOutOfJailCommunityChest(false) { }
	
	//Player class destructor
	~Player() { }

	//Accessor methods
	unsigned int getId() { return this->id_; }
	int getLocation()    { return this->location_; }
	bool isDetained()      { return this->detained_; }
	int getTurnsInJail() { return this->turns_in_jail_; }

	//Mutator methods
	Player& setLocation(int n) {
		this->location_ = n;
		return *this;
	}
	void setDetention(bool val) {
		//Reset the Player's 'time served'
		this->turns_in_jail_ = 0;
		this->detained_ = val;
	}
	void incrementTurnsInJail() {
		if(this->detained_) {
			this->turns_in_jail_++;
		} else {
			//No-op
		}
	}
	
private:

	unsigned int id_;
	int location_;
	bool detained_;
	int turns_in_jail_;

};

#endif

