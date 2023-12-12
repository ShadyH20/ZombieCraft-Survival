#pragma once

//#include <textures/Player/Player.h>
#include <Model_3DS.h>

class Wave {
public:
	int waveNumber = 1;

	int numZombies;
	int numSkeletons;

	float spawnDistanceFromGoal = 50;

	Wave ();
	virtual ~Wave();

	void waveOver();
};

