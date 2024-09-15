#pragma once

#include <SDL.h>
#include "particle.h" // Not good structure; I don't like it, but I have deadlines hahahaha


typedef struct Position {
	int x, y;
} Position;

class Renderer {
public:
	int xDimension, yDimension;

	Renderer(int xDimension, int yDimension);

	int initialize();
	SDL_Surface* getRenderSurface() { return this->renderSurface; }
	SDL_Window* getRenderWindow() { return this->renderWindow; }

	void refreshWindow();
	void fillWindow(int r, int g, int b);
	void drawRect(SDL_Rect rect, Color color);
	void drawRect(int x, int y, int h, int w, Color color);
	static Position getMousePosition();

private:
	SDL_Surface* renderSurface;
	SDL_Window* renderWindow;
};