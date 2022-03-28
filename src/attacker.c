// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t get_next_dir_random(
	direction_t possible_direction_1, 
	direction_t possible_direction_2,
	direction_t possible_direction_3){
    srand(time(NULL));
    int random_number = rand()%3;
  	if (random_number == 0)
  		return possible_direction_1;
  	if (random_number == 1)
  		return possible_direction_2;
  	return possible_direction_3;

}

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: unused parameters, remove these lines later
  //UNUSED(attacker_position);
  UNUSED(defender_spy);

  // Global state
  static position_t last_pos = INVALID_POSITION;
  static direction_t last_move = DIR_STAY;
  direction_t next_move = DIR_RIGHT;

  if (equal_positions(last_pos, (position_t) INVALID_POSITION)) 
    last_pos = attacker_position;
  else if (equal_positions(last_pos, attacker_position)){ // Check if player did not move
  	next_move = get_next_dir_random((direction_t) DIR_RIGHT, (direction_t) DIR_UP_RIGHT, (direction_t) DIR_DOWN_RIGHT);
  	while (next_move.i == last_move.i){
  		next_move = get_next_dir_random((direction_t) DIR_RIGHT, (direction_t) DIR_UP_RIGHT, (direction_t) DIR_DOWN_RIGHT);
  	}
  }
  else {
  		next_move = get_next_dir_random((direction_t) DIR_RIGHT, (direction_t) DIR_UP_RIGHT, (direction_t) DIR_DOWN_RIGHT);
  }

  last_move = next_move;
  last_pos =  attacker_position;
  return next_move;
}

