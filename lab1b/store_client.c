/*
 * CSE 351 Lab 1b (Manipulating Bits in C)
 *
 * Name(s): Robert Flores
 * NetID(s): rotyflo
 *
 * This is a file for managing a store of various aisles, represented by an
 * array of 64-bit integers. See aisle_manager.c for details on the aisle
 * layout and descriptions of the aisle functions that you may call here.
 *
 * Written by Porter Jones (pbjones@cs.washington.edu)
 */

#include <stdio.h>
#include <stddef.h>  // To be able to use NULL
#include "aisle_manager.h"
#include "store_client.h"
#include "store_util.h"

// Number of aisles in the store
#define NUM_AISLES 10

// Number of sections per aisle
#define SECTIONS_PER_AISLE 4

// Number of items in the stockroom (2^6 different id combinations)
#define NUM_ITEMS 64

// Global array of aisles in this store. Each unsigned long in the array
// represents one aisle.
unsigned long aisles[NUM_AISLES];

// Array used to stock items that can be used for later. The index of the array
// corresponds to the item id and the value at an index indicates how many of
// that particular item are in the stockroom.
int stockroom[NUM_ITEMS];


/* Starting from the first aisle, refill as many sections as possible using
 * items from the stockroom. A section can only be filled with items that match
 * the section's item id. Prioritizes and fills sections with lower addresses
 * first. Sections with lower addresses should be fully filled (if possible)
 * before moving onto the next section.
 */
void refill_from_stockroom() {
  // check every aisle
  for (char aisle_i = 0; aisle_i < 10; aisle_i += 1) {
    // check every section
    for (char section_i = 0; section_i < 4; section_i += 1) {
      unsigned short section_count = num_items(aisles + aisle_i, section_i);
      unsigned short section_id = get_id(aisles + aisle_i, section_i);
      
      // add appropriate items to aisle
      add_items(aisles + aisle_i, section_i, stockroom[section_id]);

      // remove added items from stockroom
      stockroom[section_id] -= (num_items(aisles + aisle_i, section_i) - section_count);
    }
  }
}

/* Remove at most num items from sections with the given item id, starting with
 * sections with lower addresses, and return the total number of items removed.
 * Multiple sections can store items of the same item id. If there are not
 * enough items with the given item id in the aisles, first remove all the
 * items from the aisles possible and then use items in the stockroom of the
 * given item id to finish fulfilling an order. If the stockroom runs out of
 * items, you should remove as many items as possible.
 */
int fulfill_order(unsigned short id, int num) {
  int count = 0;

  // check every aisle
  for (char aisle_i = 0; aisle_i < 10; aisle_i += 1) {
    // check every section
    for (char section_i = 0; section_i < 4; section_i += 1) {
      unsigned short section_id = get_id(aisles + aisle_i, section_i);

      // take items from section if id matches
      if (section_id == id) {
	unsigned short section_count = num_items(aisles + aisle_i, section_i);
        remove_items(aisles + aisle_i, section_i, num - count);
	count += (section_count - num_items(aisles + aisle_i, section_i));
      }

      // return count if number of items needed met
      if (num == count) {
        return count;
      }
    }
  }

  int needed_from_stockroom = num - count;

  // take what is left in the stockroom and return what all was found
  if (needed_from_stockroom > stockroom[id]) {
    count += stockroom[id];
    stockroom[id] = 0;
    return count;
  }

  // else take what is need from the stockroom and return the count
  count += needed_from_stockroom;
  stockroom[id] -= needed_from_stockroom;
  return count;
}

/* Return a pointer to the first section in the aisles with the given item id
 * that has no items in it or NULL if no such section exists. Only consider
 * items stored in sections in the aisles (i.e., ignore anything in the
 * stockroom). Break ties by returning the section with the lowest address.
 */
unsigned short* empty_section_with_id(unsigned short id) {
  // check every aisle
  for (int aisle_i = 0; aisle_i < 10; aisle_i += 1) {
    // check every section
    for (int section_i = 0; section_i < 4; section_i += 1) {
      unsigned short section_id = get_id(aisles + aisle_i, section_i);

      if (section_id == id) {
        unsigned short num = num_items(aisles + aisle_i, section_i);

	if (num == 0) {
          // get aisle address
	  unsigned short* aisle_address = (unsigned short*) (aisles + aisle_i);

	  // get section address
	  return aisle_address + section_i;
	}
      }
    }
  }
  return NULL;
}

/* Return a pointer to the section with the most items in the store. Only
 * consider items stored in sections in the aisles (i.e., ignore anything in
 * the stockroom). Break ties by returning the section with the lowest address.
 */
unsigned short* section_with_most_items() {
  int most_items = 0;
  unsigned short* aisle_with_most_items;

  // check every aisle
  for (int aisle_i = 9; aisle_i >= 0; aisle_i -= 1) {
    // check every section
    for (int section_i = 3; section_i >= 0; section_i -= 1) {
      unsigned short num = num_items(aisles + aisle_i, section_i);

      if (num >= most_items) {
        // new "most items" section
        most_items = num;

        // get aisle address
        unsigned short* aisle_address = (unsigned short*) (aisles + aisle_i);

        // get section address
        aisle_with_most_items = aisle_address + section_i;
      }
    }
  }
  return aisle_with_most_items;
}
