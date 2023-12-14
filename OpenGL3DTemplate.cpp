//#include <glew.h>
#include "Model_3DS.h"
#include <classes/sound/Sound.h>
//#include "GLTexture.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include "utilities.hpp"
#include "seesaw.hpp"
#include <Vector3f.h>
#include "collision.hpp"
#include "Camera.hpp"
#include <classes/enemy/Zombie.h>
#include <classes/enemy/Skeleton.h>
#include <textures/Player/Player.h>
#include <classes/weapon/Weapon.h>
#include <classes/weapon/pistol/Pistol.h>
#include <classes/weapon/scar/Scar.h>

//#include "Enemy.h"
#include <string>
#include <algorithm> // Make sure this line is included
#include <vector>
#include <classes/hud/HUD.h>
#include <classes/goal/Goal.h>
#include <classes/wave/Wave.h>
#include <classes/weapon/sniper/Sniper.h>
#include <classes/weapon/ammo/Ammo.h>
//#include <textures/Player/Cuboid.h>
//#include <textures/Player/Player.cpp>

//#define GLT_IMPLEMENTATION
//#include "gltext.h"

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)


/// FIRST PERSON ////
#define FPS 60
#define TO_RADIANS 3.14/180.0
#define TO_DEGREES 180.0/3.14

struct Motion
{
	bool Forward, Backward, Left, Right, Up, Down;
};

Motion motion = { false,false,false,false,false,false };


//width and height of the window ( Aspect ratio 16:9 )
const int width = 16 * 50;
const int height = 9 * 50;

float pitch = 0.0, yaw = 0.0;
//float steve->x = 0.0, steve->y = -0.25, steve->z = 0.0;

//Camera
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 0.0f;

float centerX = 0.0f;
float centerY = 0.0f;
float centerZ = 0.0f;

void init();
void display();
void GameOverScreen();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void cameraFP();
void keyboardFP(unsigned char key, int x, int y);
void keyboard_upFP(unsigned char key, int x, int y);
void mouseFP(int button, int state, int x, int y);
void shoot();
void reloadWeapon(int value);
void reload();
void reload();
void spawnEnemies();
void drawHouses();
void LoadEnemies();
/////////////////////

const double screenW = 1600.0;
const double screenH = 900.0;


// Game State
bool reachedGoal = false;
bool hasWon = false;
bool hasLost = false;

// string gamestate
std::string gameState = "menu";

float maxTime = 200;
int timeLeft = maxTime;

double deltaTime = 0.1f;

// Third Person
bool thirdPerson = false;
bool faceCamera = false;

bool cameraRight = false;
bool cameraLeft = false;
int playerDir = 0;

float playerW = 0.1;

// Movement
float moveSpeed = 0.0150f;
float currentSpeed = 0.0f;
float targetSpeed = 0.0f;

// Rotation
float rotationSpeed = 70.0f;
float playerRot = 90.0;
int targetAngle = 90;

float minX = -30;
float minZ = -38;
float maxX = 30;
float maxZ = 28;


//Wall
//147, 77, 44
float wallR = 144;
float wallG = 77;
float wallB = 44;


// Pistol
float pistolXOrig = 0.1, pistolYOrig = -0.25 / 5, pistolZOrig = -1.5 / 5;
float pistolX = pistolXOrig, pistolY = pistolYOrig, pistolZ = pistolZOrig;
float pistolRot = 10;

bool isAnimatingPistol = false;
bool isRightRotation = true;
float pistolAnimCurTime = 0.0f;
float pistolAnimDuration = 0.3f;
float pistolRecoilAngle = 0.0f;

// Player
Player* steve;
float runSpeed = 3.0;
float aimSpeed = 1.5;
float playerSpeed = runSpeed;
float playerZFromCamera = 0.5f;
float playerYFromCamera = 0.5f;

bool mouseRightDown = false;
bool mouseLeftDown = false;
bool mouseTrackingEnabled = true;

// Dragon
float dragonWingsAngle = 0;
bool dragonWingsAnimating = true;
float dragonWingsAnimDuration = 2.0f;
float dragonWingsAnimCurTime = 0.0f;

// Game Stuff
// Light intensity
float intensityX = 0.7f, intensityY = 0.7f, intensityZ = 0.7f;
bool increaseIntensity = false;

Vector3f lightPos = Vector3f(-50, 100, -240);
Vector3f sunPos = Vector3f(-50, 100, -240);

Vector3f lightColor = Vector3f(250, 203, 20);
Vector3f sunColor = Vector3f(250, 203, 20);
Vector3f moonColor = Vector3f(147, 163, 177);

Vector3f lightEmissionColor = Vector3f(250, 80, 20);
Vector3f sunEmissionColor = Vector3f(250, 80, 20);
Vector3f moonEmissionColor = Vector3f(47, 63, 77);

int score = 0;

bool isPortalOpen = false;

// Wave
Wave* wave;

// Enemies
std::unordered_map<int, Enemy*> Enemy::enemyInstances;
std::vector<Enemy*> enemies;

// Zombies
std::unordered_map<int, Zombie*> Zombie::zombieInstances;
std::vector<Zombie*> zombies;

// Skeletons
std::unordered_map<int, Skeleton*> Skeleton::skeletonInstances;
std::vector<Skeleton*> skeletons;
Sound* Skeleton::arrow_shot_sound = nullptr;

// Hearts
std::vector<Vector3f> hearts;

// Ammo
std::vector<Ammo*> ammos;


// 

// HUD
HUD* hud;

// Weapons
Pistol* pistol;
Scar* scar;
Sniper* sniper;

// Goal
Goal* church;

// Model Variables
Model_3DS model_church;
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_creeper;
Model_3DS model_sword;
Model_3DS model_torch;
Model_3DS model_village;
Model_3DS model_pistol;
Model_3DS model_shotgun;
Model_3DS model_dragon;
Model_3DS model_zombie;
Model_3DS model_bow;
Model_3DS model_scar;
Model_3DS model_sniper;
Model_3DS model_arrow;
Model_3DS model_skeleton;
Model_3DS model_villa;
Model_3DS model_heart;
Model_3DS model_mountain;
Model_3DS model_portal;

// Nether Models
Model_3DS model_nether;
Model_3DS model_piglin;
Model_3DS model_nether_ground;
Model_3DS model_lava_pit;
Model_3DS model_nether_roof;
Model_3DS model_nether_wall;
Model_3DS model_nether_stone;

float villageScale = 0.5;

// Textures
GLTexture tex_ground;
GLTexture tex_path;
GLTexture tex_ammo;
GLuint tex_sky;
GLuint tex_moon;


// Sounds
Sound* pistol_sound;
Sound* scar_sound;
Sound* sniper_sound;
Sound* bg_music;
Sound* damage_sound;

// Cuboids


// Text
float textOpacity = 0.0f;


Camera camera;


void movePlayer(int value)
{
	/*if (ridingSeesaw || ridingFerrisWheel) {
		glutPostRedisplay();
		glutTimerFunc(30, movePlayer, 0);
		return;
	}*/

	// Update the current x and y using linear interpolation
	if (currentSpeed != targetSpeed)
	{
		double speedDiff = targetSpeed - currentSpeed;
		// std::cout << "speed diff: " << speedDiff << "\n";
		double speedAmount = fabs(speedDiff) * deltaTime;

		if (fabs(speedDiff) < 0.2f)
		{
			currentSpeed = targetSpeed;
		}
		else if (speedDiff > 0)
		{
			currentSpeed += speedAmount;
		}
		else
		{
			currentSpeed -= speedAmount;
		}
	}


	float pRot = thirdPerson ? playerRot + playerDir : playerRot;

	if (targetAngle != 90 && targetAngle != 270)
		steve->x += currentSpeed * cos(pRot * 3.14159 / 180.0);
	if (targetAngle != 0 && targetAngle != 180)
		steve->z += -currentSpeed * sin(pRot * 3.14159 / 180.0);


	// make sure the player doesn't go out of bounds
	if (steve->x < minX) steve->x = minX;
	if (steve->x > maxX) steve->x = maxX;
	if (steve->z < minZ) steve->z = minZ;
	if (steve->z > maxZ) steve->z = maxZ;

	// detect coillision with donut
	float distance = sqrt(pow(steve->x - 3.5, 2) + pow(steve->z - 3.5, 2));
	if (distance < 0.17)
	{
		reachedGoal = true;
		//glutTimerFunc(3000, collidedWithGoal, 0);
	}

	glutPostRedisplay();

	glutTimerFunc(30, movePlayer, 0);
}

void rotatePlayer(int value)
{
	//if (ridingSeesaw) {
	//	glutPostRedisplay();
	//	glutTimerFunc(30, rotatePlayer, 0);
	//	return;
	//}
	// Update the current angle using linear interpolation
	if (playerRot != targetAngle)
	{
		float angleDiff = targetAngle - playerRot;
		if (angleDiff > 180.0f)
		{
			angleDiff -= 360.0f;
		}
		else if (angleDiff < -180.0f)
		{
			angleDiff += 360.0f;
		}
		float rotationAmount = rotationSpeed * deltaTime;

		/*if (fabs(angleDiff) < rotationAmount) {
			rot = targetAngle;
		}*/
		// else
		if (angleDiff > 0)
		{
			// rot += rotationAmount;
			playerRot += fabs(angleDiff) * 0.15;
		}
		else
		{
			// playerRot -= rotationAmount;
			playerRot -= fabs(angleDiff) * 0.15;
		}
		if (playerRot >= 360.0f)
		{
			playerRot -= 360.0f;
		}
		else if (playerRot < 0.0f)
		{
			playerRot += 360.0f;
		}
	}

	glutPostRedisplay();

	glutTimerFunc(30, rotatePlayer, 0);
}

Vector3f torchPos = Vector3f(0,0,0);
void setupLights() {
	// Light 0 (ambient light)
	//GLfloat ambientM[] = { 0.7f, 0.7f, 0.7, 1.0f };
	//GLfloat diffuseM[] = { 0.6f, 0.6f, 0.6, 1.0f };
	//GLfloat specularM[] = { 2.0f, 2.0f, 2.0, 1.0f };
	//GLfloat shininessM[] = { 50 };

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientM);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseM);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specularM);
	//glMaterialfv(GL_FRONT, GL_SHININESS, shininessM);

	// Light 0 setup (ambient light)
	//glEnable(GL_LIGHT0);
	////GLfloat lightPosition[] = { -7.0f, 5.0f, 5.0f, 0.0f };
	////GLfloat lightPosition[] = { -7.0f, 10.0f, 5.0f, 0.0f };
	//GLfloat lightPosition[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//GLfloat lightIntensity[] = { 1, 1, 1, 1.0f };
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { intensityX, intensityY, intensityZ, 1.0f };
	//GLfloat ambient[] = { 0.01, 0.01, 0.01, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	//GLfloat light_position[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	GLfloat light_position[] = { -50, 100, -240, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Light 1 setup (torch tip)
	glEnable(GL_LIGHT1);
	//GLfloat lightPosition2[] = { 3, 0.085, 3, 1.0 }; // Specify the position (homogeneous coordinates)
	GLfloat torchPosition[] = { torchPos.x,torchPos.y,torchPos.z, 1.0 }; // Specify the position (homogeneous coordinates)
	GLfloat torchColor[] = { 0.2, 0.2, 0.0, 1.0 }; // Specify the color (RGBA)
	GLfloat spotDirection[] = { 0.0, 0.0, -1.0 }; // Specify the spotlight direction (x, y, z)
	GLfloat torchAmbient[] = { 0.1, 0.1, 0.1, 1.0f };
	GLfloat torchSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };



	glLightfv(GL_LIGHT1, GL_POSITION, torchPosition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, torchColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, torchSpecular);
	/*glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);*/
	// ambient
	glLightfv(GL_LIGHT1, GL_AMBIENT, torchAmbient);

	/*glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);*/

	//ATTENUATION
	/*glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.5);*/
}

//void setupCamera() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60, screenW / screenH, 0.001, 100);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	if (thirdPerson)
//	{
//		//printf("Target angle: %d\n", rem);
//		//printf("Target angle: %d\n", playerRot);
//		float steve->y = ridingSeesaw ? steve->ySeesaw : ridingFerrisWheel ? steve->yFerrisWheel : 0;
//		float playerAngleY = DEG2RAD(ridingSeesaw ? playerRotSeesaw : ridingFerrisWheel ? playerRotFerrisWheel : playerRot);
//		//float playerAngleY = DEG2RAD(playerRotSeesaw);
//		float distance = 1;  // Adjust this value for the desired distance from the player
//
//		float camsteve->x = ridingSeesaw ? steve->xSeesaw : ridingFerrisWheel ? steve->xFerrisWheel : steve->x;
//		float camsteve->z = ridingSeesaw ? steve->zSeesaw : ridingFerrisWheel ? steve->zFerrisWheel : steve->z;
//
//		float camX = camsteve->x + distance * sin(ridingSeesaw ? DEG2RAD(-180) : (DEG2RAD(-90) + playerAngleY));
//		float camY = steve->y + 0.6;  // Adjust this value for the desired height of the camera
//
//		float camZ = camsteve->z + distance * cos(ridingSeesaw ? DEG2RAD(-180) : (DEG2RAD(-90) + playerAngleY));
//
//		gluLookAt(camX, camY, camZ,
//			camsteve->x, steve->y + 0.2, camsteve->z,
//			0, 1, 0);
//
//		// Rotate the camera
//		if (cameraRight)
//		{
//			targetAngle -= 1.0f;
//		}
//		else if (cameraLeft)
//		{
//			targetAngle += 1.0f;
//		}
//	}
//	else
//	{
//		camera.look();
//	}
//
//	//log the camera eye, center, up
//	/*printf("\neye= Vector3f(%f, %f, %f);\n", camera.eye.x, camera.eye.y, camera.eye.z);
//	printf("center= Vector3f(%f, %f, %f);\n", camera.center.x, camera.center.y, camera.center.z);
//	printf("up= Vector3f(%f, %f, %f);\n", camera.up.x, camera.up.y, camera.up.z);*/
//
//
//}


void renderText() {
	glColor3f(0, 0, 0);

	printStroke(screenW / 2 - 7, screenH / 2, "+", 0.15, 1.5);


	// If isPortalOpen write "Enter the portal" in the middle of the screen
	if (isPortalOpen) {
		char* p0s[30];
		sprintf((char*)p0s, "Enter the portal");
		float opacity = (sin(textOpacity * 0.5 * 3.1415 / 180) + 1) / 2;
		colorRGBA(255, 0, 255, opacity);
		printStroke(screenW / 2 - 180, screenH / 2, (char *)p0s, 0.28, 3.5);
	}

	// If isReloading write "Reloading" in the middle of the screen
	if (steve->currentWeapon->isReloading && steve->currentWeapon->totalAmmo > 0) {
		char p0s[30];
		sprintf((char*)p0s, "Reloading");
		float opacity = 1;
		colorRGBA(255, 255, 255, opacity);
		printStroke(screenW / 2 - 80, screenH / 2 - 20, (char*)p0s, 0.28, 3.5);
	}

	//drawTime(screenW, screenH, timeLeft);

	//printStroke(screenW / 2 - 30, 300, "Ammo: 36 / 98", 1);


	glPushMatrix();
	// Reset color
	glColor3f(1, 1, 1);

	// HUD
	hud->draw();

	// Write score top left
	char* scoreText[20];
	sprintf((char*)scoreText, "SCORE %i", score);
	printStroke(30, screenH - 50, (char*)scoreText, 0.15, 2);

	glPopMatrix();


	// Reset color
	glColor3f(1, 1, 1);


	//enable3D();
}


GLTexture logo;
void menuUI() {


	glPushMatrix();
		// Reset color
		glColor3f(1, 1, 1);

		glEnable(GL_TEXTURE_2D);

		// In top center. Use logo.width and logo.height
		float aspectRatio = (float)logo.width / logo.height;
		float scale = 1.2;
		float w = 560 * scale;
		float h = 100 * scale;

		glColor4f(1, 1, 1, 1);
		hud->drawSquareTexture(logo, screenW / 2 - w / 2, screenH - 190, w, h);



		glDisable(GL_TEXTURE_2D);

		// HUD
		//hud->draw();

		// Draw "Press ENTER to begin" in bottom center
		char* p0s[30];
		sprintf((char*)p0s, "Press ENTER to begin");
		float opacity = (sin(textOpacity * 0.5 * 3.1415 / 180) + 1) / 2;
		colorRGBA(0,0,0, opacity);
		printStroke(screenW / 2 - 180, 100, (char*)p0s, 0.28, 4.5);


	glPopMatrix();

	// Reset color
	glColor3f(1, 1, 1);


	//enable3D();
}


int groundSize = 60;

void RenderGround()
{
	//glDisable(GL_LIGHTING);	// Disable lighting 

	GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 0.1 };
	GLfloat low_shininess[] = { 20.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

	float intX = fmax(0.5, intensityX);
	float intY = fmax(0.5, intensityY);
	float intZ = fmax(0.5, intensityZ);
	glColor3f(intX, intY, intZ);	// Set material to white

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-groundSize, 0, -groundSize);
	glTexCoord2f(30, 0);
	glVertex3f(groundSize, 0, -groundSize);
	glTexCoord2f(30, 30);
	glVertex3f(groundSize, 0, groundSize);
	glTexCoord2f(0, 30);
	glVertex3f(-groundSize, 0, groundSize);
	glEnd();
	glPopMatrix();

	// draw the path which is 4 textures wide from z = 10 to z = 15
	//glBindTexture(GL_TEXTURE_2D, tex_path.texture[0]);	// Bind the ground texture
	//glPushMatrix();
	//glBegin(GL_QUADS);
	//glNormal3f(0, 1, 0);	// Set quad normal direction.
	//glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	//glVertex3f(-groundSize, 0.01, 10);
	//glTexCoord2f(2 * groundSize, 0);
	//glVertex3f(groundSize, 0.01, 10);
	//glTexCoord2f(2 * groundSize, 4);
	//glVertex3f(groundSize, 0.01, 15);
	//glTexCoord2f(0, 4);
	//glVertex3f(-groundSize, 0.01, 15);
	//glEnd();
	//glPopMatrix();

	float width = 1.5;
	float halfW = width / 2;
	float zCoords[] = { -10, 10 };
	float lengths[] = { 20, 20 };

	for (int i = 0; i < 2; i++) {
		float z = zCoords[i];
		float length = lengths[i];
		// draw the path which is 4 textures wide from z = 10 to z = 15
		glBindTexture(GL_TEXTURE_2D, tex_path.texture[0]);	// Bind the ground texture
		glPushMatrix();
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);	// Set quad normal direction.
		glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
		glVertex3f(-10, 0.01, z + halfW);
		glTexCoord2f(length, 0);
		glVertex3f(10, 0.01, z + halfW);
		glTexCoord2f(length, 1);
		glVertex3f(10, 0.01, z - halfW);
		glTexCoord2f(0, 1);
		glVertex3f(-10, 0.01, z - halfW);
		glEnd();
		glPopMatrix();
	}

	// Middle path
	float middleZFrom = -30;
	float middleZTo = 10;
	float middleLength = middleZTo - middleZFrom;
	float middleX = 0;

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tex_path.texture[0]);	// Bind the ground texture
		glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);	// Set quad normal direction.
			glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
			glVertex3f(middleX - halfW, 0.01, middleZFrom);
			glTexCoord2f(1, 0);
			glVertex3f(middleX + halfW, 0.01, middleZFrom);
			glTexCoord2f(1, middleLength / 2);
			glVertex3f(middleX + halfW, 0.01, middleZTo);
			glTexCoord2f(0, middleLength / 2);
			glVertex3f(middleX - halfW, 0.01, middleZTo);
		glEnd();
	glPopMatrix();


		


	//glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void drawHearts() {
	for (int i = 0; i < hearts.size(); i++) {
		Vector3f heart = hearts[i];

		// draw heart
		glPushMatrix();
		glTranslatef(heart.x,
			0.4 + 0.06 * sin(textOpacity * TO_RADIANS),
			heart.z);
		// Rotate y using textOpacity var
		glRotatef(textOpacity * 0.5, 0, 1, 0);

		//glScaled(0.5, 0.5, 0.5);
		model_heart.Draw();
		model_heart.scale = 0.03;
		glPopMatrix();
	}

	// Check collision with player
	if (steve->hp != steve->maxHp)
	{
		for (int i = 0; i < hearts.size(); i++) {
			Vector3f heart = hearts[i];
			float distance = sqrt(pow(steve->x - heart.x, 2) + pow(steve->z - heart.z, 2));
			if (distance < 0.5) {
				// remove the heart from the vector
				hearts.erase(hearts.begin() + i);
				// add a heart to the player
				steve->heal(100);
				// play sound
				//damage_sound->play();
			}
		}
	}

	////////////////////////////////////

	/// AMMO ///
	for (int i = 0; i < ammos.size(); i++) {
		Ammo* ammo = ammos[i];

		// draw ammo
		ammo->Draw(textOpacity);
	}

	// Check collision with player

	for (int i = 0; i < ammos.size(); i++) {
		Ammo* ammo = ammos[i];
		float distance = sqrt(pow(steve->x - ammo->x, 2) + pow(steve->z - ammo->z, 2));
		if (distance < 0.5) {
			// remove the ammo from the vector
			ammos.erase(ammos.begin() + i);

			steve->currentWeapon->totalAmmo += 2 * steve->currentWeapon->maxAmmo;

			//steve->ammo += 10;
			// play sound
			//damage_sound->play();
		}
	}
}

void MenuScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//setupCamera();
	//cameraFP();

	// Dragon at 5, 8.0, 2

	// Camera
	gluLookAt(
		13, 14, 13,
		0, 8, 2,
		0.0, 1.0, 0.0
	);

	// Move steve to be on top of the dragon
	steve->x = 5;
	steve->y = 11.3;
	steve->z = 4.7;

	steve->UnholdGun();

	yaw = 180;

	steve->leftLegRotX = 90;
	steve->rightLegRotX = 90;
	//steve->

	setupLights();

	bgColorRGB(171, 201, 229, 1);

	glColor3f(1.0f, 1.0f, 1.0f);

	// Ground
	RenderGround();

	// DRAW STEVE
	glPushMatrix();
	//steve->isMoving = motion.Forward || motion.Backward || motion.Left || motion.Right;
	steve->Move(false);

	glPushMatrix();


		glRotatef(yaw, 0, 1, 0);

	steve->Look(yaw, (thirdPerson && faceCamera) ? -pitch : pitch);

	// Draw Steve (if not dead)
	if (!steve->isDead)
	{
		steve->Draw(true, false, pistolRecoilAngle);
	}
	glPopMatrix();

	glPopMatrix();

	// Reset color
	glColor3f(1, 1, 1);

	// draw dragon
	glPushMatrix();
	glTranslatef(5, 8.0, 2);
	//glScaled(0.5, 0.5, 0.5);
	model_dragon.Draw();
	model_dragon.scale = 1;

	//float dragRot = dragonWingsAngle

	// set z rotation of objects 1 and 2
	model_dragon.Objects[1].rot.z = 5 - dragonWingsAngle;
	model_dragon.Objects[2].rot.z = -5 + dragonWingsAngle;
	/*model_dragon.Objects[1].rot.z = -0;
	model_dragon.Objects[2].rot.z = 0;*/

	// objects 1 and 2 are the wings
	// they are each 0.5 units away from the center of the dragon
	// their rotation is about the center of the dragon
	// so we need to translate them to compensate for the rotation
	model_dragon.Objects[1].pos.x = -1.5 * sin(dragonWingsAngle * TO_RADIANS);
	model_dragon.Objects[1].pos.y = 1 * sin(dragonWingsAngle * TO_RADIANS);

	model_dragon.Objects[2].pos.x = 1.5 * sin(dragonWingsAngle * TO_RADIANS);
	model_dragon.Objects[2].pos.y = 1 * sin(dragonWingsAngle * TO_RADIANS);
	glPopMatrix();

	// draw houses
	drawHouses();

	// mountain at - 30 x
	glPushMatrix();
	glTranslatef(25, -1.5, -50);
	glRotatef(90, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_mountain.Draw();
	model_mountain.scale = villageScale;
	glPopMatrix();

	// mountain at - 30 x
	glPushMatrix();
	glTranslatef(-25, -1.5, 40);
	glRotatef(-90, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_mountain.Draw();
	model_mountain.scale = villageScale;
	glPopMatrix();

	// mountain behind
	glPushMatrix();
	glTranslatef(-50, -1.5, -35);
	glRotatef(180, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_mountain.Draw();
	model_mountain.scale = villageScale;
	glPopMatrix();


	// draw church
	church->draw();

	// draw portal
	glPushMatrix();
	glTranslatef(0, 0, 0);
	//glRotatef(90, 0, 1, 0);
	model_portal.Draw();
	model_portal.scale = 0.35;
	glPopMatrix();

	model_portal.Objects[3].pos.y = isPortalOpen ? 0 : -10;

	// Clear enemy arrays if they arent empty
	if (enemies.size() > 0) {
		enemies.clear();
		zombies.clear();
		skeletons.clear();
	}

   // Reset color
	glColor3f(1, 1, 1);

	// Draw sun as a yellow sphere with yellow material emission. Radius is 20.0f
	glPushMatrix();
	GLfloat material_Ke[] = { lightEmissionColor.x / 255.0f, lightEmissionColor.y / 255.0f, lightEmissionColor.z / 255.0f, 0.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
	//glMaterialf(GL_FRONT, GL_SHININESS, material_Se);

	glTranslatef(lightPos.x, lightPos.y, lightPos.z);

	// Yellow sphere
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tex_moon);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	//gluSphere(qobj, 300, 100, 100);

	//colorRGB(250, 203, 20);
	colorRGB(lightColor.x, lightColor.y, lightColor.z);

	//colorRGB(147, 163, 177);
	gluSphere(qobj, 10.0f, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();

	// reset the material
	GLfloat emissionColor[] = { 0,0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
	//glDisable(GL_LIGHTING);

	glPopMatrix();

	// Reset color
	glColor3f(1, 1, 1);


	//sky box
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();

	//GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex_sky);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 300, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();



	//enable2D();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	//glDepthMask(GL_FALSE);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1600, 0, 900);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	menuUI();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_BLEND);
	//enable3D();

	// Restore OpenGL states
	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);*/

	//glutSwapBuffers();
	glFlush();
}

void VillageLevel() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//setupCamera();
	cameraFP();
	setupLights();

	bgColorRGB(171, 201, 229, 1);


	glColor3f(1.0f, 1.0f, 1.0f);


	// Ground
	RenderGround();

	//// Draw torch Model
	//GLfloat emissionColor[] = { 0,0,0,0 }; // Specify the emission color (RGBA)

	//glPushMatrix();
	//GLfloat material_Ka[] = { 0.11,0.06, 0.11, 1.00 };
	//GLfloat material_Kd[] = { 0.43, 0.47, 0.54, 1.00 };
	////GLfloat material_Ks[] = { 0.33, 0.33, 0.52, 1.00 };
	//GLfloat material_Ks[] = { 1,1,1, 1.00 };
	GLfloat torchEm[] = { 1.0, 1.0, 0.2, 0.00 };
	//GLfloat material_Se = 10;

	////glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
	////glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
	////glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
	////glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
	////glMaterialf(GL_FRONT, GL_SHININESS, material_Se);

	GLfloat emissionColor[] = { 0,0,0,0 };
	if (!steve->isDead) {
		glPushMatrix();
		// enable light 1
		glEnable(GL_LIGHT1);

		glMaterialfv(GL_FRONT, GL_EMISSION, torchEm);

		glTranslatef(torchPos.x, torchPos.y, torchPos.z);
		//glScalef(.10,.10,.1);
		//glRotatef(90.f, 0, 0, 1);

		model_torch.Draw();
		model_torch.scale = 0.1;

		////glPushMatrix();
		////glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
		
		////// reset the material
		glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
		////glDisable(GL_LIGHTING);
		////glPopMatrix();

		glPopMatrix();
	}

	//glPopMatrix();


	// DRAW STEVE
	glPushMatrix();
	steve->isMoving = motion.Forward || motion.Backward || motion.Left || motion.Right;
	steve->Move(true);

	glPushMatrix();
	if (!thirdPerson)
	{
		glRotatef(yaw, 0, 1, 0);
		glRotatef(pitch, 1, 0, 0);
		glRotatef(pistolRot, 0, 1, 0);

		//float offset = steve->currentWeapon->xOffset;
		glTranslatef((pistolX) * 1.3, -0.05, -0.15);
	}

	if (thirdPerson)
	{
		if (faceCamera) {
			glRotatef(yaw, 0, 1, 0);
		}
		else {
			float extraRot = mouseRightDown ? 15 : 10;
			glRotatef(yaw - extraRot, 0, 1, 0);
		}
	}

	steve->Look(yaw, (thirdPerson && faceCamera) ? -pitch : pitch);

	// Draw Steve (if not dead)
	if (!steve->isDead)
	{
		steve->Draw(thirdPerson, true, pistolRecoilAngle);
	}
	glPopMatrix();

	glPopMatrix();

	// Reset color
	glColor3f(1, 1, 1);



	// draw dragon
	glPushMatrix();
	glTranslatef(5, 8.0, 2);
	//glScaled(0.5, 0.5, 0.5);
	model_dragon.Draw();
	model_dragon.scale = 1;

	//float dragRot = dragonWingsAngle

	// set z rotation of objects 1 and 2
	model_dragon.Objects[1].rot.z = 5 - dragonWingsAngle;
	model_dragon.Objects[2].rot.z = -5 + dragonWingsAngle;
	/*model_dragon.Objects[1].rot.z = -0;
	model_dragon.Objects[2].rot.z = 0;*/

	// objects 1 and 2 are the wings
	model_dragon.Objects[1].pos.x = -1.5 * sin(dragonWingsAngle * TO_RADIANS);
	model_dragon.Objects[1].pos.y = 1 * sin(dragonWingsAngle * TO_RADIANS);

	model_dragon.Objects[2].pos.x = 1.5 * sin(dragonWingsAngle * TO_RADIANS);
	model_dragon.Objects[2].pos.y = 1 * sin(dragonWingsAngle * TO_RADIANS);
	glPopMatrix();

	// draw houses
	drawHouses();

	// mountain at - 30 x
	glPushMatrix();
	glTranslatef(25, -1.5, -50);
	glRotatef(90, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_mountain.Draw();
	model_mountain.scale = villageScale;
	glPopMatrix();

	// mountain at - 30 x
	glPushMatrix();
	glTranslatef(-25, -1.5, 40);
	glRotatef(-90, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_mountain.Draw();
	model_mountain.scale = villageScale;
	glPopMatrix();

	// mountain behind
	glPushMatrix();
	glTranslatef(-50, -1.5, -35);
	glRotatef(180, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_mountain.Draw();
	model_mountain.scale = villageScale;
	glPopMatrix();


	// draw church
	church->draw();
	if (church->isDestroyed) {
		gameState = "gameover";
	}

	// draw portal
	glPushMatrix();
	glTranslatef(0, 0, 0);
	//glRotatef(90, 0, 1, 0);
	model_portal.Draw();
	model_portal.scale = 0.35;
	glPopMatrix();

	model_portal.Objects[3].pos.y = isPortalOpen ? 0 : -10;

	// draw skeletons
	glPushMatrix();
	for (Skeleton* skeleton : skeletons) {
		// Check which of the player and goal is closer to the skeleton
		// and make the skeleton target that one
		float distToPlayer = sqrt(pow(skeleton->x - steve->x, 2) + pow(skeleton->z - steve->z, 2));
		float distToGoal = sqrt(pow(skeleton->x - church->x, 2) + pow(skeleton->z - church->z, 2));
		if (!steve->isDead && distToPlayer < distToGoal) {
			skeleton->target = steve;
		}
		else {
			skeleton->target = church;
		}

		skeleton->lookAtPlayer();
		skeleton->draw(true);
	}
	glPopMatrix();

	// reset color
	//glColor3f(1, 1, 1);

	// draw zombie
	// draw all zombies in the array
	glPushMatrix();
	for (Zombie* zombie : zombies) {
		// Check which of the player and goal is closer to the zombie
		// and make the zombie target that one
		float distToPlayer = sqrt(pow(zombie->x - steve->x, 2) + pow(zombie->z - steve->z, 2));
		float distToGoal = sqrt(pow(zombie->x - church->x, 2) + pow(zombie->z - church->z, 2));
		if (!steve->isDead && distToPlayer < distToGoal) {
			zombie->target = steve;
		}
		else {
			zombie->target = church;
		}

		zombie->lookAtPlayer();
		zombie->draw(true);

		// prevent enemy from overlapping with each other
		for (Enemy* enemy : enemies) {
			if (enemy != zombie) {
				// check if the enemy is overlapping with another enemy
				enemy->isOverlapping(zombie);
			}
		}
	}
	glPopMatrix();

	//reset color
	//colorRGB(255, 255, 255);

	// Hearts
	drawHearts();

   // Reset color
	glColor3f(1, 1, 1);




	// Draw sun as a yellow sphere with yellow material emission. Radius is 20.0f
	glPushMatrix();
	/*GLfloat material_Ka[] = { 0.11,0.06, 0.11, 1.00 };
	GLfloat material_Kd[] = { 0.43, 0.47, 0.54, 1.00 };
	GLfloat material_Ks[] = { 0.33, 0.33, 0.52, 1.00 };*/

	//GLfloat material_Ke[] = { 250.0f/255.0f, 80 /255.0f, 20/255.0f, 0.0 };
	//GLfloat material_Ke[] = { 47/255.0f, 63 /255.0f, 77/255.0f, 0.0 };
	GLfloat material_Ke[] = { lightEmissionColor.x / 255.0f, lightEmissionColor.y / 255.0f, lightEmissionColor.z / 255.0f, 0.0 };
	//GLfloat material_Ke[] = { 1,1,0, 0.0 };
	//GLfloat material_Se = 10;

	//glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
	glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
	//glMaterialf(GL_FRONT, GL_SHININESS, material_Se);

	glTranslatef(lightPos.x, lightPos.y, lightPos.z);

	// Yellow sphere
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tex_moon);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	//gluSphere(qobj, 300, 100, 100);

	//colorRGB(250, 203, 20);
	colorRGB(lightColor.x, lightColor.y, lightColor.z);

	//colorRGB(147, 163, 177);
	gluSphere(qobj, 10.0f, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();

	// reset the material
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
	//glDisable(GL_LIGHTING);

	glPopMatrix();

	// Reset color
	glColor3f(1, 1, 1);


	//sky box
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();

	//GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex_sky);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 300, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();



	//enable2D();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	//glDepthMask(GL_FALSE);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1600, 0, 900);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	renderText();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_BLEND);
	glFlush();
}

void NetherLevel() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//setupCamera();
	cameraFP();
	setupLights();

	// (100, 15, 19)
	bgColorRGB(100, 15, 19, 1);


	glColor3f(1.0f, 1.0f, 1.0f);


	// Ground
	//RenderGroundNether();

	//// Draw torch Model
	//GLfloat emissionColor[] = { 0,0,0,0 }; // Specify the emission color (RGBA)

	//glPushMatrix();
	//GLfloat material_Ka[] = { 0.11,0.06, 0.11, 1.00 };
	//GLfloat material_Kd[] = { 0.43, 0.47, 0.54, 1.00 };
	////GLfloat material_Ks[] = { 0.33, 0.33, 0.52, 1.00 };
	//GLfloat material_Ks[] = { 1,1,1, 1.00 };
	GLfloat torchEm[] = { 1.0, 1.0, 0.2, 0.00 };
	//GLfloat material_Se = 10;

	////glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
	////glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
	////glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
	////glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
	////glMaterialf(GL_FRONT, GL_SHININESS, material_Se);

	GLfloat emissionColor[] = { 0,0,0,0 };
	if (!steve->isDead) {
		glPushMatrix();
		// enable light 1
		glEnable(GL_LIGHT1);

		glMaterialfv(GL_FRONT, GL_EMISSION, torchEm);

		glTranslatef(torchPos.x, torchPos.y, torchPos.z);
		//glScalef(.10,.10,.1);
		//glRotatef(90.f, 0, 0, 1);

		model_torch.Draw();
		model_torch.scale = 0.1;

		////glPushMatrix();
		////glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);

		////// reset the material
		glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
		////glDisable(GL_LIGHTING);
		////glPopMatrix();

		glPopMatrix();
	}

	//glPopMatrix();


	// DRAW STEVE
	glPushMatrix();
	steve->isMoving = motion.Forward || motion.Backward || motion.Left || motion.Right;
	steve->Move(true);

	glPushMatrix();
	if (!thirdPerson)
	{
		glRotatef(yaw, 0, 1, 0);
		glRotatef(pitch, 1, 0, 0);
		glRotatef(pistolRot, 0, 1, 0);

		//float offset = steve->currentWeapon->xOffset;
		glTranslatef((pistolX) * 1.3, -0.05, -0.15);
	}

	if (thirdPerson)
	{
		if (faceCamera) {
			glRotatef(yaw, 0, 1, 0);
		}
		else {
			float extraRot = mouseRightDown ? 15 : 10;
			glRotatef(yaw - extraRot, 0, 1, 0);
		}
	}

	steve->Look(yaw, (thirdPerson && faceCamera) ? -pitch : pitch);

	// Draw Steve (if not dead)
	if (!steve->isDead)
	{
		steve->Draw(thirdPerson, true, pistolRecoilAngle);
	}
	glPopMatrix();

	glPopMatrix();

	// Reset color
	glColor3f(1, 1, 1);



	// draw dragon
	glPushMatrix();
	glTranslatef(5, 8.0, 2);
	//glScaled(0.5, 0.5, 0.5);
	model_dragon.Draw();
	model_dragon.scale = 1;

	//float dragRot = dragonWingsAngle

	// set z rotation of objects 1 and 2
	model_dragon.Objects[1].rot.z = 5 - dragonWingsAngle;
	model_dragon.Objects[2].rot.z = -5 + dragonWingsAngle;
	/*model_dragon.Objects[1].rot.z = -0;
	model_dragon.Objects[2].rot.z = 0;*/

	// objects 1 and 2 are the wings
	model_dragon.Objects[1].pos.x = -1.5 * sin(dragonWingsAngle * TO_RADIANS);
	model_dragon.Objects[1].pos.y = 1 * sin(dragonWingsAngle * TO_RADIANS);

	model_dragon.Objects[2].pos.x = 1.5 * sin(dragonWingsAngle * TO_RADIANS);
	model_dragon.Objects[2].pos.y = 1 * sin(dragonWingsAngle * TO_RADIANS);
	glPopMatrix();

	// draw houses
	drawHouses();


	/////////////
	// TERRAIN //
	/////////////

	//////////////////////////// GROUND ////////////////////////////
	// draw nether ground
	glPushMatrix();
	glTranslatef(0, 0.01, 39.5);
	model_nether_ground.Draw();
	model_nether_ground.scale = villageScale;
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0.01, -30);
	model_nether_ground.Draw();
	model_nether_ground.scale = villageScale;
	glPopMatrix();

	//////////////////////////// ROOF ////////////////////////////
	// draw nether ground
	glPushMatrix();
	glTranslatef(0, 11, 39.5);
	glRotatef(180, 1, 0, 0);
	model_nether_ground.Draw();
	model_nether_ground.scale = villageScale;
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 11, -30);
	glRotatef(180, 1, 0, 0);
	model_nether_ground.Draw();
	model_nether_ground.scale = villageScale;
	glPopMatrix();

	// draw lava pit
	//glPushMatrix();
	//glTranslatef(0, 0.05, 50);
	//model_lava_pit.Draw();
	//model_lava_pit.scale = villageScale;
	//glPopMatrix();

	//// mountain at - 30 x
	//glPushMatrix();
	//glTranslatef(25, 0, -50);
	//glRotatef(90, 0, 1, 0);
	////glScaled(0.5, 0.5, 0.5);
	//model_nether_wall.Draw();
	//model_nether_wall.scale = villageScale;
	//glPopMatrix();


	////////////////
	// RIGHT SIDE //
	////////////////

	// mountain at - 30 x
	glPushMatrix();
	glTranslatef(-20, -0.5, -32);
	glRotatef(-90, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_nether_wall.Draw();
	model_nether_wall.scale = villageScale;
	glPopMatrix();
	
	// mountain at - 30 x
	glPushMatrix();
	glTranslatef(-20, -0.5, 10);
	glRotatef(-90, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_nether_wall.Draw();
	model_nether_wall.scale = villageScale;
	glPopMatrix();

	/////////////////////////////////////////////////
	// 
	////////////////
	// LEFT SIDE //
	////////////////

	// mountain at - 30 x
	glPushMatrix();
	glTranslatef(20, -0.5, -32);
	glRotatef(90, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_nether_wall.Draw();
	model_nether_wall.scale = villageScale;
	glPopMatrix();
	
	// mountain at - 30 x
	glPushMatrix();
	glTranslatef(20, -0.5, 10);
	glRotatef(90, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_nether_wall.Draw();
	model_nether_wall.scale = villageScale;
	glPopMatrix();

	/////////////////////////////////////////////////

	// mountain behind left
	glPushMatrix();
	glTranslatef(-15, -0.5, -35);
	glRotatef(180, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_nether_wall.Draw();
	model_nether_wall.scale = villageScale;
	glPopMatrix();

	// mountain behind right
	glPushMatrix();
	glTranslatef(27, -0.5, -35);
	glRotatef(180, 0, 1, 0);
	//glScaled(0.5, 0.5, 0.5);
	model_nether_wall.Draw();
	model_nether_wall.scale = villageScale;
	glPopMatrix();


	// draw church
	church->draw();
	if (church->isDestroyed) {
		gameState = "gameover";
	}

	// draw portal
	glPushMatrix();
	glTranslatef(0, 0, 0);
	//glRotatef(90, 0, 1, 0);
	model_portal.Draw();
	model_portal.scale = 0.35;
	glPopMatrix();

	model_portal.Objects[3].pos.y = isPortalOpen ? 0 : -10;

	// draw skeletons
	glPushMatrix();
	for (Skeleton* skeleton : skeletons) {
		// Check which of the player and goal is closer to the skeleton
		// and make the skeleton target that one
		float distToPlayer = sqrt(pow(skeleton->x - steve->x, 2) + pow(skeleton->z - steve->z, 2));
		float distToGoal = sqrt(pow(skeleton->x - church->x, 2) + pow(skeleton->z - church->z, 2));
		if (!steve->isDead && distToPlayer < distToGoal) {
			skeleton->target = steve;
		}
		else {
			skeleton->target = church;
		}

		skeleton->lookAtPlayer();
		skeleton->draw(true);
	}
	glPopMatrix();

	// reset color
	//glColor3f(1, 1, 1);

	// draw zombie
	// draw all zombies in the array
	glPushMatrix();
	for (Zombie* zombie : zombies) {
		// Check which of the player and goal is closer to the zombie
		// and make the zombie target that one
		float distToPlayer = sqrt(pow(zombie->x - steve->x, 2) + pow(zombie->z - steve->z, 2));
		float distToGoal = sqrt(pow(zombie->x - church->x, 2) + pow(zombie->z - church->z, 2));
		if (!steve->isDead && distToPlayer < distToGoal) {
			zombie->target = steve;
		}
		else {
			zombie->target = church;
		}

		zombie->lookAtPlayer();
		zombie->draw(true);

		// prevent enemy from overlapping with each other
		for (Enemy* enemy : enemies) {
			if (enemy != zombie) {
				// check if the enemy is overlapping with another enemy
				enemy->isOverlapping(zombie);
			}
		}
	}
	glPopMatrix();

	

	//reset color
	//colorRGB(255, 255, 255);

	// Hearts
	drawHearts();

	// Reset color
	glColor3f(1, 1, 1);




	//// Draw sun as a yellow sphere with yellow material emission. Radius is 20.0f
	//glPushMatrix();
	///*GLfloat material_Ka[] = { 0.11,0.06, 0.11, 1.00 };
	//GLfloat material_Kd[] = { 0.43, 0.47, 0.54, 1.00 };
	//GLfloat material_Ks[] = { 0.33, 0.33, 0.52, 1.00 };*/

	////GLfloat material_Ke[] = { 250.0f/255.0f, 80 /255.0f, 20/255.0f, 0.0 };
	////GLfloat material_Ke[] = { 47/255.0f, 63 /255.0f, 77/255.0f, 0.0 };
	//GLfloat material_Ke[] = { lightEmissionColor.x / 255.0f, lightEmissionColor.y / 255.0f, lightEmissionColor.z / 255.0f, 0.0 };
	////GLfloat material_Ke[] = { 1,1,0, 0.0 };
	////GLfloat material_Se = 10;

	////glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
	////glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
	////glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
	//glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
	////glMaterialf(GL_FRONT, GL_SHININESS, material_Se);

	//glTranslatef(lightPos.x, lightPos.y, lightPos.z);

	//// Yellow sphere
	//glPushMatrix();

	GLUquadricObj* qobj;
	//qobj = gluNewQuadric();
	//glTranslated(50, 0, 0);
	//glRotated(90, 1, 0, 0);
	//glBindTexture(GL_TEXTURE_2D, tex_moon);
	//gluQuadricTexture(qobj, true);
	//gluQuadricNormals(qobj, GL_SMOOTH);
	////gluSphere(qobj, 300, 100, 100);

	////colorRGB(250, 203, 20);
	//colorRGB(lightColor.x, lightColor.y, lightColor.z);

	////colorRGB(147, 163, 177);
	//gluSphere(qobj, 10.0f, 100, 100);
	//gluDeleteQuadric(qobj);


	//glPopMatrix();

	//// reset the material
	//glMaterialfv(GL_FRONT, GL_EMISSION, emissionColor);
	////glDisable(GL_LIGHTING);

	//glPopMatrix();

	// Reset color
	glColor3f(1, 1, 1);


	////sky box
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();



	//GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(45, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex_sky);
	gluQuadricTexture(qobj, true);

	// color : (63, 27, 25)
	//colorRGB(63, 27, 25);

	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 300, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();

	// red sphere with radius 250
	glPushMatrix();

	qobj = gluNewQuadric();
	glTranslatef(50, 0, 0);
	//glRotatef(90, 0, 1, 0);
	colorRGB(156, 44, 41);
	gluSphere(qobj, 250, 100, 100);
	glPopMatrix();




	//enable2D();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	//glDepthMask(GL_FALSE);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1600, 0, 900);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	renderText();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_BLEND);
	glFlush();
}

void Display() {
	if (gameState == "menu") {
		MenuScreen();
		return;
	}
	else if (gameState == "gameover") {
		//gameState = "gameover";
		GameOverScreen();
		return;
	}
	else if (gameState == "village") {
		//gameState = "gameover";
		VillageLevel();
		return;
	}
	else if (gameState == "nether") {
		//gameState = "gameover";
		NetherLevel();
		return;
	}

	
}

// Houses
Vector3f housePositions[] = {
	Vector3f(-10, 0, -10),
	Vector3f(-10, 0, 10),
	Vector3f(10, 0, -10),
	Vector3f(10, 0, 10),

	//Vector3f(15, 0, 12.5)
};

float houseRotations[] = {
	0,
	0,
	180,
	180
	//-90
};
void drawHouses() {
	model_house.scale = villageScale;
	model_nether_stone.scale = 0.2;

	// array of Vector3f for house positions
	// array of float for house rotations
	

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
			glTranslatef(housePositions[i].x, housePositions[i].y, housePositions[i].z);
			glRotatef(houseRotations[i], 0, 1, 0);
			if(gameState == "village")
				model_house.Draw();
			else if (gameState == "nether")
				model_nether_stone.Draw();
			//model_house.Draw();

			// draw cube with scaled x and z
			//glPushMatrix();
			//	glTranslatef(0, 1.5, 0);
			//	glScalef(4.5, 3, 3.5);
			//	glutSolidCube(1);
			//glPopMatrix();
		glPopMatrix();
	}

	/*glPushMatrix();
		glTranslatef(-5, 0, 10);
		model_house.Draw();
	glPopMatrix();*/
}

void GameOverScreen() {
	enable2D();
	glColor3f(0, 0, 0);

	//printf("You lost!\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//bgColorRGB(171, 201, 229, 1);
	// dark grey bg
	bgColorRGB(30,30,30, 1);

	//BLUE_GREY_COLOR();
	glColor3f(1, 0, 0);
	printStroke(screenW / 2 - 220, screenH / 1.5, "GAME OVER", 0.5, 7);

	char waveT[100];
	sprintf(waveT, "You survived %i waves", wave->waveNumber);
	printStroke(screenW / 2 - 210, screenH / 2, (char *)waveT, 0.25, 3);

	char scoreText[20];
	sprintf(scoreText, "SCORE %i", score);
	printStroke(screenW / 2 - 160, screenH / 3, (char *)scoreText, 0.3, 3);


	float opacity = (sin(textOpacity * 3.1415 / 180) + 1) / 2;
	colorRGBA(65, 90, 105, opacity);
	// display this if the player is within 0.2 units of the seesaw
	// calculate distance between player and seesaw
	printStroke(screenW / 2 - 195, screenH / 3.8, "Press r to restart", 0.25, 3);

	glFlush();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {
	case 'i':
		camera.moveY(d);
		break;
	case 'k':
		camera.moveY(-d);
		break;
	case 'j':
		camera.moveX(d);
		break;
	case 'l':
		camera.moveX(-d);
		break;
	case 'u':
		camera.moveZ(d);
		break;
	case 'o':
		camera.moveZ(-d);
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	//glutPostRedisplay();
}

void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		if (thirdPerson)
			//targetAngle += a*2;
			cameraLeft = true;
		else
			camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		if (thirdPerson)
			//targetAngle -= a*2;
			cameraRight = true;
		else
			camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void SpecialUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		cameraLeft = false;
		break;
	case GLUT_KEY_RIGHT:
		cameraRight = false;
		break;
	}
}



void CameraKeyboard(unsigned char k, int x, int y) {
	if (k == '1') {
		camera.frontView();
	}
	if (k == '2') {
		camera.sideView();
	}
	if (k == '3') {
		camera.topView();
	}
	if (k == 'c') {
		thirdPerson = !thirdPerson;
	}
}

void decrementTime(int value)
{
	if (timeLeft <= 0)
	{
		timeLeft = 0;
		printf("Game Over\n");
		hasLost = true;
		return;
	}
	timeLeft -= 1;
	glutPostRedisplay();
	glutTimerFunc(1000, decrementTime, 0);
}

void restartGame() {
	// reset all the variables
	//reachedGoal = false;
	//hasLost = false;
	//hasWon = false;
	//timeLeft = maxTime;
	//textOpacity = 0;
	//ridingSeesaw = false;
	//ridingFerrisWheel = false;
	//lampPostAnimating = false;
	//lampPostScaleY = 1;
	//lampPostAngle = 0;
	//seesawRot = 0;
	//ferrisWheelRot = 0;
	steve->x = 2;
	steve->z = 3.8;

	//glutTimerFunc(0, decrementTime, 0);
}
void startGame() {
	wave = new Wave();

	steve = new Player(0.2, "textures/player/steve/");
	steve->currentWeapon = pistol;
	steve->HoldGun();

	// Church
	church = new Goal(0, 0, -30, 10000, model_church, villageScale);

	// HUD
	hud = new HUD(screenW, screenH, steve, church, wave);

	// Enemies
	LoadEnemies();

	gameState = "village";
}
void key(unsigned char k, int x, int y)
{

	//if (k == 'd')
	//{
	//	targetSpeed = (steve->x == maxX - playerW / 2) ? 0 : moveSpeed;
	//	if (!thirdPerson) targetAngle = 0; else playerDir = 270;
	//}
	//if (k == 'a')
	//{
	//	targetSpeed = (steve->x == minX + playerW / 2) ? 0 : moveSpeed;
	//	if (!thirdPerson) targetAngle = 180; else playerDir = 90;
	//}
	//if (k == 'w')
	//{
	//	targetSpeed = (steve->z == maxZ - playerW / 2) ? 0 : moveSpeed;
	//	if (!thirdPerson) targetAngle = 90; else playerDir = 0;
	//}
	//if (k == 's')
	//{
	//	targetSpeed = (steve->z == minZ + playerW / 2) ? 0 : moveSpeed;
	//	if (!thirdPerson) targetAngle = 270; else playerDir = 180;
	//}

	//// Ride seesaw
	//if (k == 'f' && withinSeesaw) {
	//	ridingSeesaw = !ridingSeesaw;
	//	ridingFerrisWheel = false;
	//}
	//// Ride ferris wheel
	//if (k == 'g' && withinFerrisWheel) {
	//	ridingFerrisWheel = !ridingFerrisWheel;
	//	ridingSeesaw = false;
	//}

	//// Animate Lamppost
	//if (k == 'z') {
	//	lampPostAnimating = !lampPostAnimating;
	//}
	//// Animate Trashcan
	//if (k == 'x') {
	//	trashcanAnimating = !trashcanAnimating;
	//}
	//// Animate tree
	//if (k == 'v') {
	//	if (animatingTreeTop || animatingTreeMiddle || animatingTreeBottom) {
	//		animatingTreeTop = false;
	//		animatingTreeBottom = false;
	//		animatingTreeMiddle = false;
	//		treeY = 0;
	//	}
	//	else {
	//		animatingTreeTop = true;
	//		animatingTreeBottom = false;
	//		animatingTreeMiddle = false;
	//	}
	//}

	////Restart Game
	//if (k == 'r' && (hasLost || hasWon)) {
	//	// reset all the variables
	//	restartGame();
	//}

	//Keyboard(k, x, y);
	//CameraKeyboard(k, x, y);

	//glutPostRedisplay();
}

void keyUp(unsigned char k, int x, int y)
{
	// std::cout << "The key released is: " << k << "\n";

	if (k == 'd')
	{
		targetSpeed = 0;
	}
	if (k == 'a')
	{
		targetSpeed = 0;
	}
	if (k == 'w')
	{
		targetSpeed = 0;
	}
	if (k == 's')
	{
		targetSpeed = 0;
	}

	glutPostRedisplay();
}


void animateText(int value)
{
	textOpacity += 2.0f;
	glutPostRedisplay();
	glutTimerFunc(5, animateText, 0);
}

// PISTOL ANIMATION
void pistolRecoil(int value) {
	int delay = 10;
	float speed = 0.09f;
	float maxAngle = 4.0f;

	if (isRightRotation) {
		if (pistolAnimCurTime < pistolAnimDuration) {
			float t = pistolAnimCurTime / pistolAnimDuration; // Normalize time

			// Use the ease-in ease-out function to control animation
			float alpha = easeInOutQuad(t);

			pistolRecoilAngle = maxAngle * (2 * alpha - 1); // Rotates 10° to the left
			pistolRecoilAngle += maxAngle;

			pistolAnimCurTime += speed; // Adjust this value for animation speed
			glutPostRedisplay();
			glutTimerFunc(delay, pistolRecoil, 0);
		}
		else {
			isRightRotation = false;
			pistolAnimCurTime = 0.0f;
			glutTimerFunc(delay, pistolRecoil, 0);
		}
	}
	else {
		if (pistolAnimCurTime < pistolAnimDuration) {
			float t = pistolAnimCurTime / pistolAnimDuration; // Normalize time

			// Use the ease-in ease-out function to control animation
			float alpha = easeInOutQuad(t);

			pistolRecoilAngle = -maxAngle * (2 * alpha - 1); // Rotates 10° to the right
			pistolRecoilAngle += maxAngle;

			pistolAnimCurTime += speed/5.0; // Adjust this value for animation speed
			glutPostRedisplay();
			glutTimerFunc(delay, pistolRecoil, 0);
		}
		else {
			isRightRotation = true;
			pistolAnimCurTime = 0.0f;
			pistolRecoilAngle = 0.0f;

			isAnimatingPistol = false;
			return;
			//glutTimerFunc(delay, pistolRecoil, 0);
		}
	}
}

// animate dragon wings from -10 to 20 degrees using ease in out
void animateDragonWings(int value) {
	// animate dragon wings
	// Range is -10 to 20 degrees
	// Speed is 10 degrees / second
	int delay = 10;
	float speed = 0.012f;
	float maxAngle = 15.0f;

	if (dragonWingsAnimating) {
		if (dragonWingsAnimCurTime < dragonWingsAnimDuration) {
			float t = dragonWingsAnimCurTime / dragonWingsAnimDuration; // Normalize time

			// Use the ease-in ease-out function to control animation
			float alpha = easeInOutQuad(t);

			dragonWingsAngle = maxAngle * (2 * alpha - 1); // Rotates 10° to the left
			dragonWingsAngle += maxAngle;

			dragonWingsAnimCurTime += speed; // Adjust this value for animation speed
			glutPostRedisplay();
			glutTimerFunc(delay, animateDragonWings, 0);
		}
		else {
			dragonWingsAnimating = false;
			dragonWingsAnimCurTime = 0.0f;
			glutTimerFunc(delay, animateDragonWings, 0);
		}
	}
	else {
		if (dragonWingsAnimCurTime < dragonWingsAnimDuration) {
			float t = dragonWingsAnimCurTime / dragonWingsAnimDuration; // Normalize time

			// Use the ease-in ease-out function to control animation
			float alpha = easeInOutQuad(t);

			dragonWingsAngle = -maxAngle * (2 * alpha - 1); // Rotates 10° to the right
			dragonWingsAngle += maxAngle;

			dragonWingsAnimCurTime += speed / 1.2; // Adjust this value for animation speed
			glutPostRedisplay();
			glutTimerFunc(delay, animateDragonWings, 0);
		}
		else {
			dragonWingsAnimating = true;
			dragonWingsAnimCurTime = 0.0f;
			dragonWingsAngle = 0.0f;
			glutTimerFunc(delay, animateDragonWings, 0);
		}
	}
}


// timer function to set canShoot to true
void resetGunCanShoot(int value) {
	steve->currentWeapon->canShoot = true;
	glutPostRedisplay();
}


void reloadWeapon(int value) {
	if (steve->currentWeapon->totalAmmo <= 0 && steve->currentWeapon->ammo <= 0) {
		steve->currentWeapon->canShoot = false;
	}
	else {
		int minimum = (steve->currentWeapon->maxAmmo - steve->currentWeapon->ammo);
		if (steve->currentWeapon->totalAmmo < minimum) {
			minimum = steve->currentWeapon->totalAmmo;
		}
		steve->currentWeapon->totalAmmo -= minimum;
		steve->currentWeapon->ammo += minimum;

		steve->currentWeapon->isReloading = false;
		steve->currentWeapon->canShoot = true;
	}
}

void startShootingProcedure() {
	isAnimatingPistol = true;
	steve->currentWeapon->canShoot = false;

	if (steve->currentWeapon->name == "scar") {
		// play sound
		scar_sound->play(true);
	}
	else if(steve->currentWeapon->name == "pistol") {
		// play sound
		//pistol_sound->play(true);
		pistol_sound->play(true);
	}
	else {
		sniper_sound->play(true);
	}

	glutPostRedisplay();

	// According to gun fireRate , set canShoot to false
	glutTimerFunc( (int)(1000 * steve->currentWeapon->fireRate), resetGunCanShoot, 0);

	// start animation
	glutTimerFunc(0, pistolRecoil, 0);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~ TEXTURES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	tex_ground.Load("Textures/grass.bmp");
	tex_path.Load("Textures/path.bmp");
	logo.Load("Textures/zombiecraft.png");
	tex_ammo.Load("Textures/ammo.png");
	//loadBMP(&tex_sky, "Textures/skybox.bmp", true);
	loadBMP(&tex_sky, "Textures/blu-sky-3.bmp", true);
	loadBMP(&tex_moon, "Textures/moon.bmp", true);


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~ MODELS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//model_church.Load("Models/village/house/Pueblo.3ds");
	model_church.Load("Models/village/house/church2.3ds");

	model_house.Load("Models/village/house/house.3ds");

	model_mountain.Load("Models/village/house/mountain.3ds");

	model_nether_ground.Load("Models/nether/netherGround.3ds");
	model_lava_pit.Load("Models/nether/lavaPit.3ds");
	model_nether_roof.Load("Models/nether/netherRoof.3ds");
	model_nether_wall.Load("Models/nether/netherWall.3ds");
	model_nether_stone.Load("Models/nether/netherStone.3ds");

	//model_tree.Load("Models/tree/Tree1.3ds");
	//model_creeper.Load("Models/creeper/creeper.3ds");
	//model_sword.Load("Models/sword/sword.3ds");

	//model_pistol.Load("Models/pistol/pistolNew.3ds");
	model_pistol.Load("Models/pistol/yellow/pistol.3ds");
	//model_shotgun.Load("Models/shotgun/shotgun.3ds");


	model_torch.Load("Models/torch/torch.3ds");
	//model_village.Load("Models/village/villageNew/village.3ds");

	//model_village.Load("Models/city/City.3ds");

	//model_nether.Load("Models/nether/nether.3ds");

	model_heart.Load("Models/collectibles/heart.3ds");
	
	model_dragon.Load("Models/dragon/dragon2.3ds");

	model_zombie.Load("Models/zombie/zombie.3ds");
	model_piglin.Load("Models/piglin/piglin.3ds");
	model_piglin.scale = 0.65;
	model_piglin.rot.y = -90;

	//model_bow.Load("Models/skeleton/bow_attack.3ds");
	model_bow.Load("Models/skeleton/bow.3ds");
	model_arrow.Load("Models/skeleton/arrow.3ds");

	model_scar.Load("Models/ak/gun.3ds");
	model_sniper.Load("Models/sniper/sniper.3ds");
	
	model_skeleton.Load("models/skeleton/skeleton.3ds");

	model_portal.Load("Models/portal/portal.3ds");

	//print the dragon objects
	printf("\n\n");
	printf("Number of objects of skeleton: %d\n", model_skeleton.numObjects);
	for (int i = 0; i < model_skeleton.numObjects; i++)
	{
		printf("Object %d: %s\n", i, model_skeleton.Objects[i].name);
	}

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~ SOUNDS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// Weapon(int _maxAmmo, float _damage, float _fireRate, float _reloadTime, float _accuracy, float _range, Model_3DS _model, float _modelScale);
	pistol = new Pistol(10, 40, 0.4, 1, 0.9, 10, model_pistol, 0.3);
	scar = new Scar(30, 20, 0.1, 1, 0.9, 15, model_scar, 0.15);
	sniper = new Sniper(5, 100, 1.6, 2, 0.9, 30, model_sniper, 0.05);


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~ OBJECTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	wave = new Wave();

	steve = new Player(0.2, "textures/player/steve/");
	steve->currentWeapon = pistol;
	steve->HoldGun();

	// Church
	church = new Goal(0, 0, -30, 10000, model_church, villageScale);


	// LOAD SOUNDS
	bg_music = new Sound("sounds/bg2.mp3", true);

	pistol_sound = new Sound("sounds/pistol.mp3", false);
	pistol_sound->setVolume(0.3);

	scar_sound = new Sound("sounds/scar.mp3", false);
	scar_sound->setVolume(0.3);

	sniper_sound = new Sound("sounds/SniperSound.mp3", false);
	sniper_sound->setVolume(0.6);

	// PLAY BG MUSIC
	bg_music->play(true);

}

void LoadEnemies() {
	// Start wave 1
	spawnEnemies();

}

bool isDay = true;
bool changeDayState = true;

void changeDay(int value) {
	changeDayState = true;
	printf("Changing day state\n");
}

float moonIntensity = 0.001;
float sunIntensity = 0.7;
// timer function to decrease them over time to 0.01, then increase again to 0.7.
void changeIntensity(int value) {
	if (!changeDayState) {
		glutTimerFunc(100, changeIntensity, 0);
		return;
	}
	// Day: Intensity 0.7, Color: sunColor, EmissionColor: sunEmissionColor
	// Night: Intensity 0.01, Color: moonColor, EmissionColor: moonEmissionColor
	// change intensityX, intensityY, intensityZ, lightColor, lightEmissionColor from day to night values.
	// they must all reach the end values at the same time.

	// Rate of change in percentage
	float rate = 0.005f;

	float intensityDiff = moonIntensity - sunIntensity;
	Vector3f colorDiff = moonColor - sunColor;
	Vector3f emissionDiff = moonEmissionColor - sunEmissionColor;

	if (isDay) {
		// Day to night
		if (intensityX > moonIntensity) {
			intensityX += rate * intensityDiff;
			intensityY += rate * intensityDiff;
			intensityZ += rate * intensityDiff;

			lightColor.x += rate * colorDiff.x;
			lightColor.y += rate * colorDiff.y;
			lightColor.z += rate * colorDiff.z;

			lightEmissionColor.x += rate * emissionDiff.x;
			lightEmissionColor.y += rate * emissionDiff.y;
			lightEmissionColor.z += rate * emissionDiff.z;
		}
		else {
			isDay = false;
			changeDayState = false;
			printf("Night\n");
			// start timer to change back to day
			glutTimerFunc(10000, changeDay, 0);
		}
	}
	else {
		// Night to day
		if (intensityX < sunIntensity) {
			intensityX -= rate * intensityDiff;
			intensityY -= rate * intensityDiff;
			intensityZ -= rate * intensityDiff;

			lightColor.x -= rate * colorDiff.x;
			lightColor.y -= rate * colorDiff.y;
			lightColor.z -= rate * colorDiff.z;

			lightEmissionColor.x -= rate * emissionDiff.x;
			lightEmissionColor.y -= rate * emissionDiff.y;
			lightEmissionColor.z -= rate * emissionDiff.z;
		}
		else {
			isDay = true;
			changeDayState = false;
			printf("Day\n");
			// start timer to change back to night
			glutTimerFunc(10000, changeDay, 0);
		}
	}



	glutPostRedisplay();
	glutTimerFunc(100, changeIntensity, 0);
}




void init()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	//glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glutWarpPointer(width / 2, height / 2);
	glutWarpPointer(screenW / 2, screenH / 2);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//GLenum err = glewInit();

	//if (GLEW_OK != err)
	//{
	//	// Problem: glewInit failed, something is seriously wrong.
	//	printf("Error: %s\n", glewGetErrorString(err));
	//}

	//// Initialize glText
	//if (!gltInit())
	//{
	//	printf("Failed to initialize glText\n");
	//}
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	//srand(static_cast<unsigned int>(time(nullptr)));

	glutInitWindowSize(screenW, screenH);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("ZombieCraft Survival");
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);

	glutTimerFunc(0, animateText, 0);

	// FP
	glutPassiveMotionFunc(passive_motion);
	glutMotionFunc(passive_motion);
	glutTimerFunc(0, timer, 0);    //more info about this is given below at definition of timer()
	glutKeyboardFunc(keyboardFP);
	glutKeyboardUpFunc(keyboard_upFP);
	glutMouseFunc(mouseFP);

	glutTimerFunc(0, changeIntensity, 0);
	glutTimerFunc(0, animateDragonWings, 0);

	/*glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);*/


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	init();

	LoadAssets();

	//LoadEnemies();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}


bool inPortal = false;
void playerCollisions() {
	// Check if player is within boundaries
	if (steve->x > maxX - steve->width / 2) {
		steve->x = maxX - steve->width / 2;
	}
	if (steve->x < minX + steve->width / 2) {
		steve->x = minX + steve->width / 2;
	}
	if (steve->z > maxZ - steve->width / 2) {
		steve->z = maxZ - steve->width / 2;
	}
	if (steve->z < minZ + steve->width / 2) {
		steve->z = minZ + steve->width / 2;
	}

	if(isPortalOpen) {
	//if(true) {
		// Check if player is colliding with portal at (0,0,0)
		float portalW = 1;
		float portalL = 3;

		if (steve->x > -portalL / 2 && steve->x < portalL / 2 && steve->z > -portalW / 2 && steve->z < portalW / 2) {
			//printf("Reached portal\n");
			//reachedGoal = true;
			//hasWon = true;
			//return;
			inPortal = true;
		}
		else {
			if (inPortal) {
				printf("Left portal\n");
				inPortal = false;
				isPortalOpen = false;
				if (gameState == "village") {
					gameState = "nether";
				}
				else if (gameState == "nether") {
					gameState = "village";
				}

				spawnEnemies();

				//// Loop on all zombies and set their "isNether" to true if gameState is nether
				//for (int i = 0; i < zombies.size(); i++) {
				//	zombies[i]->inNether = (gameState == "nether");
				//}

			}
		}
	}

}



/// FIRST PERSON ///
//#include <GL/glut.h>
//#include <math.h>



int main2(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Projectile Motion - 3D Simulation");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(passive_motion);
	glutTimerFunc(0, timer, 0);    //more info about this is given below at definition of timer()
	glutKeyboardFunc(keyboardFP);
	glutKeyboardUpFunc(keyboard_upFP);

	glutMainLoop();
	return 0;
}

/* This function just draws the scene. I used Texture mapping to draw
   a chessboard like surface. If this is too complicated for you ,
   you can just use a simple quadrilateral */

void draw()
{
	/*glEnable(GL_TEXTURE_2D);
	GLuint texture;
	glGenTextures(1, &texture);

	unsigned char texture_data[2][2][4] =
	{
		0,0,0,255,  255,255,255,255,
		255,255,255,255,    0,0,0,255
	};

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);  glVertex3f(-50.0, -5.0, -50.0);
	glTexCoord2f(25.0, 0.0);  glVertex3f(50.0, -5.0, -50.0);
	glTexCoord2f(25.0, 25.0);  glVertex3f(50.0, -5.0, 50.0);
	glTexCoord2f(0.0, 25.0);  glVertex3f(-50.0, -5.0, 50.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);*/
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	cameraFP();
	draw();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	/*glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 16.0 / 9.0, 1, 75);
	glMatrixMode(GL_MODELVIEW);*/

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, screenW / screenH, 0.001, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


/*this funtion is used to keep calling the display function periodically
  at a rate of FPS times in one second. The constant FPS is defined above and
  has the value of 60
*/
void timer(int)
{
	glutPostRedisplay();
	if(mouseTrackingEnabled) glutWarpPointer(screenW / 2, screenH / 2);
	glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y)
{
	if(!mouseTrackingEnabled) return;

	float mouseSlowDown = 60.0f;
	/* two variables to store X and Y coordinates, as observed from the center
	  of the window
	*/
	int dev_x, dev_y;
	dev_x = (screenW / 2) - x;
	dev_y = (screenH / 2) - y;

	/* apply the changes to pitch and yaw*/
	yaw += (float)dev_x / mouseSlowDown;
	pitch += (float)dev_y / mouseSlowDown;

	if (mouseLeftDown) {
		shoot();
	}
}

bool isCollidingWithHouses(float dx, float dz) {
	//float offset = 0.65;

	float houseW = gameState == "nether" ? 5 : 4;
	float houseL = gameState == "nether" ? 7 : 4.8;

	for (int i = 0; i < 4; i++) {
		Vector3f pos = housePositions[i];

		// check using x + or - houseL/2 and z + or - houseW/2
		// Check if player will collide with house and prevent him
		if (steve->x + dx > pos.x - houseL / 2 && steve->x + dx < pos.x + houseL / 2 && steve->z + dz > pos.z - houseW / 2 && steve->z + dz < pos.z + houseW / 2) {
			return true;
		}
	}

	// house width is 3, length is
	return false;
}

bool isCollidingWithChurch(float dx, float dz) {
	float offset = 0.65;
	Vector3f goalB1 = church->B1();
	goalB1.x -= offset;
	goalB1.z -= offset;

	Vector3f goalB2 = church->B2();
	goalB2.x += offset;
	goalB2.z += offset;

	// Check if player will collide with church and prevent him
	if (steve->x + dx > goalB1.x && steve->x + dx < goalB2.x && steve->z + dz > goalB1.z && steve->z + dz < goalB2.z) {
		return true;
	}
	return false;
}

bool isCollidingWithObstacles(float dx, float dz) {
	return isCollidingWithChurch(dx, dz) || isCollidingWithHouses(dx, dz);
}


void cameraFP()
{

	//print old values
	//printf("camX: %f, camZ: %f\n", camX, camZ);

	// Boundaries: X: -35 to 35, Z: -35 to 35

	Vector3f goalB1 = church->B1();
	Vector3f goalB2 = church->B2();

	if (motion.Forward)
	{
		float dx = cos((yaw + 90) * TO_RADIANS) * playerSpeed / 100;
		float dz = -sin((yaw + 90) * TO_RADIANS) * playerSpeed / 100;
		// Check if player will collide with church and prevent him
		if (isCollidingWithObstacles(dx, dz)) {

		}
		else {
			steve->x += dx;
			steve->z += dz;
		}
	}
	if (motion.Backward)
	{
		float dx = cos((yaw + 90 + 180) * TO_RADIANS) * playerSpeed / 100;
		float dz = -sin((yaw + 90 + 180) * TO_RADIANS) * playerSpeed / 100;

		// Check if player will collide with church and prevent him
		if (isCollidingWithObstacles(dx, dz)) {
		}
		else {
			steve->x += dx;
			steve->z += dz;
		}
	}
	if (motion.Left)
	{
		float dx = cos((yaw + 90 + 90) * TO_RADIANS) * playerSpeed / 100;
		float dz = -sin((yaw + 90 + 90) * TO_RADIANS) * playerSpeed / 100;

		// Check if player will collide with church and prevent him
		if (isCollidingWithObstacles(dx, dz)) {
		}
		else {
			steve->x += dx;
			steve->z += dz;
		}
	}
	if (motion.Right)
	{
		float dx = cos((yaw + 90 - 90) * TO_RADIANS) * playerSpeed / 100;
		float dz = -sin((yaw + 90 - 90) * TO_RADIANS) * playerSpeed / 100;

		// Check if player will collide with church and prevent him
		if (isCollidingWithObstacles(dx, dz)) {

		}
		else {
			steve->x += dx;
			steve->z += dz;
		}
	}
	if (motion.Up)
	{
		steve->y += 0.1;
	}
	if (motion.Down)
	{
		steve->y -= 0.1;
	}
	
	playerCollisions();

	//print new values
	//printf("camX: %f, camZ: %f\n", camX, camZ);

	/*limit the values of pitch
	  between -60 and 70
	*/
	if (pitch >= 70)
		pitch = 70;
	if (pitch <= -60)
		pitch = -60;


	if(!thirdPerson)	
	{
		//cameraX,Y,Z same as players's
		cameraX = steve->x;
		cameraY = steve->y;
		cameraZ = steve->z;
		glRotatef(-pitch, 1.0, 0.0, 0.0); // Along X axis
		glRotatef(-yaw, 0.0, 1.0, 0.0);    //Along Y axis
		glTranslatef(-cameraX, -cameraY, -cameraZ);
	}
	else {
		// Third Person Camera
		float xOffset = faceCamera ? 0 : 0.25f; // Adjust this value as needed
		// Calculate the position to the right of the player
		centerX = steve->x + xOffset * cos((yaw) * TO_RADIANS);
		centerY = steve->y; // Adjust for pitch
		centerZ = steve->z - xOffset * sin((yaw) * TO_RADIANS);


		float distanceFromPlayer = mouseRightDown ? 0.4f : 2.5f; // Adjust this distance as needed

		float cameraYaw = faceCamera ? yaw + 180 : yaw;
		//float cameraPitch = faceCamera ? -pitch : pitch;
		float cameraPitch = pitch;

		cameraX = centerX - distanceFromPlayer * cos((cameraYaw + 90 ) * TO_RADIANS) * cos(cameraPitch * TO_RADIANS);
		cameraY = centerY - distanceFromPlayer * sin(cameraPitch * TO_RADIANS);
		cameraZ = centerZ + distanceFromPlayer * sin((cameraYaw + 90 ) * TO_RADIANS) * cos(cameraPitch * TO_RADIANS);

		// Limit cameraY to be above the ground
		if (cameraY < 0) {
			cameraY = 0;
		}

		/*if (faceCamera) {
			cameraX = -cameraX;
			cameraZ = -cameraZ;
		}*/

		//glLoadIdentity(); // Reset the modelview matrix

		//glLoadIdentity(); // Reset the modelview matrix
		gluLookAt(
			cameraX, cameraY, cameraZ,
			centerX, centerY, centerZ,
			0.0, 1.0, 0.0);
	}


	// torchPos to the left of the player
	float xOffset = -0.15f;
	float yOffset = -0.15f;
	float zOffset = -0.3f;
	// Calculate the position to the right of the player
	torchPos.x = steve->x + xOffset * cos((yaw)*TO_RADIANS) + zOffset * sin((yaw)*TO_RADIANS);
	torchPos.y = steve->y + yOffset;
	torchPos.z = steve->z - xOffset * sin((yaw)*TO_RADIANS) + zOffset * cos((yaw)*TO_RADIANS);

	//torchPos.x = centerX;
	//torchPos.y = centerY;
	//torchPos.z = centerZ;
}

void keyboardFP(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':
		motion.Forward = true;
		break;
	case 'A':
	case 'a':
		motion.Left = true;
		break;
	case 'S':
	case 's':
		motion.Backward = true;
		break;
	case 'D':
	case 'd':
		motion.Right = true;
		break;

		// Q and E for up and down
	case 'Q':
	case 'q':
		motion.Up = true;
		break;
	case 'E':
	case 'e':
		motion.Down = true;
		break;
	// Jump
	case ' ':
		//motion.Up = true;
		steve->Jump();
		break;

	case 'c':
		thirdPerson = !thirdPerson;
		break;
	case 'v' :
		faceCamera = true;
		break;

	case '1' :
		steve->currentWeapon = pistol;
		steve->HoldGun();
		break;
	case '2':
		steve->currentWeapon = scar;
		steve->HoldGun();
		break;
	case '3':
		steve->currentWeapon = sniper;
		steve->HoldGun();
		break;
	//case 'g':
	//	skeletons[0]->shootAtPlayer(steve);
	//	break;



	// pause the mouse tracking:
	case 'p':
		mouseTrackingEnabled = !mouseTrackingEnabled;
		break;
	// esc closes the game
	case 27:
		exit(0);
		break;

	// Enter key to start game
	case 13:
		if (gameState == "menu") {
			startGame();
		}
		break;
	case 'r':
		printf("R Pressed\n");
		// restart game
		if (gameState == "gameover")
		{
			gameState = "menu";
			// clear enemies
			enemies.clear();
			zombies.clear();
			skeletons.clear();

			glutPostRedisplay();
			printf("Restarting game\n");
		}
		else {
			steve->currentWeapon->canShoot = false;
			steve->currentWeapon->isReloading = true;
			float delay = 0;

			if (!(steve->currentWeapon->totalAmmo <= 0)) {
				delay = (int)(1000 * steve->currentWeapon->reloadTime);
			}

			printf("DELAY %f", delay);
			glutTimerFunc(delay, reloadWeapon, 0);
		}
		break;

	}
}
void keyboard_upFP(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':
		motion.Forward = false;
		break;
	case 'A':
	case 'a':
		motion.Left = false;
		break;
	case 'S':
	case 's':
		motion.Backward = false;
		break;
	case 'D':
	case 'd':
		motion.Right = false;
		break;
	case 'Q':
	case 'q':
		motion.Up = false;
		break;
	case 'E':
	case 'e':
		motion.Down = false;
		break;

	case 'v':
		faceCamera = false;
		break;
	}
}

void mouseFP(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{ 
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
			//do something if left mouse is clicked

			shoot();
		}
		else if (state == GLUT_UP)
		{
			//do something if left mouse is released
			mouseLeftDown = false;
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			//do something if right mouse is clicked
			mouseRightDown = true;
			pistolRot = 0;
			pistolX = -0.0125;
			playerSpeed = aimSpeed;

		}
		else if (state == GLUT_UP)
		{
			//do something if right mouse is released
			mouseRightDown = false;
			pistolRot = 10;
			pistolX = pistolXOrig + steve->currentWeapon->xOffset / 5;
			playerSpeed = runSpeed;
		}
	}
}

std::vector<Enemy*> enemiesToDelete;

void reload()
{
	steve->currentWeapon->canShoot = false;
	steve->currentWeapon->isReloading = true;
	glutTimerFunc((int)(1000 * steve->currentWeapon->reloadTime), reloadWeapon, 0);
}

void shoot() {
	if (steve->isDead) return;
	// Shoot
	if (steve->currentWeapon->canShoot) {
		if ((steve->currentWeapon->ammo > 1 ))
		{
			steve->currentWeapon->ammo--;
			startShootingProcedure();
		}
		else {
			reload();
		}
		// Sort zombies by nearest to player using Euclidean distance
		std::sort(enemies.begin(), enemies.end(), [&](Enemy* a, Enemy* b) {
			float distA = sqrt(pow(a->x - steve->x, 2) + pow(a->z - steve->z, 2) + pow(a->y - steve->y, 2));
			float distB = sqrt(pow(b->x - steve->x, 2) + pow(b->z - steve->z, 2) + pow(b->y - steve->y, 2));

			return distA < distB;
			});

		for (Enemy* enemy : enemies) {
			Vector3f B1 = enemy->B1();
			Vector3f B2 = enemy->B2();

			// L1: camera coords
			Vector3f L1 = Vector3f(cameraX, cameraY, cameraZ);

			// L2: point 10 units in front of camera along the camera's direction using (yaw, pitch)
			float range = steve->currentWeapon->range;
			//float yawOffset = thirdPerson ? 8 : 0;

			Vector3f L2;
			if (!thirdPerson)
			{
				L2 = Vector3f(cameraX + range * cos((yaw + 90) * TO_RADIANS) * cos(pitch * TO_RADIANS),
					cameraY + range * sin(pitch * TO_RADIANS),
					cameraZ - range * sin((yaw + 90) * TO_RADIANS) * cos(pitch * TO_RADIANS));
			}
			else {
				// the direction is from the camera to the centerX, centerY, centerZ
				// calculate the yaw and pitch between the camera and the center
				float dx = centerX - cameraX;
				float dy = centerY - cameraY;
				float dz = centerZ - cameraZ;

				float yawTP = -(atan2(dz, dx) * TO_DEGREES - 270);
				float pitchTP = atan2(dy, sqrt(dx * dx + dz * dz)) * TO_DEGREES;

				L2 = Vector3f(cameraX + range * cos((yawTP + 90) * TO_RADIANS) * cos(pitchTP * TO_RADIANS),
					cameraY + range * sin(pitchTP * TO_RADIANS),
					cameraZ - range * sin((yawTP + 90) * TO_RADIANS) * cos(pitchTP * TO_RADIANS));
			}

			Vector3f hitPoint = Vector3f(0, 0, 0);
			bool hit = CheckLineBox(B1, B2, L1, L2, hitPoint);

			if (hit) {
				// Red Color
				glColor3f(1, 0, 0);

				int dmg = steve->currentWeapon->damage;

				bool died;

				if (hitPoint.y > B2.y - 0.2) {
					printf("Hit head!\n");
					// red
					//colorRGB(255, 0, 0);
					//print3D(enemy->x, enemy->y + 1.5, enemy->z, "25", enemy->rotY);
					died = enemy->hit(dmg * 2, true);

				}
				else {
					printf("Hit!\n");
					//print3D(enemy->x, enemy->y + 2.5, enemy->z, "25", enemy->rotY);
					died = enemy->hit(dmg, false);

					//printf("Hit Point: (%f, %f, %f)\n", hitPoint.x, hitPoint.y, hitPoint.z);
				}
				// Reset color
				glColor3f(1, 1, 1);

				printf("Hit Point: (%f, %f, %f)\n", hitPoint.x, hitPoint.y, hitPoint.z);
				//isAnimatingPistol = true;

				if (died) {
					// add to enemiesToDelete
					enemiesToDelete.push_back(enemy);

					// place heart at the enemy's position
					// it should have a 50% chance of dropping a heart
					int randNum = rand() % 10;
					if (randNum < 5)
						hearts.push_back(Vector3f(enemy->x, enemy->y, enemy->z));

					// Place ammo at the enemy's position
					// it should have a 50% chance of dropping ammo
					randNum = rand() % 10;
					if (randNum < 5)
						ammos.push_back(new Ammo(enemy->x + 0.3, enemy->y, enemy->z, tex_ammo));
				}

				// dont hit any more zombies
				if(steve->currentWeapon->name != "sniper") break;
				else {
				}
			}
			else {
				//printf("Miss!\n");
			}
		}

		// Erase enemies after the loop
		for (Enemy* enemy : enemiesToDelete) {
			// remove from enemies array
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());

			// remove from zombies array
			if (std::find(zombies.begin(), zombies.end(), enemy) != zombies.end()) {
				zombies.erase(std::remove(zombies.begin(), zombies.end(), enemy), zombies.end());

				// cast to zombie
				Zombie* zombie = (Zombie*)enemy;
				Zombie::zombieInstances.erase(zombie->instanceID);
			}
			// remove from skeletons array
			else if (std::find(skeletons.begin(), skeletons.end(), enemy) != skeletons.end()) {
				skeletons.erase(std::remove(skeletons.begin(), skeletons.end(), enemy), skeletons.end());

				// cast to skeleton
				Skeleton* skeleton = (Skeleton*)enemy;
				Skeleton::skeletonInstances.erase(skeleton->instanceID);
			}

			delete enemy;

			// Increment score
			score += 10;
		}

		// Check if all enemies are dead
		if(!isPortalOpen)
		{
			if (enemies.size() == 0) {
				printf("All enemies dead!\n");
				printf("Wave %d complete!\n", wave->waveNumber);

				// Start next wave
				wave->waveOver();

				if (wave->waveNumber % 3 == 0) {
					isPortalOpen = true;
				}
				else {
					spawnEnemies();
				}

			}
		}

		// Clear the temporary vector
		enemiesToDelete.clear();
	}
}

void spawnEnemies() {
	printf("Spawning wave %d\n", wave->waveNumber);
	// spawn a zombie every 5 seconds
	// numZombies and numSkeletons from wave
	// distance from church from wave
	// spawn them at random angle around the church within a certain distance

	// clear the arrays
	zombies.clear();
	skeletons.clear();
	enemies.clear();

	for (int i = 0; i < wave->numZombies; i++) {
		// Z range: 30 to 45
		// X range: -30 to 30
		float x = rand() % 60 - 30;
		float z = rand() % 15 + 30;

		// Spawn zombie
		Zombie* zombie = new Zombie(x, 0.45, z, 0, 150, model_zombie, model_piglin, church);
		zombie->inNether = (gameState == "nether");

		//Zombie* zombie = new Zombie(x, 0, z, 0, 150, model_piglin, church);
		zombies.push_back(zombie);
		enemies.push_back(zombie);
	}

	for (int i = 0; i < wave->numSkeletons; i++) {
		// Z range: 30 to 45
		// X range: -30 to 30
		float x = rand() % 60 - 30;
		float z = rand() % 15 + 30;

		/*Model_3DS model_skeleton2;
		model_skeleton2.Load("models/skeleton/skeleton.3ds");*/

		// Spawn skeleton
		Skeleton* skeleton = new Skeleton(x, 0.45, z, 0, 150, model_skeleton, model_bow, model_arrow, church);
		skeletons.push_back(skeleton);
		enemies.push_back(skeleton);
	}
}

