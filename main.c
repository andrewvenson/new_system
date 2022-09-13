#include <stdio.h> /* printf and fprintf */

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

void quitGame(SDL_Window *window, int *game){
    printf("This the game right here %d", game);

    *game = 0;
    /* Pauses all SDL subsystems for a variable amount of milliseconds */
    //SDL_Delay(DELAY);

    /* Frees memory */
    SDL_DestroyWindow(window);

    /* Shuts down all SDL subsystems */
    SDL_Quit(); 

}

int main (int argc, char **argv)
{

    const int QUIT_CODE = 113;
    /* Initialises data */
    SDL_Window *window = NULL;
    SDL_Event event;

    int game = 0;
    int *pGame;
    pGame = &game;

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
        game = 1;
    }

    while(game==1){
        if(SDL_PollEvent(&event)){
            switch(event.type){
                    case SDL_KEYDOWN:
                        printf("Key down detected: %d\n", event.key.keysym.sym);
                        break;
                    case SDL_KEYUP:
                        printf("Key up detected: %d\n", event.key.keysym.sym);
                        if(event.key.keysym.sym == QUIT_CODE){
                            quitGame(window, pGame);
                        }
                        break;
                    default:
                        break;
            }
        }
    }

  printf("World ended\n");
  return 0;
}
