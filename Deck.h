/**
 * @file Deck.h
 * @author Michael Zalla
 * @date 12-2-2013
 *
 * Describes the protected methods and private methods of the Deck class.
 * This class serves as the abstract base class for ChanceDeck and CChestDeck
 * objects. A deck is simply a wrapper for a basic Queue. This base class
 * implements some generalized card action functions for moving players between
 * properties, and to the jail. The queue holds pointers to Cards on the heap.
 */

#ifndef DECK_H
#define DECK_H