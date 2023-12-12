#include "Enemy.h"
#include <cmath>
#include <corecrt_math_defines.h>

Enemy::Enemy(float _x, float _y, float _z, float _rotY,int _maxHp, Model_3DS model, Goal* _goal) : 
    x(_x), y(_y), z(_z), rotY(_rotY), model(model), target(_goal), maxHp(_maxHp), hp(_maxHp) {
    // Initialization code
}

float Enemy::getX() {
    return x;
}

float Enemy::getY() {
    return y;
}

float Enemy::getZ() {
    return z;
}

void Enemy::setResetColorCallback(std::function<void(int)> callback) {
    callbacks.resetColor = callback;
}

void Enemy::setRemoveDamageTextCallback(std::function<void(int)> callback) {
    callbacks.removeDamageText = callback;
}

void Enemy::isOverlapping(Enemy* other) {
	// Check if this enemy is overlapping with another enemy
	// If so, move away from the other enemy
	Vector3f b1 = B1();
	Vector3f b2 = B2();
	Vector3f b3 = other->B1();
	Vector3f b4 = other->B2();

	if (b1.x < b4.x && b2.x > b3.x &&
		b1.y < b4.y && b2.y > b3.y &&
		b1.z < b4.z && b2.z > b3.z) {
		moveAwayFrom(other);
	}
}

void Enemy::moveAwayFrom(Enemy* other) {
	// Move away from another enemy
	// see which is more to the right
	// see which is more to the left, etc.
	Vector3f b1 = B1();
	Vector3f b2 = B2();
	Vector3f b3 = other->B1();
	Vector3f b4 = other->B2();

	float x1 = b1.x;
	float x2 = b2.x;
	float x3 = b3.x;
	float x4 = b4.x;

	float z1 = b1.z;
	float z2 = b2.z;
	float z3 = b3.z;
	float z4 = b4.z;
		
	float x = 0;
	float z = 0;
		
	if (x1 > x3) {
		x = x2 - x3;
	}
	else {
		x = x1 - x4;
	}

	if (z1 > z3) {
		z = z2 - z3;
	}
	else {
		z = z1 - z4;
	}

	if (abs(x) > abs(z)) {
		// Move in the x direction
		if (x > 0) {
			// Move to the right
			x += 0.1;
		}
		else {
			// Move to the left
			x -= 0.1;
		}
	}
	else {
		// Move in the z direction
		if (z > 0) {
			// Move to the front
			z += 0.1;
		}
		else {
			// Move to the back
			z -= 0.1;
		}
	}

	x /= 2;
	z /= 2;

	x += x1;
	z += z1;
		
	this->x = x;
	this->z = z;
}
