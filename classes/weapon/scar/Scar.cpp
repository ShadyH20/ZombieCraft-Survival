
#include "Scar.h"

Scar::Scar(int _maxAmmo, float _damage, float _fireRate, float _reloadTime, float _accuracy, float _range, Model_3DS _model, float _modelScale) :
	Weapon("scar", _maxAmmo, _damage, _fireRate, _reloadTime, _accuracy, _range, _model, _modelScale) {
	// Initialization code
	xOffset = 0;
	zRot = -3.0f;
	extraArmRot = 5.0f;
	handRightOffset = 0.015f;
	recoilScale = 0.02f;
}

Scar::~Scar() {
	// Cleanup code
	delete this;
}