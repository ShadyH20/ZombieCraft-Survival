// Player.cpp

//#include <Vector3f.h>
//#include <collision.hpp>
#include <corecrt_math_defines.h>
#include "Player.h"
#include <glut.h>
#include <Vector3f.h>

bool GetIntersection2(float fDst1, float fDst2, Vector3f P1, Vector3f P2, Vector3f& Hit);
bool InBox2(Vector3f Hit, Vector3f B1, Vector3f B2, int Axis);
bool CheckLineBox2(Vector3f B1, Vector3f B2, Vector3f L1, Vector3f L2, Vector3f& Hit);
bool CheckPointBox2(Vector3f point, Vector3f B1, Vector3f B2);

Player* Player::instance = nullptr;

Player::Player(float size, const std::string& texturePath)
    :
    Goal(0.0f, 0.0f, 0.0f, 500, Model_3DS(), 1.0f),
    head(size, size, size, texturePath + "head/"),
    body(size, 1.5f * size, 0.5f * size, texturePath + "body/"),
    leftArm(0.5f * size, 1.5f * size, 0.5f * size, texturePath + "leftArm/"),
    rightArm(0.5f * size, 1.5f * size, 0.5f * size, texturePath + "rightArm/"),
    leftLeg(0.5f * size, 1.5f * size, 0.5f * size, texturePath + "leftLeg/"),
    rightLeg(0.5f * size, 1.5f * size, 0.5f * size, texturePath + "rightLeg/"),
    boxCollider(size, 3.5f * size, size), currentWeapon(nullptr)
{
    isPlayer = true;

    instance = this;

    damageSound = new Sound("sounds/damage.mp3", true);
    
    glutTimerFunc(0, playerTimer, 0);
}

//move
void Player::Move() {

    // Update the player's y position based on the y velocity
    y += yVel;

    // Update the player's y velocity based on gravity
    yVel += gravity;

    //Check if the player is on the ground
    // If the player is on the ground, allow them to jump
    if (y <= yOffset) {
		y = yOffset;
		yVel = 0.0f;
        canJump = true;
    } else {
        canJump = false;
	}


	// Move the player's body
    glTranslatef(x, y, z);
}

//jump
void Player::Jump() {
	// If the player is on the ground, allow them to jump
    //printf("canJump: %d\n", canJump);
	if (canJump) {
		yVel = jumpSpeed;
	}
}


void Player::Draw(bool thirdPerson, Model_3DS gun, float pistolRecoilAngle) {
    //float gunScale = 0.3f;
    glPushMatrix(); // Player
        glColor3f(color.x, color.y, color.z);

        // MOVE TO PLAYER POSITION
        //glTranslatef(x, y, z);

        // Draw the components of the player
        glPushMatrix(); // Head
            if(!thirdPerson) glRotatef(headYaw, 0.0f, 1.0f, 0.0f);
		    glRotatef(thirdPerson? -headPitch : headPitch, 1.0f, 0.0f, 0.0f);
            if(thirdPerson) head.Draw();
        glPopMatrix(); // Head

        glTranslatef(0.0f, -body.GetHeight() / 2 - head.GetHeight() / 2, 0.0f);
        glPushMatrix(); // Body
            // At center of body
            body.Draw();

            glPushMatrix(); // Arms

            // both arms rotation
            glTranslatef(0.0f, 0.1, body.GetDepth() / 4);
                glRotatef(-(thirdPerson ? headPitch - currentWeapon->extraArmRot : 0), 1.0f, 0.0f, 0.0f);
                glTranslatef(0.0f, body.GetHeight() / 2 - 0.1,
                    -body.GetDepth() / 4
                    );

                // LEFT ARM
                glPushMatrix(); // Left Arm
                    glTranslatef(-(body.GetWidth() + leftArm.GetWidth()) / 2,
                        //leftArm.GetHeight()/2,
                        0,
                        0.0f);
                    glRotatef(leftArmRotY, 0.0f, 1.0f, 0.0f);
                    glRotatef(leftArmRotX, 1.0f, 0.0f, 0.0f);
                    glPushMatrix(); // Left Arm Draw
                        glTranslatef(0.0f, -leftArm.GetHeight()/2, 0.0f);
                        leftArm.Draw();
                    glPopMatrix(); // Left Arm Draw
                glPopMatrix(); // Left Arm

                // RIGHT ARM
                glPushMatrix(); // Right Arm
				    glTranslatef(
                        (body.GetWidth() + rightArm.GetWidth()) / 2,
                        //rightArm.GetHeight()/2 
                        - (pistolRecoilAngle * 0.005),
                        + (pistolRecoilAngle * 0.01)
                        //0.0f
                    );
                    glRotatef(rightArmRotY, 0.0f, 1.0f, 0.0f);
				    glRotatef(rightArmRotX + pistolRecoilAngle, 1.0f, 0.0f, 0.0f);
				    glPushMatrix(); // Right Arm Draw
					    glTranslatef(0.0f,
                            -rightArm.GetHeight()/2,
                            //0,
                            0.0f);
					    rightArm.Draw();

                        glTranslatef(0.038 + currentWeapon->handRightOffset, -0.2, -0.12);
                        glRotatef(-90 + (pistolRecoilAngle * currentWeapon->recoilScale), 1.0f, 0.0f, 0.0f);
                        glRotatef(leftArmRotY + currentWeapon->yRot, 0.0f, 1.0f, 0.0f);
                        glRotatef(currentWeapon->zRot, 0.0f, 0.0f, 1.0f);
                        /*currentWeapon->model.scale = 0.3;
                        gun.scale = gunScale;*/
                        currentWeapon->model.Draw();

                    glPopMatrix(); // Right Arm Draw
                glPopMatrix(); // Right Arm
            glPopMatrix(); // Arms

            // LEGS
            glPushMatrix();  // Legs
                glTranslatef(-body.GetWidth() / 4, -body.GetHeight() / 2, 0.0f);

                // LEFT LEG
                glPushMatrix(); // Left Leg
                    //glTranslatef(-(body.GetWidth() + leftArm.GetWidth()) / 2,
                    //    //leftArm.GetHeight()/2,
                    //    0,
                    //    0.0f);
                    glRotatef(leftLegRotX, 1.0f, 0.0f, 0.0f);
                    glPushMatrix(); // Left Leg Draw
                        glTranslatef(0.0f, -leftLeg.GetHeight() / 2, 0.0f);
                        leftLeg.Draw();
                    glPopMatrix(); // Left Leg Draw
                glPopMatrix(); // Left Leg


                glTranslatef(body.GetWidth() / 2, 0.0f, 0.0f);

                // RIGHT LEG
                glPushMatrix(); // Right Leg
                    //glTranslatef(-(body.GetWidth() + leftArm.GetWidth()) / 2,
                    //    //leftArm.GetHeight()/2,
                    //    0,
                    //    0.0f);
                    glRotatef(-leftLegRotX, 1.0f, 0.0f, 0.0f);
                    glPushMatrix(); // Right Leg Draw
                        glTranslatef(0.0f, -rightLeg.GetHeight() / 2, 0.0f);
                        rightLeg.Draw();
                    glPopMatrix(); // Right Leg Draw
                glPopMatrix(); // Right Leg

            glPopMatrix(); // Legs
        glPopMatrix(); // Body
    glPopMatrix(); // Player

    //glColor3f(1, 1, 1);
}

void Player::Look(float yaw, float pitch) {
	// Rotate the player's head
    headYaw = yaw;
	headPitch = -pitch;
}

void Player::HoldGun() {
    currentWeapon->canShoot = true;
    // rotate both arms infront of the player
    if(!currentWeapon || currentWeapon->name == "pistol") {
        leftArmRotX = 80;
        leftArmRotY = -30;
        rightArmRotX = 90;
        rightArmRotY = 30;
    }
    else if (currentWeapon->name == "scar") {
        leftArmRotX = 75;
        leftArmRotY = -30;
        rightArmRotX = 85;
        rightArmRotY = 30;
    }
}

//void Player::hit() {
//}

// override bool CheckCollisionWithArrow(float arrowX, float arrowY, float arrowZ, float arrowRotV, float arrowRotH)
bool Player::CheckCollisionWithArrow(float arrowX, float arrowY, float arrowZ, float arrowRotV, float arrowRotH) {

    Vector3f arrowPos = Vector3f(arrowX, arrowY, arrowZ);

    Vector3f B1 = Vector3f(
        x - head.GetWidth() / 2,
        y - head.GetHeight() / 2 - body.GetHeight() - leftLeg.GetHeight(),
        z - head.GetDepth() / 2
    );

    Vector3f B2 = Vector3f(
        x + head.GetWidth() / 2,
		y + head.GetHeight() / 2,
		z + head.GetDepth() / 2);

    /*printf("\nPlayer pos: %f, %f, %f\n", x, y, z);
    printf("Arrow pos: %f, %f, %f\n", arrowX, arrowY, arrowZ);
    printf("B1: %f, %f, %f\n", B1.x, B1.y, B1.z);
    printf("B2: %f, %f, %f\n", B2.x, B2.y, B2.z);*/

    // the arrow is 0.4 long
    // arrowX, arrowY, arrowZ is the arrow center
    // arrowRotV is the vertical rotation of the arrow (0 is horizontal, 90 is vertically up, -90 is vertically down)
    // arrowRotH is the y rotation of the arrow from the +ve x axis to the player (0 is pointing to the x axis)
    Vector3f arrowTip = Vector3f(
		arrowX + 0.2 * cos(arrowRotV * M_PI / 180) * cos(arrowRotH * M_PI / 180),
		arrowY + 0.2 * sin(arrowRotV * M_PI / 180),
		arrowZ + 0.2 * cos(arrowRotV * M_PI / 180) * sin(arrowRotH * M_PI / 180)
	);

    Vector3f arrowTail = Vector3f(
        arrowX - 0.2 * cos(arrowRotV * M_PI / 180) * cos(arrowRotH * M_PI / 180),
        arrowY - 0.2 * sin(arrowRotV * M_PI / 180),
        arrowZ - 0.2 * cos(arrowRotV * M_PI / 180) * sin(arrowRotH * M_PI / 180)
    );

    /*printf("\nArrow tail: %f, %f, %f\n", arrowTail.x, arrowTail.y, arrowTail.z);
    printf("Arrow tip: %f, %f, %f\n", arrowTip.x, arrowTip.y, arrowTip.z);*/



	return CheckLineBox2(B1, B2, arrowTip, arrowTail, arrowTip);
    return false;
}


// static void timer(int value)
void Player::playerTimer(int value)
{
    float maxAngle = 30;
    // animate legs if moving
    if(instance->isMoving)
    {
        instance->leftLegRotX += instance->legRotSpeed;
		//instance->rightLegRotX -= instance->legRotSpeed;
		if(instance->leftLegRotX > maxAngle)
		{
			instance->leftLegRotX = maxAngle;
			instance->legRotSpeed = -instance->legRotSpeed;
		}
		else if(instance->leftLegRotX < -maxAngle)
		{
			instance->leftLegRotX = -maxAngle;
			instance->legRotSpeed = -instance->legRotSpeed;
		}
    }
    else {
		instance->leftLegRotX = 0;
		//instance->rightLegRotX = 0;
    }

    glutPostRedisplay();
	glutTimerFunc(30, playerTimer, 0);
}

void Player::hit(int damage) {
    // Hit logic 
    hp -= damage;
    if (hp <= 0) {
		hp = 0;
		// Game over
	}

    // Play damage sound
    damageSound->play(true);

    color = Vector3f(1, 0, 0);
    glutTimerFunc(150, resetColorCallback, 0);

}

void Player::heal(int amount) {
	hp += amount;
    if (hp > maxHp) {
		hp = maxHp;
	}
}

void Player::resetColorCallback(int instanceID) {
        instance->color = Vector3f(1, 1, 1);
        glutPostRedisplay();  // Request a redraw to update the color
};

Vector3f Player::B1() {
    return Vector3f(
		x - head.GetWidth() / 2,
		y - head.GetHeight() / 2 - body.GetHeight() - leftLeg.GetHeight(),
		z - head.GetDepth() / 2
	);
}

Vector3f Player::B2() {
    return Vector3f(
		x + head.GetWidth() / 2,
		y + head.GetHeight() / 2,
		z + head.GetDepth() / 2
	);
}



/// ZEHEGT ///
bool GetIntersection2(float fDst1, float fDst2, Vector3f P1, Vector3f P2, Vector3f& Hit);

bool InBox2(Vector3f Hit, Vector3f B1, Vector3f B2, int Axis);

bool CheckLineBox2(Vector3f B1, Vector3f B2, Vector3f L1, Vector3f L2, Vector3f& Hit) {
    if (L2.x < B1.x && L1.x < B1.x) return false;
    if (L2.x > B2.x && L1.x > B2.x) return false;
    if (L2.y < B1.y && L1.y < B1.y) return false;
    if (L2.y > B2.y && L1.y > B2.y) return false;
    if (L2.z < B1.z && L1.z < B1.z) return false;
    if (L2.z > B2.z && L1.z > B2.z) return false;
    if (L1.x > B1.x && L1.x < B2.x &&
        L1.y > B1.y && L1.y < B2.y &&
        L1.z > B1.z && L1.z < B2.z) {
        Hit = L1;
        return true;
    }
    if ((GetIntersection2(L1.x - B1.x, L2.x - B1.x, L1, L2, Hit) && InBox2(Hit, B1, B2, 1))
        || (GetIntersection2(L1.y - B1.y, L2.y - B1.y, L1, L2, Hit) && InBox2(Hit, B1, B2, 2))
        || (GetIntersection2(L1.z - B1.z, L2.z - B1.z, L1, L2, Hit) && InBox2(Hit, B1, B2, 3))
        || (GetIntersection2(L1.x - B2.x, L2.x - B2.x, L1, L2, Hit) && InBox2(Hit, B1, B2, 1))
        || (GetIntersection2(L1.y - B2.y, L2.y - B2.y, L1, L2, Hit) && InBox2(Hit, B1, B2, 2))
        || (GetIntersection2(L1.z - B2.z, L2.z - B2.z, L1, L2, Hit) && InBox2(Hit, B1, B2, 3)))
        return true;

    return false;
}

bool GetIntersection2(float fDst1, float fDst2, Vector3f P1, Vector3f P2, Vector3f& Hit) {
    if ((fDst1 * fDst2) >= 0.0f) return false;
    if (fDst1 == fDst2) return false;
    Hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
    return true;
}

bool InBox2(Vector3f Hit, Vector3f B1, Vector3f B2, int Axis) {
    if (Axis == 1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y) return true;
    if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x) return true;
    if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y) return true;
    return false;
}


bool CheckPointBox2(Vector3f point, Vector3f B1, Vector3f B2) {
    Vector3f dummyHit;
    return CheckLineBox2(B1, B2, point, point, dummyHit);
}