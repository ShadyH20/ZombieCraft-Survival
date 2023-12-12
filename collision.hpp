#ifndef COLLISION_H
#define COLLISION_H
#include <Vector3f.h>

bool GetIntersection(float fDst1, float fDst2, Vector3f P1, Vector3f P2, Vector3f& Hit);

bool InBox(Vector3f Hit, Vector3f B1, Vector3f B2, int Axis);

bool CheckLineBox(Vector3f B1, Vector3f B2, Vector3f L1, Vector3f L2, Vector3f& Hit) {
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
    if ((GetIntersection(L1.x - B1.x, L2.x - B1.x, L1, L2, Hit) && InBox(Hit, B1, B2, 1))
        || (GetIntersection(L1.y - B1.y, L2.y - B1.y, L1, L2, Hit) && InBox(Hit, B1, B2, 2))
        || (GetIntersection(L1.z - B1.z, L2.z - B1.z, L1, L2, Hit) && InBox(Hit, B1, B2, 3))
        || (GetIntersection(L1.x - B2.x, L2.x - B2.x, L1, L2, Hit) && InBox(Hit, B1, B2, 1))
        || (GetIntersection(L1.y - B2.y, L2.y - B2.y, L1, L2, Hit) && InBox(Hit, B1, B2, 2))
        || (GetIntersection(L1.z - B2.z, L2.z - B2.z, L1, L2, Hit) && InBox(Hit, B1, B2, 3)))
        return true;

    return false;
}

bool GetIntersection(float fDst1, float fDst2, Vector3f P1, Vector3f P2, Vector3f& Hit) {
    if ((fDst1 * fDst2) >= 0.0f) return false;
    if (fDst1 == fDst2) return false;
    Hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
    return true;
}

bool InBox(Vector3f Hit, Vector3f B1, Vector3f B2, int Axis) {
    if (Axis == 1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y) return true;
    if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x) return true;
    if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y) return true;
    return false;
}


bool CheckPointBox(Vector3f point, Vector3f B1, Vector3f B2) {
    Vector3f dummyHit;
    return CheckLineBox(B1, B2, point, point, dummyHit);
}

#endif
