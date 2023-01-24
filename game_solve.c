#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_private.h"
#include "game_test.h"
#include "game_tools.h"

int main(int argc, char* argv[])
{
  if (argc < 3) {
    printf("too little arguments !\n");
    return EXIT_FAILURE;
  }
  char* filename = NULL;
  if (argc == 3) {
    filename = "default.txt";
  } else if (argc >= 4) {
    filename = argv[3];
  }

  game user_game = game_load(argv[2]);
  if (strcmp("-s", argv[1]) == 0) {
    if (game_solve(user_game)) {
      game_save(user_game, filename);
    } else {
      game_delete(user_game);
      return EXIT_FAILURE;
    }
  } else if (strcmp("-c", argv[1]) == 0) {
    FILE* file = fopen(filename, "w");
    uint nb_solutions = game_nb_solutions(user_game);
    fprintf(file, "%u\n", nb_solutions);
    fclose(file);
  }
  game_delete(user_game);
  return EXIT_SUCCESS;
}