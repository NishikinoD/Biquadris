#include "SShape.h"
using namespace std;


SShape::SShape(Grid *g, int x, int y): Block(g, x, y) {};


void SShape::init() {
    shared_ptr<Cell> c1 = g->get(lb_x, lb_y);
    shared_ptr<Cell> c2 = g->get(lb_x, lb_y + 1);
    shared_ptr<Cell> c3 = g->get(lb_x - 1, lb_y + 1);
    shared_ptr<Cell> c4 = g->get(lb_x - 1, lb_y + 2);
    shape.emplace_back(c1);
    shape.emplace_back(c2);
    shape.emplace_back(c3);
    shape.emplace_back(c4);
}


bool SShape::reachLeft() {
    // already reach the first col
    if (lb_y == 0) return true;
    
    // try to move left
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x, lb_y - 1, state);
    for (int i = 0; i < 4; ++i) {
        if (!v.at(i)->isEmpty()) return true;
    }
    
    return false;
}


bool SShape::reachRight() {
    // already reach the last col
    if (state == 0) {
        if (lb_y >= 8) return true;
    } else if (state == 1) {
        if (lb_y >= 9) return true;
    }
    
    // try to move right
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x, lb_y + 1, state);
    for (int i = 0; i < 4; ++i) {
        if (!v.at(i)->isEmpty()) return true;
    }
    
    return false;
}


bool SShape::reachBot() {
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


bool SShape::canRotate(string s) {
    int tmp_state = state;
    
    if (state == 1 && lb_y >= 9) return false;
    
    // try to rotate
    tmp_state = (tmp_state + 1) % 2;
    
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x, lb_y, tmp_state);
    for (int i = 0; i < 4; ++i) {
        if (!v.at(i)->isEmpty()) return false;
    }
    
    state = tmp_state;
    return true;
}


vector<shared_ptr<Cell>> SShape::makeShape(int x, int y, int tmp_state) {
    vector<shared_ptr<Cell>> v;
    
    if (tmp_state == 0) {
            shared_ptr<Cell> c1 = g->get(x, y);
            shared_ptr<Cell> c2 = g->get(x, y + 1);
            shared_ptr<Cell> c3 = g->get(x - 1, y + 1);
            shared_ptr<Cell> c4 = g->get(x - 1, y + 2);
            v.emplace_back(c1);
            v.emplace_back(c2);
            v.emplace_back(c3);
            v.emplace_back(c4);
    } else if (tmp_state == 1) {
        shared_ptr<Cell> c1 = g->get(x, y + 1);
        shared_ptr<Cell> c2 = g->get(x - 1, y);
        shared_ptr<Cell> c3 = g->get(x - 1, y + 1);
        shared_ptr<Cell> c4 = g->get(x - 2, y);
        v.emplace_back(c1);
        v.emplace_back(c2);
        v.emplace_back(c3);
        v.emplace_back(c4);
    }
    
    return v;
}


void SShape::down() {
    if (!reachBot()) {
        ++lb_x;
        shape = makeShape(lb_x, lb_y, state);
    }
}


void SShape::left() {
    if (!reachLeft()) {
        --lb_y;
        shape = makeShape(lb_x, lb_y, state);
    }
    if (is_heavy){
        this->heavy();
    }
}


void SShape::right() {
    if (!reachRight()) {
        ++lb_y;
        shape = makeShape(lb_x, lb_y, state);
    }
    if (is_heavy){
        this->heavy();
    }
}


void SShape::drop() {
    while (!reachBot()) {
        down();
    }
}


void SShape::rotate(string s) {
    if (canRotate(s)) {
        shape = makeShape(lb_x, lb_y, state);
    }
}


vector<shared_ptr<Cell>> SShape::getShape() {
    return shape;
}


string SShape::getName() {
    return name;
}


void SShape::print() {
    cout << " SS" << endl;
    cout << "SS" << endl;
    if (g->xp != nullptr) {
        g->xp->fillRectangle(30, 420, 40, 20, Xwindow::c::Purple);
        g->xp->fillRectangle(10, 440, 40, 20, Xwindow::c::Purple);
    }
}


void SShape::heavy() {
    int count = 2;
    while (count > 0) {
        this->down();
        --count;
    }
}


void SShape::nDown(int n) {
    while (n > 0) {
        down();
        --n;
    }
}


void SShape::nLeft(int n) {
    while (n > 0) {
        left();
        --n;
    }
}


void SShape::nRight(int n) {
    while (n > 0) {
        right();
        --n;
    }
}


void SShape::nRotate(int n, string s) {
    while (n > 0) {
        rotate(s);
        --n;
    }
}


Xwindow::c SShape::getcolour() {
    return Xwindow::c::Purple;
}
