
#include "Goal.h"
#include <Vector3f.h>
#include <corecrt_math_defines.h>
#include <glut.h>

bool GetIntersection3(float fDst1, float fDst2, Vector3f P1, Vector3f P2, Vector3f& Hit);
bool InBox3(Vector3f Hit, Vector3f B1, Vector3f B2, int Axis);
bool CheckLineBox3(Vector3f B1, Vector3f B2, Vector3f L1, Vector3f L2, Vector3f& Hit);
bool CheckPointBox3(Vector3f point, Vector3f B1, Vector3f B2);

Goal::Goal(float x, float y, float z, int _maxHp, Model_3DS _model, float _modelScale) :
    model(_model), modelScale(_modelScale), x(x), y(y), z(z), maxHp(_maxHp), hp(_maxHp) {
    // Set model scale
    model.scale = modelScale;

    isPlayer = false;
}

Goal::~Goal() {
    // Cleanup code
    delete this;
}

void Goal::draw() {
    glPushMatrix();
        glTranslatef(x, y, z);
        model.Draw();

    glPopMatrix();
}

void Goal::hit(int damage) {
    hp -= damage;
    if (hp < 0) {
        hp = 0;
        // Game Over
    }

    printf("Goal hp: %d\n", hp);
}

bool Goal::CheckCollisionWithArrow(float arrowX, float arrowY, float arrowZ, float arrowRotV, float arrowRotH) {
    // use bool CheckPointBox(Vector3f point, Vector3f B1, Vector3f B2) from collision.hpp
    Vector3f arrowPos = Vector3f(arrowX, arrowY, arrowZ);

    Vector3f B1 = Vector3f(
        x - width / 2,
		y,
		z - depth / 2
    );

    Vector3f B2 = Vector3f(
        x + width / 2,
        y + height,
        z + depth / 2);

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



    return CheckLineBox3(B1, B2, arrowTip, arrowTail, arrowTip);
    return false;
}

Vector3f Goal::B1() {
    return Vector3f(
		x - width / 2,
		y,
		z - depth / 2
	);
}

Vector3f Goal::B2() {
    return Vector3f(
		x + width / 2,
		y + height,
		z + depth / 2
	);
}






/// ZEHEGT ///
bool GetIntersection3(float fDst1, float fDst2, Vector3f P1, Vector3f P2, Vector3f& Hit);

bool InBox3(Vector3f Hit, Vector3f B1, Vector3f B2, int Axis);

bool CheckLineBox3(Vector3f B1, Vector3f B2, Vector3f L1, Vector3f L2, Vector3f& Hit) {
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
    if ((GetIntersection3(L1.x - B1.x, L2.x - B1.x, L1, L2, Hit) && InBox3(Hit, B1, B2, 1))
        || (GetIntersection3(L1.y - B1.y, L2.y - B1.y, L1, L2, Hit) && InBox3(Hit, B1, B2, 2))
        || (GetIntersection3(L1.z - B1.z, L2.z - B1.z, L1, L2, Hit) && InBox3(Hit, B1, B2, 3))
        || (GetIntersection3(L1.x - B2.x, L2.x - B2.x, L1, L2, Hit) && InBox3(Hit, B1, B2, 1))
        || (GetIntersection3(L1.y - B2.y, L2.y - B2.y, L1, L2, Hit) && InBox3(Hit, B1, B2, 2))
        || (GetIntersection3(L1.z - B2.z, L2.z - B2.z, L1, L2, Hit) && InBox3(Hit, B1, B2, 3)))
        return true;

    return false;
}

bool GetIntersection3(float fDst1, float fDst2, Vector3f P1, Vector3f P2, Vector3f& Hit) {
    if ((fDst1 * fDst2) >= 0.0f) return false;
    if (fDst1 == fDst2) return false;
    Hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
    return true;
}

bool InBox3(Vector3f Hit, Vector3f B1, Vector3f B2, int Axis) {
    if (Axis == 1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y) return true;
    if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x) return true;
    if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y) return true;
    return false;
}


bool CheckPointBox3(Vector3f point, Vector3f B1, Vector3f B2) {
    Vector3f dummyHit;
    return CheckLineBox3(B1, B2, point, point, dummyHit);
}