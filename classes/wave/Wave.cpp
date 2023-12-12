
#include "Wave.h"

Wave::Wave() {
	waveNumber = 1;

	numZombies = 4;
	numSkeletons = 2;
}

Wave::~Wave() {
	// Cleanup code
	delete this;
}

void Wave::waveOver() {
	waveNumber++;

	numZombies += waveNumber;
	numSkeletons += waveNumber;
}

