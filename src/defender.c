// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t get_next_dir_random_deffender(
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

direction_t change_next_move_if_needed(
	direction_t next_move, 
	Spy attacker_spy,
	position_t defender_position
	){
	position_t attacker_position = get_spy_position(attacker_spy);
	if (defender_position.j != attacker_position.j){
		if (attacker_position.j > defender_position.j)
			return (direction_t) DIR_DOWN_LEFT;
		return (direction_t) DIR_UP_LEFT;
	}
    return next_move;
}

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  // TODO: unused parameters, remove these lines later
  // Global state
  static position_t last_pos = INVALID_POSITION;
  static direction_t last_move = DIR_STAY;
  static int cheat_spy = 0;
  direction_t next_move = DIR_LEFT;

  if (equal_positions(last_pos, (position_t) INVALID_POSITION)) 
    last_pos = defender_position;
  else if (equal_positions(last_pos, defender_position)){ // Check if player did not move
  	next_move = get_next_dir_random_deffender((direction_t) DIR_LEFT, (direction_t) DIR_UP_LEFT, (direction_t) DIR_DOWN_LEFT);
  	while (next_move.i == last_move.i){
  		next_move = get_next_dir_random_deffender((direction_t) DIR_LEFT, (direction_t) DIR_UP_LEFT, (direction_t) DIR_DOWN_LEFT);
  	}
  }
  else {
  		next_move = get_next_dir_random_deffender((direction_t) DIR_LEFT, (direction_t) DIR_UP_LEFT, (direction_t) DIR_DOWN_LEFT);
  }
  srand(time(NULL));
  int random_number = rand()%5;
  if (random_number%5 == 0 && cheat_spy == 0){
	  next_move = change_next_move_if_needed(next_move, attacker_spy, defender_position);
	  cheat_spy += 1;
  }
  last_move = next_move;
  last_pos =  defender_position;
  // TODO: Implement Defender logic here
  return (direction_t) DIR_LEFT;
}

/*----------------------------------------------------------------------------*/
