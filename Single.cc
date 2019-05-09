#include "Single.h"
using namespace std;


Single::Single(Grid *g, int x, int y): Block(g, x, y) {};


void Single::init() {
    shared_ptr<Cell> c = g->get(lb_x,lb_y);
    shape.emplace_back(c);
}


vector<shared_ptr<Cell>> Single::makeShape(int x, int y, int tmp_state) {
    vector <shared_ptr<Cell>> v;
    shared_ptr<Cell> c = g->get(x, y);
    v.emplace_back(c);
    return v;
}


void Single::down() {
    if (!reachBot()) {
        ++lb_x;
        shape = makeShape(lb_x, lb_y, state);
    }
}


void Single::left() {}


bool Single::reachBot() {
    if (lb_x >= 17) return true;
    vector<shared_ptr<Cell>> v;
    v = makeShape(lb_x + 1, lb_y, state);
     if (!v.at(0)->isEmpty()) return true;
     else  return false;
}


void Single::right() {}


void Single::drop() {
    while(!reachBot()) {
        down();
    }
}


void Single::rotate(string s) {}


vector<shared_ptr<Cell>> Single::getShape() {
    return shape;
}


string Single::getName() {
    return name;
}


void Single::print() {
    cout << "*" <<endl;
}


void Single::heavy(){}


void Single::nDown(int n) {
    while (n > 0) {
        down();
        --n;
    }
}


void Single::nLeft(int n) {}


void Single::nRight(int n) {}


void Single::nRotate(int n, string s) {}


Xwindow::c Single::getcolour() {
    return Xwindow::c::Brown;
}

