#include <cmath>
#include "Fish.h"

Fish::Fish(Vector2d position, double velocityAngle)
{
	this->position = position;
	velocity.x = cos(velocityAngle);
	velocity.y = sin(velocityAngle);
}

void Fish::Draw()
{
	double l = 3;
	Vector2d v = velocity.normalized();

	Vector2d P = Vector2d(position.x - 3*l*v.x, position.y - 3*l*v.y);
	Vector2d p1 = Vector2d(P.x - l*v.y, P.y + l*v.x);
	Vector2d p2 = Vector2d(P.x + l*v.y, P.y - l*v.x);

	glVertex2f(position.x, position.y);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
}

void Fish::Move()
{
	position.x += velocity.x;
	position.y += velocity.y;

	// przep³yniêcie na drug¹ stronê ekranu
	if (position.x > MAX_XY)
		position.x -= 2.0*MAX_XY;
	else if (position.x < -MAX_XY)
		position.x += 2.0*MAX_XY;

	if (position.y > MAX_XY)
		position.y -= 2.0*MAX_XY;
	else if (position.y < -MAX_XY)
		position.y += 2.0*MAX_XY;
}
