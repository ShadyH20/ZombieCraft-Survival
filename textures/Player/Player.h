// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "Cuboid.h"
#include <Model_3DS.h>
#include <Vector3f.h>
#include <classes/sound/Sound.h>
#include <classes/weapon/Weapon.h>
#include <classes/goal/Goal.h>
//#include <collision.hpp>

class Player : public Goal {
private:
    Cuboid head;
    Cuboid body;
    Cuboid leftArm;
    Cuboid rightArm;
    Cuboid leftLeg;
    Cuboid rightLeg;

    // Box collider
    Cuboid boxCollider;

    const float yOffset = 3.5f * 0.2f;


    // Rotations
    float headYaw = 0.0f;
    float headPitch = 0.0f;

    float leftArmRotX = 0.0f;
    float leftArmRotY = 0.0f;

    float rightArmRotX = 0.0f;
    float rightArmRotY = 0.0f;

    // Speeds
    // gravity
    const float gravity = -0.002f;
    float yVel = 0.0f;
    const float jumpSpeed = 0.07f;

    bool canJump = false;
    bool isJumping = false;

    Vector3f color = Vector3f(1, 1, 1);

    Sound* damageSound;

public:
    static Player* instance;
    // Positions        
    //float x = 0.0f;
    //float y = 0.0f;
    //float z = 0.0f;

    float leftLegRotX = 0.0f;
    float rightLegRotX = 0.0f;

    float legRotSpeed = 10.0f;

    bool isMoving = false;

    int reviveTime = 12000;
    int reviveCountdownTime;
    bool isDead = false;

    Weapon* currentWeapon;

    // HP
 /*   int maxHp = 500;
    int hp = maxHp;*/

    Player(float size, const std::string& texturePath);

    void Draw(bool thirdPerson, bool holdingGun, float pistolRecoilAngle);
    void Look(float yaw, float pitch);
    void HoldGun();
    void UnholdGun();
    void Move(bool allowJump);
    void Jump();

    //timer function
    static void playerTimer(int value);
    static void resetColorCallback(int value);
    static void revivePlayer(int value);
    static void reviveCountdown(int value);

    bool CheckCollisionWithArrow(float arrowX, float arrowY, float arrowZ, float arrowYaw, float arrowPitch) override;
    void hit(int damage) override;
    void heal(int amount);

    Vector3f B1() override;
    Vector3f B2() override;
};

#endif // PLAYER_H
