#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <unordered_map>
#include <corecrt_math_defines.h>
#include <glut.h>
#include "Model_3DS.h"
//#include "Vector3f.h"

#include "Enemy.h"

#define TO_RADIANS 3.14/180.0

class Zombie: public Enemy{
public:

 //   float x, y, z;
	//float rotY;

	//Vector3f color = Vector3f(1, 1, 1);
 //   Model_3DS model;

	static std::unordered_map<int, Zombie*> zombieInstances;
	int instanceID;

	bool justHit = false;
	bool dupText = false;
	char* damageText = "";
	bool collidingWithTarget = false;

	bool canHitPlayer = true;

	Model_3DS model2;
	bool inNether = false;

	Zombie(float _x, float _y, float _z, float _rotY, int _maxHp , Model_3DS _model, Model_3DS _model2, Goal* _player)
		: Enemy(_x, _y, _z, _rotY, _maxHp, _model, _player)
	{
		model2 = _model2;
		// Generate a unique ID for each instance
		instanceID = rand();  // You may want to use a more sophisticated method for generating IDs

		// if zombieInstances is empty, initialize it
		if (zombieInstances.empty()) {
			zombieInstances = std::unordered_map<int, Zombie*>();
		}
		zombieInstances[instanceID] = this;
	}
	;
	~Zombie() {};

	void draw(bool shouldMove) override {
		y = inNether ? 0 : 0.45;
		// draw zombie
		glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef(rotY, 0, 1, 0);

			// if just hit print 25 above zombie's head
			//if (justHit) {
			//	print3D(x, y + 0.5, z, "25", 0);
			//	//justHit = false;
			//}

			// Bottom left corner = (2 - 0.4/2, 1.2 - 0.8/2, 2 - 0.4/2)
			// Top right corner  = (2 + 0.4/2, 1.2 + 0.8/2, 2 + 0.4/2)

			// color
			glColor3f(color.x, color.y, color.z);

			if (!inNether) model.Draw();
			else model2.Draw();
		//model_zombie.scale = 0.1;
		glPopMatrix();

		// Damage Text

		// red color
		glColor3f(1, 0, 0);
		// print3d 
		if (justHit) print3D(
			x - 0.05 * cos(rotY * TO_RADIANS),
			inNether ? y + 0.95 : y + 0.5,
			z,
			damageText, 0);
		// reset color
		glColor3f(1, 1, 1);

		// Check collision with target using target B1 and B2
		Vector3f b1 = B1();
		Vector3f b2 = B2();

		// Add 0.8 padding to target B1 and B2
		Vector3f b3 = target->B1();
		Vector3f b4 = target->B2();

		b3.x -= 0.8;
		b3.z -= 0.8;

		b4.x += 0.8;
		b4.z += 0.8;
	

		if (b1.x < b4.x && b2.x > b3.x &&
			b1.y < b4.y && b2.y > b3.y &&
			b1.z < b4.z && b2.z > b3.z) {
			//printf("Zombie is colliding with target\n");
			collidingWithTarget = true;
		}
		else {
			collidingWithTarget = false;
		}


		if (shouldMove) {
			// Move zombie towards player. Stop when within 1 unit of player
			float dx = target->x - x;
			float dz = target->z - z;

			float dist = sqrt(dx * dx + dz * dz);

			if (!collidingWithTarget && dist > 0.8) {
				// random number between 0 and 1 to randomize motion a bit
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				r = r * 2 - 1;

				// Normalize dx and dz
				dx /= dist;
				dz /= dist;

				x += 0.01 * dx;
				z += 0.01 * dz;

				x += r * 0.0005;
				z += r * 0.0005;
			}
			else {
				// Hit player
				if (canHitPlayer)
				{
					target->hit(50);
					canHitPlayer = false;
					glutTimerFunc(1500, resetCanHitPlayerCallback, instanceID);
				}
			}
		}
	};


    void lookAtPlayer() override {
		float dx = target->x - x;
		float dz = target->z - z;
		rotY = atan2(dx, dz) * 180 / M_PI;
	};


	bool hit(int dmg, bool headShot) override {
		color = Vector3f(1, 0, 0);

		if (justHit)
			dupText = true;
		justHit = true;
		//damageText = headShot ? "50" : "25";
		//dmg to string
		damageText = new char[10];
		sprintf(damageText, "%d", dmg);

		printf("Zombie hit for %d damage\n", dmg);

		printf("Zombie hp: %d/%d\n", hp, maxHp);

		hp -= dmg;
		printf("Zombie hp after: %d\n", hp);

		if (hp <= 0) {
			printf("Zombie died\n");
			return true;
			// remove from skeletonInstances
			zombieInstances.erase(instanceID);
			// delete this
			delete this;
		}

		glutTimerFunc(1200, removeDamageText, instanceID);

		// Set a timer to reset the color after 150 milliseconds
		glutTimerFunc(150, resetColorCallback, instanceID);

		return false;
	};

    void resetColor() {
		color = Vector3f(1, 1, 1);
		glutPostRedisplay();  // Request a redraw to update the color
	};

    static void removeDamageText(int instanceID) {
		auto it = zombieInstances.find(instanceID);
		if (it != zombieInstances.end()) {
			Zombie* zombie = it->second;
			if (zombie->dupText)
			{
				zombie->dupText = false;
			}
			else {
				zombie->justHit = false;
			}
			glutPostRedisplay();  // Request a redraw to update the color
		}
	};

    static void resetColorCallback(int instanceID) {
		auto it = zombieInstances.find(instanceID);
		if (it != zombieInstances.end()) {
			Zombie* zombie = it->second;
			zombie->color = Vector3f(1, 1, 1);
			glutPostRedisplay();  // Request a redraw to update the color
		}
	};

	static void resetCanHitPlayerCallback(int instanceID) {
		auto it = zombieInstances.find(instanceID);
		if (it != zombieInstances.end()) {
			Zombie* zombie = it->second;
			zombie->canHitPlayer = true;
		}
	}

    Vector3f B1() override {
		if (inNether) {
			return Vector3f(x - 0.1, y, z - 0.1);
		}
		return Vector3f(x - 0.1, y - 0.4, z - 0.1);
	};

    Vector3f B2() override {
		if (inNether) {
			return Vector3f(x + 0.1, y + 0.8, z + 0.1);
		}
		return Vector3f(x + 0.1, y + 0.4, z + 0.1);
	};

private:
};

#endif // ZOMBIE_H