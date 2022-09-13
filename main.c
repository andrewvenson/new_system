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

    game = 1;

    struct Cube {
        int width;
        int height;
        //First face
        int faceOneRectX;
        int faceOneRectY;
        //Second face
        int faceTwoRectX;
        int faceTwoRectY;

        int firstLineStartPointX;
        int firstLineStartPointY;

        int secondLineStartPointX;
        int secondLineStartPointY;

        int thirdLineStartPointX;
        int thirdLineStartPointY;

        int fourthLineStartPointX;
        int fourthLineStartPointY;

        int firstLineEndPointX;
        int firstLineEndPointY;
        int secondLineEndPointX;
        int secondLineEndPointY;
        int thirdLineEndPointX;
        int thirdLineEndPointY;
        int fourthLineEndPointX;
        int fourthLineEndPointY;
    };

    struct Cube cube;
    cube.width = 50;
    cube.height = 50;

    cube.faceOneRectX = 0;
    cube.faceOneRectY = 0;

    cube.faceTwoRectX = 20;
    cube.faceTwoRectY = 20;

    while(game==1){


        //Sets full screen to Sky blue color 
        SDL_SetRenderDrawColor(renderer, 0, 181, 226, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);


        if(SDL_PollEvent(&event)){
            switch(event.type){
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            // A key ~ means we going left
                            case 97: case 1073741904:
                                // += because the axis are flipped from traditional life lol
                                cube.faceOneRectX-=20;
                                cube.faceTwoRectX-=20;
                                break;
                            // D key ~ means we going right
                            case 100: case 1073741903:
                                // += because the axis are flipped from traditional life lol
                                cube.faceOneRectX+=20;
                                cube.faceTwoRectX+=20;
                                break;
                            // S key ~ means we going down
                            case 115: case 1073741905:
                                // += because the axis are flipped from traditional life lol
                                cube.faceOneRectY+=20;
                                cube.faceTwoRectY+=20;
                                break;
                            // W key ~ means we going up
                            case 119: case 1073741906:
                                // += because the axis are flipped from traditional life lol
                                cube.faceOneRectY-=20;
                                cube.faceTwoRectY-=20;
                                break;
                            default:
                                break;

                        }
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

        // Sets cube attributes
        cube.firstLineStartPointX = cube.faceOneRectX;
        cube.firstLineStartPointY = cube.faceOneRectY;
        cube.firstLineEndPointX = cube.faceTwoRectX;
        cube.firstLineEndPointY = cube.faceTwoRectY;

        cube.secondLineStartPointX = cube.faceOneRectX + cube.width;
        cube.secondLineStartPointY = cube.faceOneRectY;
        cube.secondLineEndPointX = cube.faceTwoRectX + cube.width;
        cube.secondLineEndPointY = cube.faceTwoRectY;

        cube.thirdLineStartPointX = cube.faceOneRectX;
        cube.thirdLineStartPointY = cube.faceOneRectY + cube.width;
        cube.thirdLineEndPointX = cube.faceTwoRectX;
        cube.thirdLineEndPointY = cube.faceTwoRectY + cube.height;

        cube.fourthLineStartPointX = cube.faceOneRectX + cube.width;
        cube.fourthLineStartPointY = cube.faceOneRectY + cube.height;
        cube.fourthLineEndPointX = cube.faceTwoRectX + cube.width;
        cube.fourthLineEndPointY = cube.faceTwoRectY + cube.height;

        rect.x = cube.faceOneRectX;
        rect.y = cube.faceOneRectY;
        rect.w = cube.width;
        rect.h = cube.height;

        rect2.x = cube.faceTwoRectX;
        rect2.y = cube.faceTwoRectY;
        rect2.w = cube.width;
        rect2.h = cube.height;

        // Sets cube fill color
        SDL_SetRenderDrawColor(renderer, 0, 83, 255, 255);
        // Draws cube faces
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect2);

        // Draws cube lines
        // Don't need to render this line as it's hidden by cube facesx
        SDL_RenderDrawLine(renderer, cube.fourthLineStartPointX, cube.fourthLineStartPointY, cube.fourthLineEndPointX, cube.fourthLineEndPointY);
        // Sets cube line color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, cube.firstLineStartPointX, cube.firstLineStartPointY, cube.firstLineEndPointX, cube.firstLineEndPointY);
        SDL_RenderDrawLine(renderer, cube.secondLineStartPointX, cube.secondLineStartPointY, cube.secondLineEndPointX, cube.secondLineEndPointY);
        SDL_RenderDrawLine(renderer, cube.thirdLineStartPointX, cube.thirdLineStartPointY, cube.thirdLineEndPointX, cube.thirdLineEndPointY);

        /* Up until now everything was drawn behind the scenes.
           This will show the new, red contents of the window. */
        SDL_RenderPresent(renderer);
    }

  printf("World ended\n");
  return 0;
}
