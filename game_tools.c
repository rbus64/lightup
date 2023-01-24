#include "game_tools.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_random.h"

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_private.h"
#include "game_test.h"

static int valueCorr[255] = {
    ['b'] = S_BLANK,  ['0'] = S_BLACK0, ['1'] = S_BLACK1,    ['2'] = S_BLACK2, ['3'] = S_BLACK3,
    ['4'] = S_BLACK4, ['w'] = S_BLACKU, ['*'] = S_LIGHTBULB, ['-'] = S_MARK};

/* ************************************************************************** */

int _str2square2(char c)
{
  unsigned char uc = c;
  if (c == 'b')
    return S_BLANK;
  else
    return valueCorr[uc] == 0 ? -1 : valueCorr[uc];
}

game game_load(char* filename)
{
  FILE* fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "file doesn't exist!\n");
    exit(EXIT_FAILURE);
  }
  uint rows;
  uint cols;
  uint wrapping;

  if (fscanf(fp, "%d %d %d", &rows, &cols, &wrapping) != 3) {
    fclose(fp);
    fprintf(stderr, "Invalid format\n");
    exit(EXIT_FAILURE);
  }

  game g = game_new_empty_ext(rows, cols, wrapping);
  char c;

  for (uint i = 0; i < rows; i++) {
    uint error = fscanf(fp, "%c", &c);
    error = error;
    for (uint j = 0; j < cols; j++) {
      uint error1 = fscanf(fp, "%c", &c);
      error1 = error1;

      if (_str2square2(c) == -1) {
        game_delete(g);
        fclose(fp);
        fprintf(stderr, "Invalid format2\n");
        exit(EXIT_FAILURE);
      }
      game_set_square(g, i, j, _str2square2(c));
    }
  }
  fclose(fp);
  game_update_flags(g);
  return g;
}

void game_save(cgame g, char* filename)
{
  if (g == NULL) {
    printf("jeu inexistant");
  }
  int wrapping_number;
  uint nb_rows = game_nb_rows(g);
  uint nb_cols = game_nb_cols(g);
  bool wrapping = game_is_wrapping(g);
  if (wrapping) {
    wrapping_number = 1;
  } else {
    wrapping_number = 0;
  }
  FILE* fichier = NULL;
  fichier = fopen(filename, "w+");
  if (fichier == NULL) {
    printf("null");
  }
  fprintf(fichier, "%u %u %d\n", nb_rows, nb_cols, wrapping_number);

  for (uint i = 0; i < game_nb_rows(g); i++) {
    for (uint j = 0; j < game_nb_cols(g); j++) {
      if (game_get_state(g, i, j) == S_LIGHTBULB) {
        fprintf(fichier, "*");
      } else if (game_get_state(g, i, j) == S_BLANK) {
        fprintf(fichier, "b");
      } else if (game_get_state(g, i, j) == S_BLACKU) {
        fprintf(fichier, "w");
      } else if (game_get_state(g, i, j) == S_BLACK0) {
        fprintf(fichier, "0");
      } else if (game_get_state(g, i, j) == S_BLACK1) {
        fprintf(fichier, "1");
      } else if (game_get_state(g, i, j) == S_BLACK2) {
        fprintf(fichier, "2");
      } else if (game_get_state(g, i, j) == S_BLACK3) {
        fprintf(fichier, "3");
      } else if (game_get_state(g, i, j) == S_BLACK4) {
        fprintf(fichier, "4");
      }
    }
    fprintf(fichier, "\n");
  }
  fclose(fichier);
}

bool game_solve(game g)
{
  assert(g);
  uint solution_length = g->nb_cols * g->nb_rows;
  // Calulation of number of squares in square array.
  uint counter = 0;
  // counter is useless but necessairy for fonction call.
  bool isSolution = game_solve_aux(g, solution_length, 0, &counter, false);
  return isSolution;
}

uint game_nb_solutions(cgame g)
{
  assert(g);
  game copy = game_copy(g);
  assert(copy);
  uint solution_length = g->nb_cols * g->nb_rows;
  // Calulation of number of squares in square array.
  uint counter = 0;
  // Solution counter set to 0.
  game_solve_aux(copy, solution_length, 0, &counter, true);
  game_delete(copy);
  // Deleting clone of game.
  return counter;
}

bool game_solve_aux(game g, uint game_length, uint pos, uint* count, bool counting)
{
  // Inital and at each call, checking for errors, if errors ends recurisive branch.
  if (full_game_has_error(g)) {
    return false;
  }

  // Translation of pos to x and y coordinates.
  uint x = pos % g->nb_cols;
  uint y = pos / g->nb_cols;

  // Checks all playable sqaures are full.
  if (pos == game_length) {
    if (game_is_over(g) == true)
    // If the game is won (adds to counter if counting) and returns true;
    {
      if (counting) (*count)++;
      // adds to pointer counting the number of solutions
      return true;
    } else
      return false;
    // if the game isn't won, end recurrisive branch by returning false;
  }
  if (game_check_move(g, x, y, S_LIGHTBULB))
  // checking for valid move, if possible plays otherwise passes
  {
    game_set_square(g, x, y, S_LIGHTBULB);
    game_update_flags(g);
    // verifing if is first solution(if not counting ends fonctions and all other recursive branches returns true
    if (game_solve_aux(g, game_length, pos + 1, count, counting) &&
        !counting)  // verifing if is first solution(if not counting ends fonctions and all other recursive branches
                    // returns true)
      return true;
  }
  if (game_check_move(g, x, y, S_BLANK))
  // checking for valid move, if possible plays otherwise passes
  {
    game_set_square(g, x, y, S_BLANK);
    game_update_flags(g);
    if (game_solve_aux(g, game_length, pos + 1, count, counting) && !counting) return true;
  } else {
    if (game_solve_aux(g, game_length, pos + 1, count, counting) && !counting) return true;
    // if no moves are possible we only cast 1 recurisive branch that is just advancing;
  }
  return false;
  // at the end of all recurrisive branches to end fonctions once all possiblies are explored.
}

bool full_game_has_error(game g)
// checks all squares in square array for errors.
{
  assert(g);
  for (uint i = 0; i < game_nb_rows(g); i++) {
    for (uint j = 0; j < game_nb_cols(g); j++) {
      if (game_has_error(g, i, j)) return true;
    }
  }
  return false;
}