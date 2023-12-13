#ifndef SKELETON_H
#define SKELETON_H
#include <unordered_map>
#include <corecrt_math_defines.h>
#include <glut.h>
#include "Model_3DS.h"
#include <textures/Player/Player.h>

//#include "Vector3f.h"

#include "Enemy.h"

#define TO_RADIANS 3.14/180.0

/*
Object 0: RArm
Object 1: LArm
Object 2: HeadMesh
Object 3: BodyMesh
Object 4: LLeg
Object 5: RLeg
*/

class Skeleton : public Enemy{
public:
	static const int fireRate = 3500; // 5 seconds

    /*float x, y, z;
	float rotY;

	Vector3f color = Vector3f(1, 1, 1);
    Model_3DS model;*/

    Model_3DS bow;
    Model_3DS arrow;
	float scale = 0.13;
	float bow_scale = scale * 30;

	static std::unordered_map<int, Skeleton*> skeletonInstances;
	static Sound* arrow_shot_sound;
	
	int instanceID;

	int damage = 25;

	bool justHit = false;
	bool dupText = false;
	char* damageText = "";

	Skeleton(float _x, float _y, float _z, float _rotY, int _maxHp, Model_3DS _model, Model_3DS _bow, Model_3DS _arrow, Goal* _target)
	: Enemy(_x, _y, _z, _rotY, _maxHp, _model, _target) {
		bow = _bow;
		arrow = _arrow;

		// Generate a unique ID for each instance
		instanceID = rand();  // You may want to use a more sophisticated method for generating IDs

		// if skeletonInstances is empty, initialize it
		if (skeletonInstances.empty()) {
			skeletonInstances = std::unordered_map<int, Skeleton*>();
		}
		skeletonInstances[instanceID] = this;

		// Load sound if not loaded
		if (arrow_shot_sound == nullptr) {
			printf("Loading arrow shot sound\n");
			arrow_shot_sound = new Sound("sounds/arrow_shot.mp3", false);
			arrow_shot_sound->setVolume(0.3);
		}

		// Calculate armHeight
			// get min and max y in object
		float minY = INT16_MAX, minX = INT16_MAX;
		float maxY = INT16_MIN, maxX = INT16_MIN;


		for (int j = 0; j < model.Objects[0].numVerts; j++)
		{
			float y = model.Objects[0].Vertexes[j * 3 + 1];

			if (y < minY) minY = y;
			if (y > maxY) maxY = y;

			float x = model.Objects[0].Vertexes[j * 3];
			if (x < minX) minX = x;
			if (x > maxX) maxX = x;
		}

		armHeight = (maxY - minY);
		shoulderY = maxY;

		// generate random number between 0 and 1
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		//model.Load("models/skeleton/skeleton.3ds");

		// Hold bow
		holdBow();

		glutTimerFunc(fireRate + r*2000, periodicShoot, instanceID);
	}
	;
	~Skeleton() {};

	void draw(bool shouldMove) override {

		// draw skeleton
		glPushMatrix();
			glTranslatef(x, y, z);
			
			glRotatef(rotY - 90, 0, 1, 0);

			// color
			glColor3f(color.x, color.y, color.z);

			model.scale = scale;
			model.Draw();

			// draw bow
			glPushMatrix();
				glTranslatef(0, 0.15, 0.11);

				glPushMatrix();
					glRotatef(-rightArmVRot, 0, 0, 1);
					glPushMatrix();
						glTranslatef(0, -0.3, 0.0);
						glRotatef(180, 0, 1, 0);
						glRotatef(90 - arrowYaw, 0, 0, 1);
						/*glPushMatrix();
							glTranslatef(0, 0, -0.05 * bow_scale / 10);
							glScalef(1, 1, 0.75);
							arrow.scale = bow_scale * 1.5;
							arrow.Draw();
						glPopMatrix();*/

						bow.scale = bow_scale;
						bow.Draw();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

			// draw an arrow infront
			if(!shooting){
				glPushMatrix();
					glTranslatef(0.3, 0.15, 0.11);
					glRotatef(180, 0, 1, 0);
					glRotatef(-arrowYaw, 0, 0, 1);

					glPushMatrix();
						glTranslatef(0, 0, -0.05 * bow_scale / 10);
						glScalef(1, 1, 0.75);
						arrow.scale = bow_scale * 1.5;
						arrow.Draw();
					glPopMatrix();
				glPopMatrix();
			}
		glPopMatrix();

		// draw flying arrow if shooting
		if (shooting) {
			glPushMatrix();
				glTranslatef(arrowX, arrowY, arrowZ);
				glRotatef(180 - arrowTargetPitch, 0, 1, 0);
				glRotatef(-arrowTargetYaw, 0, 0, 1);
				glScalef(1, 1, 0.75);
				arrow.Draw();
			glPopMatrix();
		}

		// Damage text
		//glDisable(GL_BLEND);
		// red color
		glColor3f(1, 0, 0);	
		// print3d 
		if (justHit) print3D(
			x - 0.05 * cos(rotY * TO_RADIANS),
			y + 0.5,
			z,
			damageText, 0);
		// reset color
		glColor3f(1, 1, 1);
		//glEnable(GL_BLEND);



		if (shouldMove) {
			// Move skeleton towards player. Stop when within 6 units of player
			float dx = target->x - x;
			float dz = target->z - z;

			float dist = sqrt(dx * dx + dz * dz);

			if (dist > 8) {
				// random number between 0 and 1 to randomize motion a bit
				/*float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				r = r * 2 - 1;*/

				// Normalize dx and dz
				dx /= dist;
				dz /= dist;

				x += 0.009 * dx;
				z += 0.009 * dz;

				/*x += r * 0.005;
				z += r * 0.005;*/
			}
			else {
				// random motion
				/*float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

				r = r * 2 - 1;

				x += r * 0.0008;
				z += r * 0.0008;*/
			}
		}
	};


    void lookAtPlayer() override {
		float dx = target->x - x;
		float dz = target->z - z;
		rotY = (atan2(dx, dz)) * 180 / M_PI;

		bowAtPlayer(target->x, target->y, target->z);
	};

	void holdBow() {
		// shift the object up by half of the difference between min and max y
		float shiftY = armHeight / 2;
		model.Objects[0].pos.y = shiftY;

		// shift the object right
		model.Objects[0].pos.x = shiftY;

		rightArmVRot = -90;
		model.Objects[0].rot.z = rightArmVRot;

		// same for object 1
		model.Objects[1].pos.y = shiftY;
		model.Objects[1].pos.x = shiftY * 0.5;
		model.Objects[1].pos.z = shiftY * 0.25;

		leftArmVRot = -90;
		leftArmHRot = 45;
		model.Objects[1].rot.z = leftArmVRot;
		model.Objects[1].rot.x = leftArmHRot;
	}

	void bowAtPlayer(float playerX, float playerY, float playerZ) {
		// calculate direction from skeleton to player
		float dx = playerX - x;
		float dy = playerY - y;
		float dz = playerZ - z;

		// calculate angle between skeleton and player
		float pitch = atan2(dz, dx) * 180 / M_PI;
		float yaw = atan2(dy, sqrt(dx * dx + dz * dz)) * 180 / M_PI;

		// set rotation of arrow
		arrowYaw = yaw;
		arrowPitch = pitch;
		//arrow.rot.y = -pitch + 90;
		//arrow.rot.y = yaw;

		model.Objects[2].rot.z = arrowYaw;
		//model.Objects[2].pos.x = x + (0.1 + 0.1 * sin(arrowPitch));

	}

	static void periodicShoot(int instanceId) {
		// call shootAtPlayer on instance
		auto it = skeletonInstances.find(instanceId);
		if (it != skeletonInstances.end()) {
			Skeleton* skeleton = it->second;
			// if in range
			float dx = skeleton->target->x - skeleton->x;
			float dy = skeleton->target->y - skeleton->y;
			float dz = skeleton->target->z - skeleton->z;

			float dist = sqrt(dx * dx + dy * dy + dz * dz);

			if (dist < 10) 
			{
				skeleton->shootAtTarget();
			}
			else {
				glutTimerFunc(fireRate, periodicShoot, instanceId);
			}
		}
	
	}

	void shootAtTarget() {
		bool isPlayer = target->isPlayer;
		// calculate direction from skeleton to target
		// then move the arrow in that direction by 1 unit
		float dx = target->x - x;
		float dy = isPlayer ?
			(target->y - 0.2 * 1.25) - y :
			0;
		float dz = target->z - z;

		// calculate angle between skeleton and target
		float pitch = atan2(dz, dx) * 180 / M_PI;
		float yaw = atan2(dy, sqrt(dx * dx + dz * dz)) * 180 / M_PI;

		// set rotation of arrow
		arrowTargetYaw = yaw;
		arrowTargetPitch = pitch;

		arrowX = x;
		arrowY = y;
		arrowZ = z;

		// play sound
		Skeleton::arrow_shot_sound->play(true);

		// set arrow to be shooting
		if (shooting) return;

		shooting = true;

		// start moving arrow
		// move arrow in direction of player
		glutTimerFunc(10, moveArrow, instanceID);
	}


	bool hit(int dmg, bool headShot) override {
		color = Vector3f(1, 0, 0);

		if (justHit)
			dupText = true;
		justHit = true;
		//damageText = headShot ? "50" : "25";
		//dmg to string
		damageText = new char[10];
		sprintf(damageText, "%d", dmg);

		hp -= dmg;
		if (hp <= 0) {
			printf("Skeleton died\n");
			// remove from skeletonInstances
			return true;
			//skeletonInstances.erase(instanceID);
			//// delete this
			//delete this;
		}

		glutTimerFunc(1200, removeDamageText, instanceID);

		// Set a timer to reset the color after 1000 milliseconds (1 second)
		glutTimerFunc(150, resetColorCallback, instanceID);

		return false;
	};

    void resetColor() {
		color = Vector3f(1, 1, 1);
		glutPostRedisplay();  // Request a redraw to update the color
	};

    static void removeDamageText(int instanceID) {
		auto it = skeletonInstances.find(instanceID);
		if (it != skeletonInstances.end()) {
			Skeleton* skeleton = it->second;
			if (skeleton->dupText)
			{
				skeleton->dupText = false;
			}
			else {
				skeleton->justHit = false;
			}
			glutPostRedisplay();  // Request a redraw to update the color
		}
	};

    static void resetColorCallback(int instanceID) {
		auto it = skeletonInstances.find(instanceID);
		if (it != skeletonInstances.end()) {
			Skeleton* skeleton = it->second;
			skeleton->color = Vector3f(1, 1, 1);
			glutPostRedisplay();  // Request a redraw to update the color
		}
	};

	static void moveArrow(int instanceID)
	{
		// get instance
		auto it = skeletonInstances.find(instanceID);

		if (it != skeletonInstances.end()) {
			Skeleton* skeleton = it->second;

			// we have arrowTargetYaw and arrowTargetPitch
			float pitch = skeleton->arrowTargetPitch;
			float yaw = skeleton->arrowTargetYaw;
			
			// calculate components based on angles
			float speedX = skeleton->arrowSpeed * cos(yaw * M_PI / 180) * cos(pitch * M_PI / 180);
			float speedY = skeleton->arrowSpeed * sin(yaw * M_PI / 180);
			float speedZ = skeleton->arrowSpeed * cos(yaw * M_PI / 180) * sin(pitch * M_PI / 180);

			// set arrow position to be in front of skeleton
			skeleton->arrowX += speedX;
			skeleton->arrowY += speedY;
			skeleton->arrowZ += speedZ;

			// check if arrow hit player
			bool hit = skeleton->target->CheckCollisionWithArrow(skeleton->arrowX, skeleton->arrowY, skeleton->arrowZ, skeleton->arrowTargetYaw, skeleton->arrowTargetPitch);

			if (hit) {
				//printf("OUCH!!!!\n");
				skeleton->target->hit(skeleton->damage);
				skeleton->shooting = false;
				glutTimerFunc(fireRate, periodicShoot, instanceID);
				return;
			}

			// check if arrow moved 10 units away from skeleton
			// if so, stop shooting
			float dx = skeleton->arrowX - skeleton->x;
			float dy = skeleton->arrowY - skeleton->y;
			float dz = skeleton->arrowZ - skeleton->z;

			float dist = sqrt(dx * dx + dy * dy + dz * dz);
			if (dist > 10) {
				skeleton->shooting = false;
				glutTimerFunc(fireRate, periodicShoot, instanceID);
			}
			// if not, keep moving arrow
			else {
				glutTimerFunc(5, moveArrow, instanceID);
			}
		}
	}

    Vector3f B1() override {
		return Vector3f(x - 0.1, y - 0.5, z - 0.1);
	};

    Vector3f B2() override {
		return Vector3f(x + 0.1, y + 0.3, z + 0.1);
	};

private:
	float armHeight = 0.0f;
	float shoulderY = 0.0f;

	float rightArmVRot = 0.0f;

	float leftArmHRot = 0.0f;
	float leftArmVRot = 0.0f;

	float arrowYaw = 0.0f;
	float arrowPitch = 0.0f;

	bool shooting = false;
	float arrowSpeed = 0.4f;
	float arrowTargetYaw = 0.0f;
	float arrowTargetPitch = 0.0f;

	float arrowX = 0.0f;
	float arrowY = 0.0f;
	float arrowZ = 0.0f;
};

#endif // ZOMBIE_H