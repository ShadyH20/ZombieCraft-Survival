
#include "Sniper.h"

Sniper::Sniper(int _maxAmmo, float _damage, float _fireRate, float _reloadTime, float _accuracy, float _range, Model_3DS _model, float _modelScale) :
	Weapon("sniper", _maxAmmo, _damage, _fireRate, _reloadTime, _accuracy, _range, _model, _modelScale) {
	// Initialization code
	xOffset = 0.05f;
	zRot = -4.8f;
	yRot = 0.2f;
	extraArmRot = 5.0f;
	handRightOffset = 0.016f;
	recoilScale = 1.4f;
}

Sniper::~Sniper() {
	// Cleanup code
	delete this;
}