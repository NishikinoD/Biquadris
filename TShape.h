#ifndef _TSHAPE_H_
#define _TSHAPE_H_
#include "Block.h"


class TShape: public Block {
    std::string name = "T";
    std::vector<std::shared_ptr<Cell>> shape;
    bool reachLeft();
    bool reachRight();
    bool canRotate(std::string);
    std::vector<std::shared_ptr<Cell>> makeShape(int, int, int);
    
public:
    // four operations on blocks
    TShape(Grid *g, int x, int y);
    void print() override;
    void init() override;
    void down() override;
    void left() override;
    void right() override;
    void drop() override;
    void rotate(std::string) override;
    bool reachBot() override;
    void heavy() override;
    void nDown(int n) override;
    void nLeft(int n) override;
    void nRight(int n) override;
    void nRotate(int n, std::string s) override;
    Xwindow::c getcolour() override;
    
    // accessors & mutators
    std::vector<std::shared_ptr<Cell>> getShape() override;
    std::string getName() override;
};


#endif
