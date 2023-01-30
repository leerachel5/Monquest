#ifndef Collision_hpp
#define Collision_hpp

#include <SDL2/SDL.h>

class ColliderComponent;

class Collision {
public:
    struct Direction {
        bool N, S, E, W;
        
        Direction() : N{ false }, S{ false }, E{ false }, W{ false } {};
    };
    
public:
    // Axis-Aligned Bounding Box (only works with axis-aligned rectangles)
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
    static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB, Direction& direction);
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB, Direction& direction);
};

#endif /* Collision_hpp */
