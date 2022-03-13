#include<iostream>
#include<dll/SDL.h>
#include<dll/SDL_image.h>
#include<dll/SDL_mixer.h>
#include<string>
using namespace std;

//Dimension and name
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string screenTitle = "Chess' Known Battleground";

//Create Window, Renderer, etc...
SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRender = NULL;

//Start SDL and check for error
void createAndCheckError(SDL_Window* window, SDL_Renderer* renderer);

//Close the game and free everything
void closeTheGame(SDL_Window* window, SDL_Renderer* renderer);

//Cout the Error and close the Game
void logSDLError(std::ostream& os, string& msg, bool fatal = false);

int main() {
    createAndCheckError(mainWindow,mainRender);
    closeTheGame(mainWindow,mainRender);
    return 0;
}

void createAndCheckError(SDL_Window* window, SDL_Renderer* renderer) {
    //Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
            logSDLError(cout, "SDL Init ",true);
            return;
    }

    //Create Window
    window = SDL_CreateWindow(screenTitle, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window==nullptr) {
        logSDLError(cout, "SDL Window ",true);
        return;
    }

    //Create Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer==nullptr) {
        logSDLError(cout, "SDL Window ",true);
        return;
    }


}

void logSDLError(std::ostream& os, string& msg, bool fatal) {
    os << "SDL Error Detected: " << msg << SDL_Error() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void closeTheGame(SDL_Window* window,SDL_renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}
