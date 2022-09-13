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

void quitGame(SDL_Window *window, SDL_Renderer *renderer, int *game){
    /* Frees memory */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /* Shuts down all SDL subsystems */
    SDL_Quit(); 
    *game = 0;
}

int main (int argc, char **argv)
{
    const int QUIT_CODE = 113;
    /* Initialises data */
    SDL_Window *window = NULL;
    SDL_Event event;
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Rect rect2;

    rect.x = 20;
    rect.y = 20;
    rect.w = 50;
    rect.h = 50;

    rect2.x = 0;
    rect2.y = 0;
    rect2.w = 50;
    rect2.h = 50;

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
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    /* Checks if renderer has been created; if not, exits program */
    if (renderer == NULL) {
        fprintf(stderr, "SDL renderer failed creation: %s\n", SDL_GetError());
        return 1;
    }



    /* Select the color for drawing. It is set to red here. */
    //Sky blue color 
    SDL_SetRenderDrawColor(renderer, 0, 181, 226, 255);

    /* Clear the entire screen to our selected color. */
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_RenderDrawRect(renderer, &rect2);

    SDL_RenderDrawLine(renderer, 0, 0, 20, 20);
    SDL_RenderDrawLine(renderer, 50, 0, 70, 20);
    SDL_RenderDrawLine(renderer, 0, 50, 20, 70);
    SDL_RenderDrawLine(renderer, 50, 50, 70, 70);

    /*
    SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
    SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
    */

    /* Up until now everything was drawn behind the scenes.
       This will show the new, red contents of the window. */
    SDL_RenderPresent(renderer);

    game = 1;

    while(game==1){
        if(SDL_PollEvent(&event)){
            switch(event.type){
                    case SDL_KEYDOWN:
                        printf("Key down detected: %d\n", event.key.keysym.sym);
                        break;
                    case SDL_KEYUP:
                        printf("Key up detected: %d\n", event.key.keysym.sym);
                        if(event.key.keysym.sym == QUIT_CODE){
                            quitGame(window, renderer, pGame);
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
