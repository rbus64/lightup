
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_ext.h"

game game_random(uint nb_rows, uint nb_cols, bool wrapping, uint nb_walls, bool with_solution);