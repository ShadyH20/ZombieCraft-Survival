
#include "Pistol.h"

Pistol::Pistol(int _maxAmmo, float _damage, float _fireRate, float _reloadTime, float _accuracy, float _range, Model_3DS _model, float _modelScale) :
	Weapon("pistol", _maxAmmo, _damage, _fireRate, _reloadTime, _accuracy, _range, _model, _modelScale) {
	// Initialization code
	xOffset = 0.0f;
	zRot = 0.0f;
	extraArmRot = 0.0f;
	handRightOffset = 0.0f;
}

Pistol::~Pistol() {
	// Cleanup code
	delete this;
}