#pragma once
#include "Fish.h"

class Shoal
{
private:
	unsigned int N;	// liczba ryb
	Fish* fishes;


public:
	float separation_lvl = 0.07f;
	float alignment_lvl = 0.01f;
	float cohesion_lvl = 0.07f;

	Shoal(unsigned int n);

	void Draw();
	void Move();

	~Shoal();

private:
	void flock(int fish_index);
};