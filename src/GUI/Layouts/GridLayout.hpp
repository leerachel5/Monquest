#ifndef GridLayout_hpp
#define GridLayout_hpp

#include <vector>
#include "Layout.hpp"


template <typename T>
class GridLayout : public Layout<T> {
public:
    GridLayout();
    GridLayout(int x, int y, int w, int h, int numRows, int numColumns);
    ~GridLayout() override;
    
    // Mutator member functions
    void addObject(T object, int row, int col);
    void removeObject(int row, int col);
    
    // Main loop functions
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void draw() override;
    
private:
    std::vector<std::vector<T>> grid;
    SDL_Rect cell;
};

template <typename T>
GridLayout<T>::GridLayout() {}

template <typename T>
GridLayout<T>::GridLayout(int x, int y, int w, int h, int numRows, int numColumns)
: Layout<T>(x, y, w, h) {
    grid = std::vector<std::vector<T>>(numRows, std::vector<T>(numColumns));
}

template <typename T>
GridLayout<T>::~GridLayout() {}

template <typename T>
void GridLayout<T>::addObject(T object, int row, int col) {
    grid.at(row).at(col) = object;
}

template <typename T>
void GridLayout<T>::removeObject(int row, int col) {
    std::vector<T> gridRow = grid.at(row);
    gridRow.erase(gridRow.begin() + col);
}

template <typename T>
void GridLayout<T>::init() {
    // Calculate cell sizes
    if (grid.size() > 0) {
        cell.w = this->w / grid[0].size();
        cell.h = this->h / grid.size();
    }
    
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            T obj = grid[r][c];
            std::cout << r << "," << c << std::endl;

            obj->init();
            
            // Calculate cell position
            cell.x = this->x + c * cell.w;
            cell.y = this->y + r * cell.h;
            
            // Map object to cell
            obj->destRect.x = cell.x;
            obj->destRect.y = cell.y;
            
            obj->destRect.w = cell.w;
            obj->destRect.h = cell.h;
        }
    }
}

template <typename T>
void GridLayout<T>::handleEvents(SDL_Event& event) {
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            grid[r][c]->handleEvents(event);
        }
    }
}

template <typename T>
void GridLayout<T>::update() {
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            grid[r][c]->update();
        }
    }
}

template <typename T>
void GridLayout<T>::draw() {
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            grid[r][c]->draw();
        }
    }
}

#endif /* GridLayout_hpp */
