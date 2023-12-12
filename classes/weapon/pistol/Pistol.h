#pragma once

#include <textures/Player/Player.h>
#include <classes/weapon/Weapon.h>

class Pistol: public Weapon {
public:
	Pistol(int _maxAmmo, float _damage, float _fireRate, float _reloadTime, float _accuracy, float _range, Model_3DS _model, float _modelScale);
	virtual ~Pistol();
};

