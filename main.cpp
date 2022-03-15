#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<string>
using namespace std;

//Dimension and name
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string screenTitle = "Chess' Known Battleground";

//Create Window, Renderer, etc...
//SDL_Window* mainWindow = NULL;
//SDL_Renderer* mainRender = NULL;

//Start SDL and check for error
void createAndCheckError(SDL_Window* &window, SDL_Renderer* &renderer);

//Close the game and free everything
void closeTheGame(SDL_Window* window, SDL_Renderer* renderer);

//Print the Error and close the Game
void logSDLError(std::ostream& os,const string& msg, bool fatal = false);

//Draw the template of the gameplay
void mainTemplate(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* argv[]) {
    SDL_Window* mainWindow = NULL;
    SDL_Renderer* mainRender = NULL;
    //Create Window, check Error
    createAndCheckError(mainWindow,mainRender);

    //The event begin
    SDL_Event mainEvent;

    //Bool quit flag
    bool quit=false;

    mainTemplate(mainWindow,mainRender);
    while(!quit) {
        while(SDL_PollEvent(&mainEvent)!=0) {
            if (mainEvent.type==SDL_QUIT) quit=true;
        }
        mainTemplate(mainWindow,mainRender);
    }

    closeTheGame(mainWindow,mainRender);
    return 0;
}

void createAndCheckError(SDL_Window* &window, SDL_Renderer* &renderer) {
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0 ) {
            logSDLError(std::cout, "SDL Init",true);
            return;
    }

    //Create Window
    window = SDL_CreateWindow(screenTitle.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window==nullptr) {
        logSDLError(std::cout, "SDL Window ",true);
        return;
    }

    //Create Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer==nullptr) {
        logSDLError(std::cout, "SDL Window ",true);
        return;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void logSDLError(std::ostream& os,const string& msg, bool fatal) {
    os << msg << "SDL Error Detected: "<< SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void closeTheGame(SDL_Window* window,SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}

void mainTemplate(SDL_Window* window, SDL_Renderer* gRenderer) {
    SDL_SetRenderDrawColor( gRenderer, 0xAA, 0x00, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );
    //Render red filled quad
    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( gRenderer, &fillRect );

    //Render green outlined quad
    SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRect( gRenderer, &outlineRect );

    //Draw blue horizontal line
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
    SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

    //Draw vertical line of yellow dots
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
    for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
    {
        SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
    }

    //Update screen
    SDL_RenderPresent( gRenderer );
}
