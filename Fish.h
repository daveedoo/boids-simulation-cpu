#pragma once
#include "Vector2d.h"
#include <GL/glut.h>
#define MAX_XY 500

class Fish
{
private:
	Vector2d position;
	Vector2d velocity;
	double viewDistance = 40.0;

public:
	double sep = 1.0;

	Fish(Vector2d position, double velocityAngle);

	void Draw();
	void Move();

	friend class Shoal;
};
