#pragma once

//#include <textures/Player/Player.h>
#include <Model_3DS.h>

class Weapon {
public:
	const char* name;
	int ammo;
	int maxAmmo;
	int totalAmmo;

	float damage;
	float fireRate;
	float reloadTime;

	bool canShoot = true;

	float accuracy;

	float range;

	Model_3DS model;
	float modelScale = 1;

	// Weapon offset
	float xOffset = 0;
	float zRot = 0;
	float yRot = 0;
	float extraArmRot = 0;
	float handRightOffset = 0;
	float recoilScale = 1;

	//Player* player;

	Weapon(const char* _name, int _maxAmmo, float _damage, float _fireRate, float _reloadTime, float _accuracy, float _range, Model_3DS _model, float _modelScale);
	virtual ~Weapon();
};

