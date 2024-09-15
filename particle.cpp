// Don't forget to include the header in the .cpp file.
#include <iostream>
#include <random>
#include "particle.h"


std::random_device MersenneTwister;
std::mt19937 MersenneGenerator(MersenneTwister());
int mersenneTwister(int min, int max) {
    // Mersenne Twister random number generator
    std::uniform_int_distribution<> dist(min, max); // Range of values
    return dist(MersenneGenerator);
}

PrimitiveDrawable::PrimitiveDrawable(int xPos, int yPos) {
    x = xPos;
    y = yPos;
}


Particle::Particle(int x, int y) {
    this->x = x;
    this->y = y;
    this->resetColor();
    h = 10;
    w = 10;
}

void Particle::physicsTick() {
    if (dead) return;

    x += xVel;
    y += yVel;
    xVel += xAcc;
    yVel += yAcc;
}

void Particle::limitVelocity() {
    if (xVel > maxVel) xVel = maxVel;
    if (xVel < -maxVel) xVel = -maxVel;
    if (yVel > maxVel) yVel = maxVel;
    if (yVel < -maxVel) yVel = -maxVel;
}

void Particle::tick() {
    this->physicsTick();
    this->limitVelocity();
}
void Particle::setColor(Color* color) {
    this->color = *color;
}
void Particle::setColor(int r, int g, int b) {
    if (r >= 0 && r <= 256 &&
        g >= 0 && g <= 256 &&
        b >= 0 && b <= 256) {
        Color newColor = { r, g, b };
        this->setColor(&newColor);
    }
    else {
        std::cout << "Error: setColor can only take integers between 0 and 256\n";
        exit(-1);
    }
}

void Particle::resetColor() {
    std::random_device rd; // Mersenne Twister generator
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 256); // Range of values
    this->color = {
        dist(gen),
        dist(gen),
        dist(gen)
    };
}

Firework::Firework(int x, int y) {
    this->x = x;
    this->y = y;
    this->resetColor();
}

void Firework::tick() {
    this->physicsTick();
    
    if (!this->hasBounced) {
        this->limitVelocity();
    }
    if (this->hasBounced && this->yVel > 0) { // Reached climax of bounce -> explode
        this->dead = true;
    }
}

void Firework::bounceVertical() {
    int bounciness = mersenneTwister(this->minBounciness, this->maxBounciness);
    this->yVel = -(bounciness);
    this->hasBounced = true;
}


Spark::Spark(int x, int y) {
    this->x = x;
    this->y = y;
    this->resetColor();
    this->randomDirection();
}

void Spark::tick() {
    this->physicsTick();
    this->applyXFriction();
}

void Spark::applyXFriction() {
    if (x > 0) {
        x -= xFriction;
    }
    else if (x < 0) {
        x += xFriction;
    }
}

void Spark::randomDirection() {
    // Make the spark "jump" towards a random direction, as determined by Spark.spread.

    int minX = -this->spread;
    int maxX = this->spread;

    /* Notice that this function's spread technically is square:
    * It is possible for both xVel and yVel to be their maximum values.
    * Normally, I would like a circular spread, but I'm being lazy here,
    * as the square spread isn't recognizable until you increase the spark count per explosion.
    */
    int directionX = rand() % (maxX - minX + 1) + minX;
    int directionY = rand() % (maxX - minX + 1) + minX;

    this->xVel = directionX;
    this->yVel = directionY;
}
