
#include "Weapon.h"

Weapon::Weapon(const char* _name, int _maxAmmo, float _damage, float _fireRate, float _reloadTime, float _accuracy, float _range, Model_3DS _model, float _modelScale) :
	name(_name), ammo(_maxAmmo), maxAmmo(_maxAmmo), damage(_damage), fireRate(_fireRate), reloadTime(_reloadTime), accuracy(_accuracy), range(_range), model(_model), modelScale(_modelScale) {
	// Initialization code

	// Set model scale
	model.scale = modelScale;
}

Weapon::~Weapon() {
	// Cleanup code
	delete this;
}