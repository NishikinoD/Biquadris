#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <iostream>
#include <string>
#include <vector>
#include "Grid.h"
#include "Cell.h"
#include "window.h"


class Block {
/*    std::vector<Cell *> shape;
    std::vector<Cell *> neighbours; */
    protected:
    Grid *g;
    int lb_x; // x coordinates of the left-bot corner
    int lb_y; // y coordinates of the left-bot corner
    int state = 0; // keep track of the rotated shape
    bool is_heavy = false;

public:
    // four operations on blocks
    Block(Grid *g, int x, int y);
    virtual void print() = 0;
    virtual void init() = 0;
    virtual void down() = 0;
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void drop() = 0;
    virtual void rotate(std::string) = 0;
    virtual bool reachBot() = 0;
    virtual void heavy() = 0;
    virtual void nDown(int n) = 0;
    virtual void nLeft(int n) = 0;
    virtual void nRight(int n) = 0;
    virtual void nRotate(int n, std::string s) = 0;
    virtual Xwindow::c getcolour() = 0;
    
    // accessors & mutators
    bool get_heavy();
    void set_heavy();
    virtual std::vector<std::shared_ptr<Cell>> getShape() = 0;
    virtual std::string getName() = 0;
    

};


#endif
