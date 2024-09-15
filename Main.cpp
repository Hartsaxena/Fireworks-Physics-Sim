#include <iostream>
#include <vector>
#include <SDL.h>
#include "particle.h"
#include "simulation.h"
#include "renderer.h"

#define SCRWIDTH 1280
#define SCRHEIGHT 800

// Lets us write, e.g., cout << endl; instead of std::cout << std::endl;
using namespace std;

int main(int argc, char* argv[])
{
    Renderer renderer = Renderer(SCRWIDTH, SCRHEIGHT);
    std::cout << "Finding a good viewing location... \n";
    Position mousePosition;
    Simulation sim = Simulation(SCRWIDTH, SCRHEIGHT, &renderer);
    std::cout << "Setting up fireworks...\n";

    SDL_Event* event = new SDL_Event;
    std::cout << "Scheduling dates...\n";

    std::cout << "\nThe Fireworks are ready!\n";
    std::cout << "Press any key on the window to begin!\n";
    bool isRunning = true;
    while (isRunning) {

        /* Pool SDL Events. I normally like to have this in a renderer or frontEnd class,
        * But I'm being lazy here again.
        */
        while (SDL_PollEvent(event) > 0) {
            switch (event->type) {

                case SDL_QUIT: {
                    isRunning = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    mousePosition = renderer.getMousePosition();
                    sim.addFirework(mousePosition.x, mousePosition.y);
                    break;
                }
            }
        }
        
        // Blank the screen
        renderer.fillWindow(0, 0, 0);

        // Update + Render particles
        sim.tick();

        // Update our changes
        renderer.refreshWindow();
        // Delay 10ms.  Could be longer, could be shorter; will affect the speed and smoothness of the particles.
        SDL_Delay(10);
    }

    delete event; // Clean up heap
    SDL_Quit();
    return 0;
}