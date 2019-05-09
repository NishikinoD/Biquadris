#include "TShape.h"
using namespace std;


TShape::TShape(Grid *g, int x, int y): Block :: Block(g, x, y) {}


void TShape::init() {
    shared_ptr<Cell> c1 = g->get(lb_x, lb_y + 1);
    shared_ptr<Cell> c2 = g->get(lb_x - 1, lb_y);
    shared_ptr<Cell> c3 = g->get(lb_x - 1, lb_y + 1);
    shared_ptr<Cell> c4 = g->get(lb_x - 1, lb_y + 2);
    shape.emplace_back(c1);
    shape.emplace_back(c2);
    shape.emplace_back(c3);
    shape.emplace_back(c4);
}


vector<shared_ptr<Cell>> TShape::makeShape(int x, int y, int tmp_state) {
    vector<shared_ptr<Cell>> v;
    
    if (tmp_state == 0) {
        shared_ptr<Cell> c1 = g->get(x, y + 1);
        shared_ptr<Cell> c2 = g->get(x - 1, y);
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
        shared_ptr<Cell> c4 = g->get(x - 2, y + 1);
        v.emplace_back(c1);
        v.emplace_back(c2);
        v.emplace_back(c3);
        v.emplace_back(c4);
    } else if (tmp_state == 2) {
        shared_ptr<Cell> c1 = g->get(x, y);
        shared_ptr<Cell> c2 = g->get(x, y + 1);
        shared_ptr<Cell> c3 = g->get(x, y + 2);
        shared_ptr<Cell> c4 = g->get(x - 1, y + 1);
        v.emplace_back(c1);
        v.emplace_back(c2);
        v.emplace_back(c3);
        v.emplace_back(c4);
    } else if (tmp_state == 3) {
        shared_ptr<Cell> c1 = g->get(x, y);
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


bool TShape::reachBot() {
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


void TShape::down() {
    if (!this->reachBot()) {
        ++lb_x;
        shape = this->makeShape(lb_x, lb_y, state);
    }
}


bool TShape::reachLeft() {
    // already reach left
    if (lb_y == 0) return true;
    
    // try to move left
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x, lb_y - 1, state);
    for (int i = 0; i < 4; ++i) {
        if (!v.at(i)->isEmpty()) return true;
     }

    return false;
}


void TShape::left() {
    if (!this->reachLeft()) {
        --lb_y;
        shape = this->makeShape(lb_x, lb_y, state);
    }
    if (is_heavy){
        this->heavy();
    }
}


bool TShape::reachRight() {
    // already reach right
    if (state == 0 || state == 2) {
        if (lb_y >= 8) return true;
    } else if (state == 1 || state == 3) {
        if (lb_y >= 9) return true;
    }
    
    // try to move right
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x, lb_y + 1,state);
    for (int i = 0; i < 4; ++i) {
        if (!v.at(i)->isEmpty()) return true;
    }
    
    return false;
}


void TShape::right() {
    if (!this->reachRight()) {
        ++lb_y;
        shape = makeShape(lb_x, lb_y, state);
    }
    if (is_heavy){
        this->heavy();
    }
}


bool TShape::canRotate(string s) {
    int tmp_state = state;
    
    if (state == 1 || state == 3) {
        if (lb_y >= 9)  return false;
    }
    
    // try to rotate
    if (s == "cw") {
        tmp_state = (tmp_state + 1 ) % 4;
    }
    if (s == "ccw") {
        tmp_state = (tmp_state + 3) % 4;
    }
    vector<shared_ptr<Cell>> v;
    v = this->makeShape(lb_x, lb_y, tmp_state);
    for (int i = 0; i < 4; ++i) {
        if (!v.at(i)->isEmpty()) return false;
    }
    
    state = tmp_state;
    return true;
}


void TShape::rotate(string s) {
    if (!canRotate(s)) return;
    shape = makeShape(lb_x, lb_y, state);
}


void TShape::drop() {
    while (!reachBot()) {
        down();
    }
}


vector<shared_ptr<Cell>> TShape::getShape() {
    return shape;
}


string TShape::getName() {
    return name;
}


void TShape::print() {
    cout << "TTT" << endl;
    cout <<" T " << endl;
    if (g->xp != nullptr) {
        g->xp->fillRectangle(10, 420, 60, 20, Xwindow::c::Blue);
        g->xp->fillRectangle(10, 440, 20, 20, Xwindow::c::Blue);
    }
}


void TShape::heavy() {
    int count = 2;
    while (count > 0) {
        this->down();
        --count;
    }
}


void TShape::nDown(int n) {
    while (n > 0) {
        down();
        --n;
    }
}


void TShape::nLeft(int n) {
    while (n > 0) {
        left();
        --n;
    }
}


void TShape::nRight(int n) {
    while (n > 0) {
        right();
        --n;
    }
}


void TShape::nRotate(int n, string s) {
    while (n > 0) {
        rotate(s);
        --n;
    }
}


Xwindow::c TShape::getcolour() {
    return Xwindow::c::Blue;
}
