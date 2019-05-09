#include "OShape.h"
using namespace std;


OShape::OShape(Grid *g, int x, int y): Block(g, x, y) {};


void OShape::init() {
    shared_ptr<Cell> c1 = g->get(lb_x, lb_y);
    shared_ptr<Cell> c2 = g->get(lb_x, lb_y + 1);
    shared_ptr<Cell> c3 = g->get(lb_x - 1, lb_y);
    shared_ptr<Cell> c4 = g->get(lb_x - 1, lb_y + 1);
    shape.emplace_back(c1);
    shape.emplace_back(c2);
    shape.emplace_back(c3);
    shape.emplace_back(c4);
}


bool OShape::reachLeft() {
    // already reach the first col
    if (lb_y == 0) return true;
    
    // try to move left
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x, lb_y - 1, state);
    for (int i = 0; i < 4; ++i){
        if (!v.at(i)->isEmpty()) return true;
    }
    
    return false;
}


bool OShape::reachRight() {
    // already reach the last col
    if (lb_y >= 9) return true;
    
    // try to move right
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x, lb_y + 1, state);
    for (int i = 0; i < 4; ++i) {
        if (!v.at(i)->isEmpty()) return true;
    }
    
    return false;
}


bool OShape::reachBot() {
    // already reach bot
    if (lb_x >= 17) return true;
    
    // try to move down
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x + 1, lb_y, state);
    for (int i = 0; i < 4 ; ++i) {
        if (!v.at(i)->isEmpty()) return true;
    }
    
    return false;
}


bool OShape::canRotate(string s) {
    return true;
}


vector<shared_ptr<Cell>> OShape::makeShape(int x, int y, int tmp_state) {
    vector<shared_ptr<Cell>> v;
    
    shared_ptr<Cell> c1 = g->get(x, y);
    shared_ptr<Cell> c2 = g->get(x, y + 1);
    shared_ptr<Cell> c3 = g->get(x - 1, y);
    shared_ptr<Cell> c4 = g->get(x - 1, y + 1);
    v.emplace_back(c1);
    v.emplace_back(c2);
    v.emplace_back(c3);
    v.emplace_back(c4);

    return v;
}


void OShape::down() {
    if (!reachBot()) {
        ++lb_x;
        shape = makeShape(lb_x, lb_y, state);
    }
}


void OShape::left() {
    if (!reachLeft()) {
        --lb_y;
        shape = makeShape(lb_x, lb_y, state);
    }
    if (is_heavy){
        this->heavy();
    }
}


void OShape::right() {
    if (!reachRight()) {
        ++lb_y;
        shape = makeShape(lb_x, lb_y, state);
    }
    if (is_heavy){
        this->heavy();
    }
}


void OShape::drop() {
    while (!reachBot()) {
        down();
    }
}


void OShape::rotate(string s) {
    if (canRotate(s)) {
        shape = makeShape(lb_x, lb_y, state);
    }
}


vector<shared_ptr<Cell>> OShape::getShape() {
    return shape;
}


string OShape::getName() {
    return name;
}


void OShape::print() {
    cout << "OO" << endl;
    cout << "OO" << endl;
    if (g->xp != nullptr) {
        g->xp->fillRectangle(10, 420, 40, 20, Xwindow::c::Green);
        g->xp->fillRectangle(10, 440, 40, 20, Xwindow::c::Green);
    }
}


void OShape::heavy() {
    int count = 2;
    while (count > 0) {
        this->down();
        --count;
    }
}


void OShape::nDown(int n) {
    while (n > 0) {
        down();
        --n;
    }
}


void OShape::nLeft(int n) {
    while (n > 0) {
        left();
        --n;
    }
}


void OShape::nRight(int n) {
    while (n > 0) {
        right();
        --n;
    }
}


void OShape::nRotate(int n, string s) {
    while (n > 0) {
        rotate(s);
        --n;
    }
}


Xwindow::c OShape::getcolour() {
    return Xwindow::c::Green;
}
