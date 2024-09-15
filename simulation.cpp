#include <SDL.h>
#include <vector>
#include <random>
#include "particle.h"
#include "simulation.h"
#include "renderer.h"

#include <iostream>


Simulation::Simulation(int maxX, int maxY, Renderer* renderer) {
	this->maxX = maxX;
	this->maxY = maxY;
	this->renderer = renderer;
}

void Simulation::tick() {
	this->processFireworks();
	this->processSparks();
	this->eraseDeadParticles();
	this->render();
}

void Simulation::addFirework(Firework newFirework) {
	this->fireworks.push_back(newFirework);
}
void Simulation::addFirework(int x, int y) {
	Firework newFirework = Firework(x, y);
	this->addFirework(newFirework);
}

void Simulation::addSpark(Spark newSpark) {
	this->sparks.push_back(newSpark);
}
void Simulation::addSpark(int x, int y) {
	Spark newSpark = Spark(x, y);
	this->addSpark(newSpark);
}

void Simulation::processFireworks() {
	for (Firework& particle : this->fireworks) {
		particle.tick();
		if (particle.dead) { // Create a spark where the dead particle is
			int sparkCount = rand() % (this->maxSparks - this->minSparks + 1) + this->minSparks;

			Color sparkColor = randomColor(); // Put this outside of the loop so all sparks in a group are the same color
			for (int i = 0; i < sparkCount; i++) {
				Spark newSpark = Spark(particle.getX(), particle.getY());
				newSpark.setColor(&sparkColor);
				this->addSpark(newSpark);
			}
		}

		if (!particle.checkVerticalBound(this->maxY)) { // Bounce the particle if it touches the ground
			particle.bounceVertical();
		}
	}
}

void Simulation::processSparks() {
	for (Spark& particle : this->sparks) {
		particle.tick();

		if (!particle.checkVerticalBound(this->maxY)) {
			particle.dead = true;
		}
	}
}

void Simulation::eraseDeadParticles() {
	// Delete all dead particles at once using std::vector<>.erase() loop

	/* Idea: We iterate through both particle vectors twice.
	* Maybe we could write bool processFirework(Particle particle):
	* This method would process a single firework, and return a boolean depending on if the particle is dead.
	* Then, run this method through the std::vector<>.erase() loop, making the iteration happen only once.
	*/

	// Lambda function for filtering out dead particles
	auto filter = [](const Particle& particle) { return particle.dead; };

	this->fireworks.erase(
		std::remove_if( // std::allocator instance (similar to filter() in python)
			this->fireworks.begin(),
			this->fireworks.end(),
			filter
		),
		this->fireworks.end()
	);
	
	// Do it again, but with sparks
	this->sparks.erase(
		std::remove_if(
			this->sparks.begin(),
			this->sparks.end(),
			filter
		),
		this->sparks.end()
	);
}

void Simulation::render() {
	for (Firework& firework : this->fireworks) {
		this->drawParticle(&firework);
	}
	for (Spark& spark : this->sparks) {
		this->drawParticle(&spark);
	}
}

void Simulation::drawParticle(Particle* particle) {
	// Kind of a pain to draw rectangles; need to create a rect object and then fillrect on it.
	SDL_Rect particleRect = {
		particle->getX(),
		particle->getY(),
		particle->getW(),
		particle->getH()
	};

	this->renderer->drawRect(particleRect, particle->getColor());
}

Color Simulation::randomColor() {
	std::random_device rd;
	std::mt19937 gen(rd()); // Mersenne Twister Generator
	std::uniform_int_distribution<> dist(1, 256);

	Color newColor = {
		dist(gen),
		dist(gen),
		dist(gen),
	};

	return newColor;
}