#pragma once

#include <unordered_map>
#include <functional>
#include <textures/Player/Player.h>
#include <classes/goal/Goal.h>

class Enemy {
public:
    float x, y, z;
    float rotY;
    int hp;
    int maxHp;

    Vector3f color = Vector3f(1, 1, 1);
    Model_3DS model;

    Goal* target;

    static std::unordered_map<int, Enemy*> enemyInstances;

    Enemy(float _x, float _y, float _z, float _rotY, int _maxHp, Model_3DS model, Goal* _goal);
    virtual ~Enemy() = default;

    virtual void lookAtPlayer() = 0;
    virtual void draw() = 0;
    virtual bool hit(int dmg, bool headShot) = 0;

    virtual Vector3f B1() = 0;
    virtual Vector3f B2() = 0;

    float getX();
    float getY();
    float getZ();

    void isOverlapping(Enemy* other);
    void moveAwayFrom(Enemy* other);


protected:

    struct Callbacks {
        std::function<void(int)> resetColor;
        std::function<void(int)> removeDamageText;
    };

    Callbacks callbacks;

    void setResetColorCallback(std::function<void(int)> callback);
    void setRemoveDamageTextCallback(std::function<void(int)> callback);
};

