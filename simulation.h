#pragma once

#include <vector>
#include <SDL.h>
#include "particle.h"
#include "renderer.h"

class Simulation {

public:
	Simulation(int maxX, int maxY, Renderer* renderer);

	void tick();
	void addFirework(Firework newFirework);
	void addFirework(int x, int y);

private:
	std::vector<Firework> fireworks;
	std::vector<Spark> sparks;

	int maxX, maxY; // Dimensions in which the simulation runs. Boundary checks are based on these.
	int minSparks = 20; // The minimum sparks for each firework explosion
	int maxSparks = 35; // The maximum sparks

	/* Would this be good structure? Normally, I like to keep rendering objects and logic objects separate,
	* but I feel that the Simulation class is on a line between the two.
	* At the same time, Simulation doesn't feel like it should be higher than Renderer in a class hierarchy.
	* Nonetheless, this works.
	*/
	Renderer* renderer;

	void addSpark(const Spark newSpark);
	void addSpark(int x, int y);
	void processFireworks();
	void processSparks();
	void eraseDeadParticles();
	void render();
	void drawParticle(Particle* particle);
	static Color randomColor();
};