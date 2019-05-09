#ifndef _CELL_H_
#define _CELL_H_
#include <iostream>
#include <string>
#include <memory>
#include "window.h"


class Cell {
    int x;
    int y;
    int width;
    int height;
    std::string s = " ";
    bool is_empty = true;
    Xwindow::c colour = Xwindow::c::White;
    
public:
    std::shared_ptr<Xwindow> w = nullptr;
    void setCoords(int x, int y, int width, int height);
    void draw();
    void undraw();
    bool isEmpty();
    void setAlive();
    void setString(std::string, Xwindow::c);
    ~Cell();
    std::string prettyprint();
};


#endif
