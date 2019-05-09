#include "Cell.h"
#include "window.h"
#include <memory>
#include <string>
using namespace std;


Cell::~Cell() {}


void Cell::setCoords(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Cell::draw() {
    if ( w != nullptr) {
        w->fillRectangle(x, y, width, height,colour);
    }
}

void Cell::undraw() {
    if (w != nullptr) {
        w->fillRectangle(x, y, width, height,Xwindow::c::White);
    }
}


void Cell::setAlive() {
    is_empty = false;
    draw();
}


void Cell::setString(string str, Xwindow::c col) {
    s = str;
    colour = col;
}


bool Cell::isEmpty() {
    return is_empty;
}


string Cell::prettyprint() {
    if (is_empty) return " ";
    return s;
}
