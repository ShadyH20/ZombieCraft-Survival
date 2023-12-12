#pragma once

//#include <textures/Player/Player.h>
#include <Model_3DS.h>
#include <Vector3f.h>

class Goal {
public:
	Model_3DS model;
	float modelScale = 1;

	float x, y, z;
	float width = 10;
	float height = 8;
	float depth = 5;

	int maxHp;
	int hp;

	bool isPlayer;

	Goal(float x, float y, float z, int _maxHp, Model_3DS _model, float _modelScale);
	virtual ~Goal();
	void draw();
	virtual void hit(int damage);
	virtual bool CheckCollisionWithArrow(float arrowX, float arrowY, float arrowZ, float arrowRotV, float arrowRotH);
	virtual Vector3f B1();
	virtual Vector3f B2();
};

