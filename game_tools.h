/**
 * @file game_tools.h
 * @brief Game Tools.
 * @details See @ref index for further details.
 * @copyright University of Bordeaux. All rights reserved, 2021.
 *
 **/

#ifndef __GAME_TOOLS_H__
#define __GAME_TOOLS_H__
#include <stdbool.h>
#include <stdio.h>

#include "game.h"

/**
 * @name Game Tools
 * @{
 */

/**
 * @brief Creates a game by loading its description from a text file.
 * @details See the file format description in @ref index.
 * @param filename input file
 * @return the loaded game
 **/
game game_load(char* filename);

/**
 * @brief Saves a game in a text file.
 * @details See the file format description in @ref index.
 * @param g game to save
 * @param filename output file
 **/
void game_save(cgame g, char* filename);

/**
 * @brief Computes the solution of a given game
 * @param g the game to solve
 * @details The game @p g is updated with the first solution found. If there are
 * no solution for this game, @p g must be unchanged.
 * @return true if a solution is found, false otherwise
 */
bool game_solve(game g);

/**
 * @brief Computes the total number of solutions of a given game.
 * @param g the game
 * @details The game @p g must be unchanged.
 * @return the number of solutions
 */
uint game_nb_solutions(cgame g);

/**
 * @brief Computes the total number of solutions of a given game.
 * @param g the game
 * @details The game @p g must be unchanged.
 * @return the number of solutions
 */
uint game_nb_solutions(cgame g);

/**
 * @brief Auxiliary fonction for game_solve and game_nb_solutions.
 * @param g the game
 * @param game_length number of squares in square array from g.
 * @param pos current pos in sqaure array.
 * @param count pointer used for counting number of solutions of g.
 * @param counting bool for counting condition.


 * @details The game @p g must be unchanged.
 * @return the number of solutions
 */
bool game_solve_aux(game g, uint game_length, uint pos, uint* count, bool counting);

bool full_game_has_error(game g);

#endif  // __GAME_TOOLS_H__
