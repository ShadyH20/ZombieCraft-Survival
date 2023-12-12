//#include "Zombie.h"
////#include <math.h>
////#include <corecrt_math_defines.h>
////#include <unordered_map>
////#include <glut.h>
////#include <Vector3f.hpp>
////#include <Model_3DS.h>
//
////std::unordered_map<int, Zombie*> Zombie::zombieInstances;
//
//Zombie::Zombie(float _x, float _y, float _z, float _rotY, Model_3DS _model) {
//	x = _x;
//	y = _y;
//	z = _z;
//	rotY = _rotY;
//	model = _model;
//
//	// Generate a unique ID for each instance
//	instanceID = rand();  // You may want to use a more sophisticated method for generating IDs
//
//	// if zombieInstances is empty, initialize it
//	if (zombieInstances.empty()) {
//		zombieInstances = std::unordered_map<int, Zombie*>();
//	}
//	zombieInstances[instanceID] = this;
//}
//
//Zombie::~Zombie() {
//	// Cleanup code if needed
//}
//
//void Zombie::draw() {
//	// draw zombie
//	glPushMatrix();
//	glTranslatef(x, y, z);
//	glRotatef(rotY, 0, 1, 0);
//	
//	// if just hit print 25 above zombie's head
//	//if (justHit) {
//	//	print3D(x, y + 0.5, z, "25", 0);
//	//	//justHit = false;
//	//}
//	
//	// Bottom left corner = (2 - 0.4/2, 1.2 - 0.8/2, 2 - 0.4/2)
//	// Top right corner  = (2 + 0.4/2, 1.2 + 0.8/2, 2 + 0.4/2)
//	
//	// color
//	glColor3f(color.x, color.y, color.z);
//	
//	model.Draw();
//	//model_zombie.scale = 0.1;
//	glPopMatrix();
//}
//
//void Zombie::lookAtPlayer(float playerX, float playerZ) {
//	float dx = playerX - x;
//	float dz = playerZ - z;
//	rotY = atan2(dx, dz) * 180 / M_PI;
//}
//
//void Zombie::hit(bool headShot) {
//	color = Vector3f(1, 0, 0);
//
//	if(justHit)
//		dupText = true;
//	justHit = true;
//	damage = headShot ? "50" : "25";
//
//	glutTimerFunc(1200, removeDamageText, instanceID);
//
//	// Set a timer to reset the color after 1000 milliseconds (1 second)
//	glutTimerFunc(150, resetColorCallback, instanceID);
//}
//
//void Zombie::resetColor() {
//	color = Vector3f(1, 1, 1);
//	glutPostRedisplay();  // Request a redraw to update the color
//}
//
//// Callback function to reset the color after a certain time
//void Zombie::resetColorCallback(int instanceID) {
//	auto it = zombieInstances.find(instanceID);
//	if (it != zombieInstances.end()) {
//		Zombie* zombie = it->second;
//		zombie->color = Vector3f(1, 1, 1);
//		glutPostRedisplay();  // Request a redraw to update the color
//	}
//}
//
//// Callback function to remove the damage text after a certain time
//void Zombie::removeDamageText(int instanceID) {
//	auto it = zombieInstances.find(instanceID);
//	if (it != zombieInstances.end()) {
//		Zombie* zombie = it->second;
//		if(zombie->dupText)
//		{
//			zombie->dupText = false;
//		}
//		else {
//			zombie->justHit = false;
//		}
//		glutPostRedisplay();  // Request a redraw to update the color
//	}
//}
//
//Vector3f Zombie::B1() {
//	return Vector3f(x - 0.1, y - 0.4, z - 0.1);
//}
//
//Vector3f Zombie::B2() {
//	return Vector3f(x + 0.1, y + 0.4, z + 0.1);
//}
//
////class Zombie {
////private:
////public:
////
////	Zombie(float _x, float _y, float _z, float _rotY, Model_3DS _model) {
////		x = _x;
////		y = _y;
////		z = _z;
////		rotY = _rotY;
////		model = _model;
////
////		// Generate a unique ID for each instance
////		instanceID = rand();  // You may want to use a more sophisticated method for generating IDs
////
////		// if zombieInstances is empty, initialize it
////		if (zombieInstances.empty()) {
////			zombieInstances = std::unordered_map<int, Zombie*>();
////		}
////		zombieInstances[instanceID] = this;
////	}
////
////	float x, y, z;
////	float rotY;
////	Model_3DS model;
////
////	Vector3f color = Vector3f(1, 1, 1);
////
////	static std::unordered_map<int, Zombie*> zombieInstances;
////	int instanceID;
////
////	bool justHit = false;
////	bool dupText = false;
////	char* damage = "";
////
////	// Callback function to reset the color after a certain time
////	static void resetColorCallback(int instanceID) {
////		auto it = zombieInstances.find(instanceID);
////		if (it != zombieInstances.end()) {
////			Zombie* zombie = it->second;
////			zombie->color = Vector3f(1, 1, 1);
////			glutPostRedisplay();  // Request a redraw to update the color
////		}
////	}
////
////	// Callback function to remove the damage text after a certain time
////	static void removeDamageText(int instanceID) {
////		auto it = zombieInstances.find(instanceID);
////		if (it != zombieInstances.end()) {
////			Zombie* zombie = it->second;
////			if(zombie->dupText)
////			{
////				zombie->dupText = false;
////			}
////			else {
////				zombie->justHit = false;
////			}
////			glutPostRedisplay();  // Request a redraw to update the color
////		}
////	}
////
////	//getters
////	float getX() {
////		return x;
////	}
////
////	float getY() {
////		return y;
////	}
////
////	float getZ() {
////		return z;
////	}
////
////
////	Vector3f B1() {
////		return Vector3f(x - 0.1, y - 0.4, z - 0.1);
////	}
////
////	Vector3f B2() {
////		return Vector3f(x + 0.1, y + 0.4, z + 0.1);
////	}
////
////	void lookAtPlayer(float playerX, float playerZ) {
////		float dx = playerX - x;
////		float dz = playerZ - z;
////		rotY = atan2(dx, dz) * 180 / M_PI;
////	}
////
////	void draw() {
////		// draw zombie
////		glPushMatrix();
////		glTranslatef(x, y, z);
////		glRotatef(rotY, 0, 1, 0);
////
////		// if just hit print 25 above zombie's head
////		//if (justHit) {
////		//	print3D(x, y + 0.5, z, "25", 0);
////		//	//justHit = false;
////		//}
////
////		// Bottom left corner = (2 - 0.4/2, 1.2 - 0.8/2, 2 - 0.4/2)
////		// Top right corner  = (2 + 0.4/2, 1.2 + 0.8/2, 2 + 0.4/2)
////
////		// color
////		glColor3f(color.x, color.y, color.z);
////
////		model.Draw();
////		//model_zombie.scale = 0.1;
////		glPopMatrix();
////	}
////
////	void hitColor() {
////		color = Vector3f(1, 0, 0);
////		draw();
////		glutPostRedisplay();  // Request a redraw to update the color
////	}
////
////	void hit(bool headShot) {
////		color = Vector3f(1, 0, 0);
////
////		if(justHit)
////			dupText = true;
////		justHit = true;
////		damage = headShot ? "50" : "25";
////
////		glutTimerFunc(1200, removeDamageText, instanceID);
////
////		// Set a timer to reset the color after 1000 milliseconds (1 second)
////		glutTimerFunc(150, resetColorCallback, instanceID);
////	}
////
////	void resetColor() {
////		color = Vector3f(1, 1, 1);
////		glutPostRedisplay();  // Request a redraw to update the color
////	}
////
////};
////
