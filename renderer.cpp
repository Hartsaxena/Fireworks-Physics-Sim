#include <SDL.h>
#include <iostream>

#include "renderer.h"


Renderer::Renderer(int xDimension, int yDimension) {
	this->xDimension = xDimension;
	this->yDimension = yDimension;

    this->initialize();
}

int Renderer::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Could not initialize!" << SDL_GetError() << "\n";
        return 1;
    }
    else {
        // Create our window
        this->renderWindow = SDL_CreateWindow(
            "The Festival!",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            this->xDimension, this->yDimension,
            SDL_WINDOW_SHOWN
        );
    }
    if (this->renderWindow == NULL) {
        std::cout << "Window could not initialize!" << SDL_GetError() << "\n";
        return 1;
    }
    else {
        // Create our surface (the object we actually draw to)
        this->renderSurface = SDL_GetWindowSurface(this->renderWindow);
        if (this->renderSurface == NULL)
        {
            std::cout << "surface could not be created! SDL Error: " << SDL_GetError() << "\n";
            return 1;
        }
    }

    return 0;
}

void Renderer::refreshWindow() {
    SDL_UpdateWindowSurface(this->renderWindow);
}

void Renderer::fillWindow(int r, int g, int b) {
    SDL_FillRect(this->renderSurface, NULL, SDL_MapRGB(this->renderSurface->format, r, g, b));
}

void Renderer::drawRect(SDL_Rect rect, Color color) {
    SDL_FillRect(this->renderSurface,
        &rect,
        SDL_MapRGB(this->renderSurface->format, color.r, color.g, color.b)
    );
}
void Renderer::drawRect(int x, int y, int w, int h, Color color) {
    SDL_Rect rectObj = { x, y, w, h };
    this->drawRect(rectObj, color);
}

Position Renderer::getMousePosition() {
    Position mousePosition = { 0, 0 };
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    return mousePosition;
}