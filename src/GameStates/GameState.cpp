#include "GameState.hpp"
#include "Game.hpp"
#include "../MapManager.hpp"

GameState::GameState() : mapManager{new MapManager()}, camera{SDL_Rect{0, 0, Game::windowW, Game::windowH}} {}
