#ifndef _GRID_H_
#define _GRID_H_
#include <iostream>
#include <vector>
#include "Cell.h"
#include "level.h"
#include <memory>
#include "window.h"

class Block;

class Grid {
    int row = 18;
    int col = 11;
    int countStep = 0;
    std::vector<std::vector<std::shared_ptr<Cell>>> theGrid;
    int score = 0;
    int hi = 0;
    int clearedrows = 0;
    std::shared_ptr<Block> curblock = nullptr;
    std::shared_ptr<Block> nextblock = nullptr;
    bool is_blind = false;
    int last_cleared = 0;
    std::shared_ptr<Level> level = nullptr;
    
public:
    std::shared_ptr <Xwindow> xp = nullptr;
    void clearGrid();
    void init();
    void recalculate();
    bool gameOver();
    void prettyprint();

    // accessors & mutators
    std::shared_ptr<Cell> get(int x, int y);
    void set_score(int);
    int get_score();
    int get_hi();
    int get_last_cleared();
    int getclearedrow();
    std::shared_ptr<Level> get_level();
    void set_level(std::shared_ptr<Level>);
    std::shared_ptr<Block> get_cur();
    std::shared_ptr<Block> get_next();
    void set_cur(std::shared_ptr<Block>);
    void set_next(std::shared_ptr<Block>);
    
    // special effects
    void set_blind();
    void force(std:: string);

};


#endif
