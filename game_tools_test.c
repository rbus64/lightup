/**
 * @file game_tools_test.c
 * @brief Game tools test.
 * @copyright University of Bordeaux. All rights reserved, 2021.
 *
 **/

#include "game_tools.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_examples.h"
#include "game_ext.h"
#include "game_test.h"

/* ************************************************************************** */
/*                            BASIC TESTS (game_tools)                        */
/* ************************************************************************** */

int test_load(void)
{
  char* name = "test_fct";
  game_save(game_default(), name);
  game test_comp = game_load(name);
  if (game_equal(game_default(), test_comp)) return EXIT_SUCCESS;
  return EXIT_FAILURE;
}

int test_save(void)
{
  game g1 = game_default();
  char* c1 = "test1";
  game_save(g1, c1);
  game g3 = game_load(c1);
  bool test1 =
      ((game_equal(g1, g3)) && (game_nb_cols(g1) == game_nb_cols(g3)) && (game_nb_rows(g1) == game_nb_rows(g3)));
  game g2 = game_default_solution();
  char* c2 = "test2";
  game_save(g2, c2);
  game g4 = game_load(c2);
  bool test2 =
      ((game_equal(g2, g4)) && (game_nb_cols(g2) == game_nb_cols(g4)) && (game_nb_rows(g2) == game_nb_rows(g4)));
  if (test1 && test2) {
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}