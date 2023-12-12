#pragma once

#include <textures/Player/Player.h>
#include <classes/weapon/Weapon.h>

class Sniper: public Weapon {
public:
	Sniper(int _maxAmmo, float _damage, float _fireRate, float _reloadTime, float _accuracy, float _range, Model_3DS _model, float _modelScale);
	virtual ~Sniper();
};

