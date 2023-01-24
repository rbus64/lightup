// SDL2 Model by aurelien.esnard@u-bordeaux.fr

#ifndef MODEL_H
#define MODEL_H

#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_private.h"
#include "game_test.h"
#include "game_tools.h"

typedef struct Env_t Env;

/* **************************************************************** */

#ifdef __ANDROID__
#define PRINT(STR, ...)          \
  do {                           \
    SDL_Log(STR, ##__VA_ARGS__); \
  } while (0)
#define ERROR(STR, ...)          \
  do {                           \
    SDL_Log(STR, ##__VA_ARGS__); \
    exit(EXIT_FAILURE);          \
  } while (0)
#else
#define PRINT(STR, ...)         \
  do {                          \
    printf(STR, ##__VA_ARGS__); \
  } while (0)
#define ERROR(STR, ...)                  \
  do {                                   \
    fprintf(stderr, STR, ##__VA_ARGS__); \
    exit(EXIT_FAILURE);                  \
  } while (0)
#endif

/* **************************************************************** */

#define APP_NAME "LIGHT-UP"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define DELAY 100
#define min(a, b) (a <= b ? a : b)
/* **************************************************************** */

Env* init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[], game* g);
void render(SDL_Window* win, SDL_Renderer* ren, Env* env, game g, bool* isMarking);
void clean(Env* env);
bool process(SDL_Window* win, SDL_Renderer* ren, SDL_Event* e, Env* env, game g, bool* isMarking);
int nb_of_blank(game g);
void menu(game* g);

/* **************************************************************** */

/****************************************************************************/
#endif
