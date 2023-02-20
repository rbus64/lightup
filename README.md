# lightup-04b
## Rules

This game is a simple one-player puzzle, called *Light Up* in the
[Simon Tatham's Puzzle Collection](https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/lightup.html).

# Idée du jeu 

All art/sprites are OC. Created by the team.

Concept is based on light-up game.

To win the game, you must light up with night-lights all the dark squares, to get rid of the uncatchable monster.
A night-light can not face one another. You must respect the number of night-lights written on the walls.
The game will offer a number of tools for the player:
            | undo | redo | toggle flag | restart | help | auto - solve | save | exit |
            
##### Aux Tests (game_aux.h)

* game_print
* game_default
* game_default_solution

##### Basic Tests (game.h)

* game_new
* game_new_empty
* game_copy
* game_equal
* game_delete
* game_set_square
* game_get_square
* game_get_state
* game_get_flags
* game_is_blank
* game_is_lightbulb
* game_is_black
* game_get_black_number
* game_is_marked
* game_is_lighted
* game_has_error
* game_check_move
* game_play_move
* game_update_flags
* game_is_over
* game_restart

### Test V2

##### Ext Tests (game_ext.h)

* game_new_ext
* game_new_empty_ext
* game_nb_rows
* game_nb_cols
* game_is_wrapping
* game_undo
* game_redo

### Test Tools

##### Tools Tests (game_tools.h)

* game_load
* game_save
* game_solve
* game_nb_solutions
* game_solve_aux

# issues closes
game_load issue closed #1
game_save issue closed #2
