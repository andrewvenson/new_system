#include <stdio.h> /* printf and fprintf */
#include <stdbool.h>

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

void quitGame(SDL_Window *window){
  /* Pauses all SDL subsystems for a variable amount of milliseconds */
  SDL_Delay(DELAY);

  /* Frees memory */
  SDL_DestroyWindow(window);
  
  /* Shuts down all SDL subsystems */
  SDL_Quit(); 
}

int main (int argc, char **argv)
{
  /* Initialises data */
  SDL_Window *window = NULL;
  SDL_Event event;
  bool game = false;
  
  /*
  * Initialises the SDL video subsystem (as well as the events subsystem).
  * Returns 0 on success or a negative error code on failure using SDL_GetError().
  */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  /* Creates a SDL window */
  window = SDL_CreateWindow("New World", /* Title of the SDL window */
			    SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
			    SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
			    WIDTH, /* Width of the window in pixels */
			    HEIGHT, /* Height of the window in pixels */
			    0); /* Additional flag(s) */

  /* Checks if window has been created; if not, exits program */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
  }else{
      game = true;
  }

  while(game){
      while(SDL_PollEvent(&event)){
          switch(event.type){
              case SDL_KEYDOWN:
                  printf("Key down detected");
                  break;
                case SDL_KEYUP:
                  printf("Key up detected");
                  quitGame(window, game);
                  break;
                default:
                  break;
          }
      }
  }
  
  return 0;
}
