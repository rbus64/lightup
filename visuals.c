// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "visuals.h"

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "game_random.h"
#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_private.h"
#include "game_test.h"
#include "game_tools.h"
#include <time.h>

/* ***************************************************************** */
/* initialisation of end message box*/
const SDL_MessageBoxButtonData buttons[] = {
    {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "replay"},
    {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "exit"},
};
const SDL_MessageBoxData messageboxdata = {
    SDL_MESSAGEBOX_INFORMATION,                   /* .flags */
    NULL,                                         /* .window */
    "!!!GAGNEEEE!!!",                             /* .title */
    "VOUS AVEZ GAGNEZ \nQUE VOULEZ VOUS FAIRE ?", /* .message */
    SDL_arraysize(buttons),                       /* .numbuttons */
    buttons,                                      /* .buttons */
    NULL                                          /* .colorScheme */
};
/*initialisation of menu box*/



struct Env_t {
  int windows_width, window_height;
  int case_x, case_y;

  SDL_Texture* marked;
  SDL_Texture* error;
  SDL_Texture* wallu;
  SDL_Texture* wall1;
  SDL_Texture* wall2;
  SDL_Texture* wall3;
  SDL_Texture* wall4;
  SDL_Texture* background;
  SDL_Texture* night_lamp;
  SDL_Texture* floor_1;
  SDL_Texture* lighted;
  SDL_Texture* undo;
  SDL_Texture* redo;
  SDL_Texture* exit;
  SDL_Texture* save;
  SDL_Texture* solve;
  SDL_Texture* restart;
  SDL_Texture* help;
  SDL_Texture* wall0;
  SDL_Texture* monster;
  SDL_Texture* flag_marked;
  SDL_Texture* titre;
};

/* **************************************************************** */
/*gere la message box menu*/
void menu(game* g)
{

  srand(time(NULL));  // initialize radom seed with current time
  *g = game_random(7, 7, false, 10, false);

}

/* **************************************************************** */
Env* init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[], game* g)
{
  if (argc == 2) {
    *g = game_load(argv[1]);
  }

  else {
    menu(g);
  }

  Env* env = malloc(sizeof(struct Env_t));

  /* PUT YOUR CODE HERE TO INIT TEXTURES, ... */

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  env->case_x = w / 4;
  env->case_y = h / 4;

  /*init img*/

  env->error = IMG_LoadTexture(ren, "error.png");
  if (!env->error) ERROR("IMG_LoadTexture: %s\n", "error.png");
  env->marked = IMG_LoadTexture(ren, "marked.png");
  if (!env->marked) ERROR("IMG_LoadTexture: %s\n", "marked.png");
  env->wall1 = IMG_LoadTexture(ren, "wall1.png");
  if (!env->wall1) ERROR("IMG_LoadTexture: %s\n", "wall1.png");
  env->wall2 = IMG_LoadTexture(ren, "wall2.png");
  if (!env->wall2) ERROR("IMG_LoadTexture: %s\n", "wall2.png");
  env->wall3 = IMG_LoadTexture(ren, "wall3.png");
  if (!env->wall3) ERROR("IMG_LoadTexture: %s\n", "wall3.png");
  env->wall4 = IMG_LoadTexture(ren, "wall4.png");
  if (!env->wall4) ERROR("IMG_LoadTexture: %s\n", "wall4.png");
  env->wallu = IMG_LoadTexture(ren, "wallu.png");
  if (!env->wallu) ERROR("IMG_LoadTexture: %s\n", "wallu.png");
  env->night_lamp = IMG_LoadTexture(ren, "night_light.png");
  if (!env->night_lamp) ERROR("IMG_LoadTexture: %s\n", "night_light.png");
  env->floor_1 = IMG_LoadTexture(ren, "wood_floor_1.png");
  if (!env->floor_1) ERROR("IMG_LoadTexture: %s\n", "wood_floor_1.png");
  env->lighted = IMG_LoadTexture(ren, "lighted_floor.png");
  if (!env->lighted) ERROR("IMG_LoadTexture: %s\n", "lighted_floor.png");
  env->background = IMG_LoadTexture(ren, "background.png");
  if (!env->background) ERROR("IMG_LoadTexture: %s\n", "background.png");
  env->undo = IMG_LoadTexture(ren, "undo.png");
  if (!env->undo) ERROR("IMG_LoadTexture: %s\n", "undo.png");
  env->redo = IMG_LoadTexture(ren, "redo.png");
  if (!env->redo) ERROR("IMG_LoadTexture: %s\n", "redo.png");
  env->save = IMG_LoadTexture(ren, "save.png");
  if (!env->save) ERROR("IMG_LoadTexture: %s\n", "save.png");
  env->exit = IMG_LoadTexture(ren, "exit.png");
  if (!env->exit) ERROR("IMG_LoadTexture: %s\n", "exit.png");
  env->solve = IMG_LoadTexture(ren, "solve.png");
  if (!env->solve) ERROR("IMG_LoadTexture: %s\n", "solve.png");
  env->restart = IMG_LoadTexture(ren, "restart.png");
  if (!env->restart) ERROR("IMG_LoadTexture: %s\n", "restart.png");
  env->help = IMG_LoadTexture(ren, "help.png");
  if (!env->help) ERROR("IMG_LoadTexture: %s\n", "help.png");
  env->wall0 = IMG_LoadTexture(ren, "wall0.png");
  if (!env->wall0) ERROR("IMG_LoadTexture: %s\n", "wall0.png");
  env->monster = IMG_LoadTexture(ren, "monster_01.png");
  if (!env->monster) ERROR("IMG_LoadTexture: %s\n", "monster_01.png");
  env->flag_marked = IMG_LoadTexture(ren, "flag_pressed.png");
  if (!env->flag_marked) ERROR("IMG_LoadTexture: %s\n", "flag_pressed.png");
  env->titre = IMG_LoadTexture(ren, "title.png");
  if (!env->titre) ERROR("IMG_LoadTexture: %s\n", "title.png");
  return env;
}

int nb_of_blank(game g)
{
  int cpt = 0;
  for (uint y = 0; y < game_nb_rows(g); y++) {
    for (uint x = 0; x < game_nb_cols(g); x++) {
      if (game_is_blank(g, y, x) && !game_is_lighted(g, y, x)) {
        cpt++;
      }
    }
  }
  return cpt;
}

/* **************************************************************** */

void render(SDL_Window* win, SDL_Renderer* ren, Env* env, game g, bool* isMarking)
{
  SDL_Rect rect;
  int cpt = 0;
  int result = nb_of_blank(g);
  int nb_blank = 0;
  if (result > 2) {
    nb_blank = (rand() % result);
  }

  uint g_rows = game_nb_rows(g);
  uint g_cols = game_nb_cols(g);

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  int min = min(w, h);
  SDL_RenderCopy(ren, env->background, NULL, NULL);
  for (uint y = 0; y < g_rows; y++) { /*rendering of game grid with specific textures*/
    for (uint x = 0; x < g_cols; x++) {
      if (w > h) { /* calculation of smallest dimesion to assure the game stay squares*/
        env->case_x = ((min / 4) + (x * (min / 2) / g_cols)) + (w - h) / 2; /* creating sqaure size in grid */
        env->case_y = (h / 4) + (y * (h / 2 / g_rows));
      } else {
        env->case_y = ((min / 4) + (y * (min / 2) / g_rows)) + (h - w) / 2;
        env->case_x = (w / 4) + (x * (w / 2 / g_cols));
      }
      if (game_is_marked(g, y, x)) {
        SDL_QueryTexture(env->marked, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->marked, NULL, &rect); /* rendering of texture for maked flags*/
      } else if (game_is_lightbulb(g, y, x)) {
        SDL_QueryTexture(env->lighted, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->lighted, NULL, &rect); /* rendering of texture lighted squares*/
        SDL_QueryTexture(env->night_lamp, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->night_lamp, NULL, &rect); /* rendering of texture for lamps*/
      } else if (game_is_lighted(g, y, x)) {
        SDL_QueryTexture(env->lighted, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->lighted, NULL, &rect); /* rendering of texture lighted textures*/
      } else if (game_is_blank(g, y, x)) {
        SDL_QueryTexture(env->floor_1, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->floor_1, NULL, &rect); /* rendering of texture of floor (blanks)*/
        if (cpt == nb_blank && result > 2) {
          SDL_QueryTexture(env->monster, NULL, NULL, &rect.w, &rect.h);
          rect.x = env->case_x;
          rect.y = env->case_y;
          rect.h = min / 2 / g_rows;
          rect.w = min / 2 / g_cols;
          SDL_RenderCopy(ren, env->monster, NULL, &rect); /* rendering of texture of the monster */
        }
        cpt++;
      } else if (game_get_state(g, y, x) == S_BLACKU) {
        SDL_QueryTexture(env->wallu, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->wallu, NULL, &rect); /* rendering of texture of wallu*/
      } else if (game_get_state(g, y, x) == S_BLACK0) {
        SDL_QueryTexture(env->wall0, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->wall0, NULL, &rect); /* rendering of texture of wall0*/
      } else if (game_get_state(g, y, x) == S_BLACK1) {
        SDL_QueryTexture(env->wall1, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->wall1, NULL, &rect); /* rendering of texture of wall1*/
      } else if (game_get_state(g, y, x) == S_BLACK2) {
        SDL_QueryTexture(env->wall2, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->wall2, NULL, &rect); /* rendering of texture of wall2*/
      } else if (game_get_state(g, y, x) == S_BLACK3) {
        SDL_QueryTexture(env->wall3, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->wall3, NULL, &rect); /* rendering of texture of wall3*/
      } else if (game_get_state(g, y, x) == S_BLACK4) {
        SDL_QueryTexture(env->wall4, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->wall4, NULL, &rect); /* rendering of texture of wall4*/
      }
      if (game_has_error(g, y, x)) {
        SDL_QueryTexture(env->error, NULL, NULL, &rect.w, &rect.h);
        rect.x = env->case_x;
        rect.y = env->case_y;
        rect.h = min / 2 / g_rows;
        rect.w = min / 2 / g_cols;
        SDL_RenderCopy(ren, env->error, NULL, &rect); /* rendering of texture of error flag*/
      }
    }

    /*Rendering of the tool buttons on bottom of screen */
    env->case_x = (w / 10); /* sectioning out window to create emplacement for buttons */
    env->case_y = (h / 5) * 4;
    SDL_QueryTexture(env->undo, NULL, NULL, &rect.w, &rect.h);
    rect.x = env->case_x;
    rect.y = env->case_y;
    rect.h = min / 12;
    rect.w = min / 12;
    SDL_RenderCopy(ren, env->undo, NULL, &rect); /* rendering of texture of undo button*/
    env->case_x = env->case_x + w / 10;
    SDL_QueryTexture(env->redo, NULL, NULL, &rect.w, &rect.h);
    rect.x = env->case_x;
    rect.y = env->case_y;
    rect.h = min / 12;
    rect.w = min / 12;
    SDL_RenderCopy(ren, env->redo, NULL, &rect); /* rendering of texture of redo button*/
    env->case_x = env->case_x + w / 10;
    if (*isMarking) {
      SDL_QueryTexture(env->flag_marked, NULL, NULL, &rect.w, &rect.h);
      rect.x = env->case_x;
      rect.y = env->case_y;
      rect.h = min / 12;
      rect.w = min / 12;
      SDL_RenderCopy(ren, env->flag_marked, NULL, &rect); /* rendering of texture of marking_toggle_on button*/
    } else {
      SDL_QueryTexture(env->marked, NULL, NULL, &rect.w, &rect.h);
      rect.x = env->case_x;
      rect.y = env->case_y;
      rect.h = min / 12;
      rect.w = min / 12;
      SDL_RenderCopy(ren, env->marked, NULL, &rect); /* rendering of texture of marking_toggle_off button*/
    }
    env->case_x = env->case_x + w / 10;
    SDL_QueryTexture(env->restart, NULL, NULL, &rect.w, &rect.h);
    rect.x = env->case_x;
    rect.y = env->case_y;
    rect.h = min / 12;
    rect.w = min / 12;
    SDL_RenderCopy(ren, env->restart, NULL, &rect); /* rendering of texture of restart button*/
    env->case_x = env->case_x + w / 10;
    SDL_QueryTexture(env->help, NULL, NULL, &rect.w, &rect.h);
    rect.x = env->case_x;
    rect.y = env->case_y;
    rect.h = min / 12;
    rect.w = min / 12;
    SDL_RenderCopy(ren, env->help, NULL, &rect); /* rendering of texture of help button*/
    env->case_x = env->case_x + w / 10;
    SDL_QueryTexture(env->solve, NULL, NULL, &rect.w, &rect.h);
    rect.x = env->case_x;
    rect.y = env->case_y;
    rect.h = min / 12;
    rect.w = min / 12;
    SDL_RenderCopy(ren, env->solve, NULL, &rect); /* rendering of texture of solve button*/
    env->case_x = env->case_x + w / 10;
    SDL_QueryTexture(env->save, NULL, NULL, &rect.w, &rect.h);
    rect.x = env->case_x;
    rect.y = env->case_y;
    rect.h = min / 12;
    rect.w = min / 12;
    SDL_RenderCopy(ren, env->save, NULL, &rect); /* rendering of texture of save button*/
    env->case_x = env->case_x + w / 10;
    SDL_QueryTexture(env->exit, NULL, NULL, &rect.w, &rect.h);
    rect.x = env->case_x;
    rect.y = env->case_y;
    rect.h = min / 12;
    rect.w = min / 12;
    SDL_RenderCopy(ren, env->exit, NULL, &rect); /* rendering of texture of exit button*/
  }

  SDL_QueryTexture(env->titre, NULL, NULL, &rect.w, &rect.h);
  rect.w = min / 2;
  rect.h = min / 8;
  rect.x = w / 2 - rect.w / 2;
  rect.y = h / 12;
  SDL_RenderCopy(ren, env->titre, NULL, &rect); /* rendering of texture the title sprite on top of the game grid*/
}

/* **************************************************************** */

bool process(SDL_Window* win, SDL_Renderer* ren, SDL_Event* e, Env* env, game g, bool* isMarking)
{
  int w, h;
  /*recupération de la taille de la page*/
  SDL_GetWindowSize(win, &w, &h);
  /*minimun entre la largeur et la hauteur*/
  int min = min(w, h);
  int posx, posy;
  /*definition de la position de la grille*/
  if (w > h) {
    posx = (min / 4) + (w - h) / 2;
    posy = (h / 4);
  } else {
    posy = (min / 4) + (h - w) / 2;
    posx = (w / 4);
  }
  if (e->type == SDL_QUIT) {
    return true;
  }
  /*affichage du message quand le jeu est gagné*/
  
#ifdef __ANDROID__

  if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y); /*recup des coordonnées de la souris*/
    if (mouse.x > posx && mouse.x < (w - posx) &&
        (mouse.y > posy && mouse.y < h - posy)) { /*test si le clic est dans la grille*/
      /*defini quel colone et quel ligne*/
      int mouse_x = ((mouse.x - posx) / (min / 2 / game_nb_cols(g)));
      int mouse_y = ((mouse.y - posy) / (min / 2 / game_nb_rows(g)));
      /*regarde si le bouton marked est enfonce*/
      if (*isMarking == false) {
        if (!game_is_lightbulb(g, mouse_y, mouse_x) && game_check_move(g, mouse_y, mouse_x, S_LIGHTBULB) &&
            !full_game_has_error(g)) { /*si pas d'erreur et que le coup est possible et que la case n'est pas deja
                                          allume alors play_move*/
          game_play_move(g, mouse_y, mouse_x, S_LIGHTBULB);
          if (game_is_over(g)) {
            render(win, ren, env, g, isMarking);
          }
        } else {
          if (game_get_state(g, mouse_y, mouse_x) == S_LIGHTBULB ||
              game_get_state(g, mouse_y, mouse_x) == S_MARK) { /*si case deja lightbulb play_move blank*/
            game_play_move(g, mouse_y, mouse_x, S_BLANK);
          } else if (full_game_has_error(g)) { /*affichage d'une fenetre erreur avant de pouvoir rejouer*/
            int error = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ERROR",
                                                 "VOUS AVEZ UNE ERREUR CORRIGER LA AVANT DE CONTINUER ", NULL);
            (void)error;
          }
        }
      } else {
        if (game_get_state(g, mouse_y, mouse_x) == S_MARK) { /*si la case est deja marked play_move blank*/
          game_play_move(g, mouse_y, mouse_x, S_BLANK);
        } else if (game_check_move(g, mouse_y, mouse_x, S_MARK) == true) { /*play_move blank*/
          game_play_move(g, mouse_y, mouse_x, S_MARK);
        }
      }
    }
    /*gere les boutons du bas*/
    else if ((mouse.y > (h / 5) * 4) && (mouse.y < ((h / 5) * 4) + h / 12)) {
      int mouse_x = (mouse.x / (w / 10));
      /*colone 1 pour le bouton undo*/
      if (mouse_x == 1) {
        game_undo(g);
      }
      /*colone 2 pour le bouton redo*/
      else if (mouse_x == 2) {
        game_redo(g);
      }
      /*colone 3 pour le bouton qui defini si on place une mark ou un lightbulb*/
      else if (mouse_x == 3) {
        if (*isMarking == true) {
          *isMarking = false;
        } else {
          *isMarking = true;
        }
      }
      /*colone 4 pour le bouton restart*/
      else if (mouse_x == 4) {
        game_restart(g);
      }
      /*colone 5 pour le bouton help*/
      else if (mouse_x == 5) {
        int reussite = SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_INFORMATION, "HELP",
            "Welcome to Lightup !\n To win the game, you must light up with night-lights all the dark squares, to "
            "get rid of the uncatchable monster!\n Remember a night-light can not face one another!\n You must respect "
            "the number of night-lights written on the walls!\nYou have a number of tools at your disposal\n\n"
            "| undo | redo | toggle flag | restart | help | auto - solve | save | exit |\n\nGood "
            "luck!!!\n ",
            NULL);
        (void)reussite;
      }
      /*colone 6 pour le bouton solve*/
      else if (mouse_x == 6) {
        game_restart(g);
        game_solve_aux(g, g->nb_cols * g->nb_rows, 0, NULL, NULL);
        render(win, ren, env, g, isMarking);
      }
      /*colone 7 pour le bouton save*/
      else if (mouse_x == 7) {
        printf("save in test.txt");
        game_save(g, "test");
      }
      /*colone 8 pour le bouton exit*/
      else if (mouse_x == 8) {
        int exit = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "EXIT", "WHAT A SHAME YOU GAVE UP :-(", NULL);
        (void)exit;
        return true;
      }
    }
  }
#endif
  if (game_is_over(g)) {
    render(win, ren, env, g, isMarking);
    render(win, ren, env, g, isMarking);
    SDL_Delay(500);
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
      SDL_Log("error displaying message box");
      return 1;
    }
    if (buttonid == -1) {
      SDL_Log("no selection");
    } else if (buttonid == 0) {
      game_restart(g);
    } else {
      return true;
    }
  }

  return false;
}

/* ********************************************************************** */

void clean(Env* env)
{
  /* Cleans the env of all used textures */
  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->flag_marked);
  SDL_DestroyTexture(env->error);
  SDL_DestroyTexture(env->exit);
  SDL_DestroyTexture(env->floor_1);
  SDL_DestroyTexture(env->help);
  SDL_DestroyTexture(env->lighted);
  SDL_DestroyTexture(env->marked);
  SDL_DestroyTexture(env->night_lamp);
  SDL_DestroyTexture(env->redo);
  SDL_DestroyTexture(env->restart);
  SDL_DestroyTexture(env->save);
  SDL_DestroyTexture(env->solve);
  SDL_DestroyTexture(env->undo);
  SDL_DestroyTexture(env->wall0);
  SDL_DestroyTexture(env->wall1);
  SDL_DestroyTexture(env->wall2);
  SDL_DestroyTexture(env->wall3);
  SDL_DestroyTexture(env->wall4);
  SDL_DestroyTexture(env->wallu);
  SDL_DestroyTexture(env->titre);
  SDL_DestroyTexture(env->monster);

  free(env); /* frees the env struct */
}

/* **************************************************************** */
