#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB) {
    return rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
    return AABB(colA.collider, colB.collider);
}

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB, Direction& direction) {
    if (rectA.y < rectB.y + rectB.h &&
        rectA.y + rectA.h > rectB.y + rectB.h &&
        rectA.x + rectA.w > rectB.x &&
        rectA.x < rectB.x + rectB.w) {
        direction.N = true;
    }
    else if (rectA.y + rectA.h > rectB.y &&
             rectA.y + rectA.h < rectB.y + rectB.h &&
             rectA.x + rectA.w > rectB.x &&
             rectA.x < rectB.x + rectB.w) {
        direction.S = true;
    }
    if (rectA.x + rectA.w > rectB.x &&
             rectA.x + rectA.w < rectB.x + rectB.w &&
             rectA.y < rectB.y + rectB.h &&
             rectA.y + rectA.h > rectB.y) {
        direction.E = true;
    }
    else if (rectA.x < rectB.x + rectB.w &&
             rectA.x > rectB.x &&
             rectA.y < rectB.y + rectB.h &&
             rectA.y + rectA.h > rectB.y) {
        direction.W = true;
    }
    
    return direction.N || direction.S || direction.E || direction.W;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB, Direction& direction) {
    return AABB(colA.collider, colB.collider, direction);
}
