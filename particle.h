// The header file gives us a nice template for our class structure
// Note that the program does not instantiate any PrimitiveDrawables;
// It is a utility class designed to ensure that all drawables have certain properties.
// One type of particle is derived from it, but you could derive others.
#pragma once

#include <vector>

typedef struct Color {
    int r, g, b;
} Color;

int mersenneTwister(int min, int max);


class PrimitiveDrawable {
public:
    PrimitiveDrawable() { reset(); };
    PrimitiveDrawable(int, int);
    // Virtual functions ensure that when we pass a derived object
    // e.g. a Particle as a PrimitiveDrawable that the functions on
    // the Particle definition get called (instead of the functions on the PrimitiveDrawable).
    // In this case, sometimes it doesn't make a difference - not all of these functions get overridden in Particle,
    // But it's good practice.
    virtual int getW() const { return w; }
    virtual int getH() const { return h; }
    virtual int getX() const { return x; }
    virtual int getY() const { return y; }

    /* JAMES NOTE : r, g, and b aren't ever used in my program. Instead, I use struct Color.
    * However, because I should adhere to the rules and not modify the Primitive Drawable class,
    * I will not remove it from the class definition, just to be safe.
    */
    virtual int getR() const { return r; }
    virtual int getG() const { return r; }
    virtual int getB() const { return r; }

    // Protected members can be accessed by derived classes. 
    // Since we don't ever plan on instantiating a PrimitiveDrawable,
    // It doesn't need any private members.
protected:
    int x, y;
    int screenWidth;
    int screenHeight;
    int w;
    int h;
    int r;
    int g;
    int b;
    bool active = true;
    bool expired = false;

    virtual void reset() { return; }
};

class Particle : public PrimitiveDrawable {

public:
    Particle(int x = 0, int y = 0);

    bool checkVerticalBound(int maxY) { return this->y < maxY; }
    virtual void tick();
    virtual void bounceVertical() { return; } // To be determined by child classes
    void setColor(Color* color);
    void setColor(int r, int g, int b);
    Color getColor() const { return this->color; }

    bool dead = false;

protected:
    Color color = { 0, 0, 0 };
    int xVel = 0, yVel = 0;
    int xAcc = 0, yAcc = 1;
    int maxVel = 8;

    virtual void resetColor();
    virtual void physicsTick();
    virtual void limitVelocity();
};


class Firework : public Particle {

public:
    Firework(int x = 0, int y = 0);

    void tick() override;
    void bounceVertical();

private:
    bool hasBounced = false;
    int minBounciness = 22; // How much the firework will bounce when it hits the ground at minimum
    int maxBounciness = 38; // at maximum
    int h = 10;
    int w = 10;
};

class Spark : public Particle {

public:
    Spark(int x = 0, int y = 0);
    
    void tick() override;

private:
    int spread = 13; // How far the spark will "jump" from its original position
    int h = 3;
    int w = 3;
    int xFriction = 1;

    void applyXFriction();
    void randomDirection();
};