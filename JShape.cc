#include "JShape.h"
using namespace std;


JShape::JShape(Grid *g, int x, int y): Block(g, x, y) {};


void JShape::init() {
    shared_ptr<Cell> c1 = g->get(lb_x, lb_y);
    shared_ptr<Cell> c2 = g->get(lb_x, lb_y + 1);
    shared_ptr<Cell> c3 = g->get(lb_x, lb_y + 2);
    shared_ptr<Cell> c4 = g->get(lb_x - 1, lb_y);
    shape.emplace_back(c1);
    shape.emplace_back(c2);
    shape.emplace_back(c3);
    shape.emplace_back(c4);
}


bool JShape::reachLeft() {
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


bool JShape::reachRight() {
    // already reach the last col
    if (state == 0 || state == 2) {
        if (lb_y >= 8) return true;
    } else if (state == 1 || state == 3) {
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


bool JShape::reachBot() {
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


bool JShape::canRotate(string s) {
    int tmp_state = state;
    
    if (tmp_state == 1 || tmp_state == 3) {
        if (lb_y >= 9) return false;
    }
    
    // try to rotate
    if (s == "cw") { // clockwise
        tmp_state = (tmp_state + 1) % 4;
    } else if (s == "ccw") { // counter-clockwise
        tmp_state = (tmp_state + 3) % 4;
    }
    
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x, lb_y, tmp_state);
    for (int i = 0; i < 4; ++i) {
        if (!v.at(i)->isEmpty()) return false;
    }
    
    state = tmp_state;
    return true;
}


vector<shared_ptr<Cell>> JShape::makeShape(int x, int y, int tmp_state) {
    vector<shared_ptr<Cell>> v;
    
    if (tmp_state == 0) {
        shared_ptr<Cell> c1 = g->get(x, y);
        shared_ptr<Cell> c2 = g->get(x, y + 1);
        shared_ptr<Cell> c3 = g->get(x, y + 2);
        shared_ptr<Cell> c4 = g->get(x - 1, y);
        v.emplace_back(c1);
        v.emplace_back(c2);
        v.emplace_back(c3);
        v.emplace_back(c4);
    } else if (tmp_state == 1) {
        shared_ptr<Cell> c1 = g->get(x, y);
        shared_ptr<Cell> c2 = g->get(x - 1, y);
        shared_ptr<Cell> c3 = g->get(x - 2, y);
        shared_ptr<Cell> c4 = g->get(x - 2, y + 1);
        v.emplace_back(c1);
        v.emplace_back(c2);
        v.emplace_back(c3);
        v.emplace_back(c4);
    } else if (tmp_state == 2) {
        shared_ptr<Cell> c1 = g->get(x, y + 2);
        shared_ptr<Cell> c2 = g->get(x - 1, y);
        shared_ptr<Cell> c3 = g->get(x - 1, y + 1);
        shared_ptr<Cell> c4 = g->get(x - 1, y + 2);
        v.emplace_back(c1);
        v.emplace_back(c2);
        v.emplace_back(c3);
        v.emplace_back(c4);
    } else if (tmp_state == 3) {
        shared_ptr<Cell> c1 = g->get(x, y);
        shared_ptr<Cell> c2 = g->get(x, y + 1);
        shared_ptr<Cell> c3 = g->get(x - 1, y + 1);
        shared_ptr<Cell> c4 = g->get(x - 2, y + 1);
        v.emplace_back(c1);
        v.emplace_back(c2);
        v.emplace_back(c3);
        v.emplace_back(c4);
    }
    
    return v;
}


void JShape::down() {
    if (!reachBot()) {
        ++lb_x;
        shape = makeShape(lb_x, lb_y, state);
    }
}


void JShape::left() {
    if (!reachLeft()) {
        --lb_y;
        shape = makeShape(lb_x, lb_y, state);
    }
    if (is_heavy){
        this->heavy();
    }
}


void JShape::right() {
    if (!reachRight()) {
        ++lb_y;
        shape = makeShape(lb_x, lb_y, state);
    }
    if (is_heavy){
        this->heavy();
    }
}


void JShape::drop() {
    while (!reachBot()) {
        down();
    }
}


void JShape::rotate(string s) {
    if (canRotate(s)) {
        shape = makeShape(lb_x, lb_y, state);
    }
}


vector<shared_ptr<Cell>> JShape::getShape() {
    return shape;
}


string JShape::getName() {
    return name;
}


void JShape::print() {
    cout << "J" << endl;
    cout << "JJJ" << endl;
    if (g->xp != nullptr) {
        g->xp->fillRectangle(10, 420, 20, 20, Xwindow::c::Red);
        g->xp->fillRectangle(10, 440, 60, 20, Xwindow::c::Red);
    }
}


void JShape::heavy() {
    int count = 2;
    while (count > 0) {
        this->down();
        --count;
    }
}


void JShape::nDown(int n) {
    while (n > 0) {
        down();
        --n;
    }
}


void JShape::nLeft(int n) {
    while (n > 0) {
        left();
        --n;
    }
}


void JShape::nRight(int n) {
    while (n > 0) {
        right();
        --n;
    }
}


void JShape::nRotate(int n, string s) {
    while (n > 0) {
        rotate(s);
        --n;
    }
}


Xwindow::c JShape::getcolour() {
    return Xwindow::c::Red;
}
