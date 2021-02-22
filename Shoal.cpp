#define _USE_MATH_DEFINES
#include <stdexcept>
#include <time.h>
#include <cmath>
#include "Shoal.h"

Shoal::Shoal(unsigned int n)
{
	if (n == 0)
		throw std::invalid_argument("n should be positive int");
	N = n;

	fishes = (Fish*)malloc(n * sizeof(Fish));
	if (fishes == NULL)
		throw new std::bad_alloc();

	double x, y, angle;
	srand((unsigned int)time(NULL));
	for (unsigned int i = 0; i < n; i++)
	{
		x = -MAX_XY + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (2*MAX_XY)));
		y = -MAX_XY + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (2*MAX_XY)));
		angle = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2*M_PI)));
		fishes[i] = Fish(Vector2d(x, y), angle);
	}
}

void Shoal::Draw()
{
	for (unsigned int i = 0; i < N; i++)
	{
		fishes[i].Draw();
	}
}

void Shoal::Move()
{
	for (unsigned int i = 0; i < N; i++)
	{
		flock(i);

		fishes[i].Move();
	}
}

Shoal::~Shoal()
{
	delete[] fishes;
}

void Shoal::flock(int i)
{
	Vector2d sep_v = Vector2d();
	Vector2d align_v = Vector2d();
	Vector2d cohes_v = Vector2d();
	int counter = 0;
	for (unsigned int j = 0; j < N; j++)
	{
		if (j == i)
			continue;

		double dist = Vector2d::Distance(fishes[i].position, fishes[j].position);
		if (dist < fishes[i].viewDistance)
		{
			sep_v.Add((fishes[i].position - fishes[j].position) / (dist * dist));	// 1. separation
			align_v.Add(fishes[j].velocity);										// 2. alignment
			cohes_v.Add(fishes[j].position);										// 3. cohesion

			counter++;
		}
	}

	if (counter > 0)
	{
		align_v = align_v / counter;
		cohes_v = (cohes_v / counter) - fishes[i].position;

		sep_v.normalize();
		align_v.normalize();
		cohes_v.normalize();

		fishes[i].velocity.Add((sep_v * separation_lvl) + (align_v * alignment_lvl) + (cohes_v * cohesion_lvl));
		fishes[i].velocity.normalize();
	}

}
