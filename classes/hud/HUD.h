#pragma once

#include <unordered_map>
#include <functional>
#include <textures/Player/Player.h>
#include <classes/goal/Goal.h>
#include <classes/weapon/Weapon.h>
#include <classes/wave/Wave.h>

class HUD {
public:
    int screenW, screenH;
    Player* player;
    Goal* goal;
    Wave* wave;
    GLTexture heart;
    GLTexture heartHalf;
    GLTexture heartEmpty;

    static std::unordered_map<int, Weapon*> inventory;

    void draw();
    void goalHP();

    HUD(int _screenW, int _screenH, Player* _player, Goal* _goal, Wave* _wave);
    ~HUD();

};

