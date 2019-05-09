#include "Grid.h"
#include "Block.h"
#include "IShape.h"
#include "JShape.h"
#include "TShape.h"
#include "SShape.h"
#include "OShape.h"
#include "ZShape.h"
#include "LShape.h"
using namespace std;


void Grid::init() {
    for (int i = 0 ; i < 18; ++i) {
        vector<shared_ptr<Cell>> row_cell;
        for (int j = 0; j < 11; ++j) {
            auto c = make_shared<Cell>();
            c->w = xp;
            c->setCoords(j*220/col, 40+i*360/row ,220/col,360/row);
            // graph set coords
            row_cell.emplace_back(c);
        }
        theGrid.emplace_back(row_cell);
    }
}


void Grid::recalculate() {
    if (is_blind) is_blind = false;
    
    // put the block into the grid
    vector<shared_ptr<Cell>> shape = curblock->getShape();
    for (auto &c: shape) {
        c->setAlive();
        c->setString(curblock->getName(),curblock->getcolour());
    }
    
    // clear rows if filled
    int pos = 0;
    this->clearedrows = 0;
    for (auto &vc: theGrid) { // erase all rows that are filled
        bool filled = true;
        for (auto &c: vc) {
            if (c->isEmpty()) {
                filled = false;
                break;
            }
        }
        if (filled == true) {
            for (int i = 0; i <11 ; i++) {
                vc[i]->undraw();
            }
            theGrid.erase(theGrid.begin() + pos);
            last_cleared = 0;
            ++clearedrows; 
            // add a new row to the front
            vector<shared_ptr<Cell>> newRow;
            for (int i = 0; i < 11; ++i) {
                shared_ptr<Cell> c = make_shared<Cell>();
                c->setCoords(i*220/col, 40,220/col,360/row);
                newRow.emplace_back(c);
                
            }
            theGrid.emplace(theGrid.begin(), newRow);
             for (int i = 0 ; i < 18; ++i) {
                 for (int j = 0; j < 11; ++j) {
                   theGrid[i][j]->setCoords(j*220/col,40+i*360/row , 220/col, 360/row);
               }
             } 
        } else {
            ++last_cleared;
        }
        ++pos;
    }
    if (clearedrows != 0) {
        int increment = (level->getlv() + clearedrows) * (level->getlv() + clearedrows);
        this->set_score(this->get_score() + increment);
    }
}


bool Grid::gameOver() {
    // if any cell of the block is in the first three hidden rows
    for (int i = 0; i < 3; ++i) { // first 3 rows
        for (auto &c: theGrid.at(i)) { // columns
            if (!c->isEmpty()) return true;
        }
    }
    
    vector<shared_ptr<Cell>> nextshape = nextblock->getShape();
    for (auto &c: nextshape) {
        if (!c->isEmpty()) return true;
    }
    
    return false;
}


shared_ptr<Cell> Grid::get(int x, int y) {
    return theGrid.at(x).at(y);
}


void Grid::prettyprint() {
    if (xp != nullptr) {
        xp->fillRectangle(0, 420, 220, 60, Xwindow::c::White);
        xp->fillRectangle(0, 0, 220, 40, Xwindow::c::White);
    }
    cout << "Level:" << "   " << level->getlv() << endl;
    cout << "Score:" << "   " << this->get_score() << endl;
    string s = "Level:   ";
    string lev = to_string(level->getlv());
    s += lev;
    if (xp != nullptr) {
        xp->drawString(10, 10, s);
    } // graph print
    s = "Score:   ";
    string sco = to_string(this->get_score());
    s+= sco;
    if (xp != nullptr) {
        xp->drawString(10, 20, s); // graph print
    }
    if (curblock != nullptr) {
        vector<shared_ptr<Cell>> v = curblock->getShape();
        for (int i = 0; i<18; ++i) {
            string s1 = "";
            for (int j=0; j<11; ++j) {
                bool exist = false;
                auto c = theGrid.at(i).at(j);
                int len = v.size();
                for (int k=0; k <len; ++k) {
                    if (c == v.at(k)) {
                        exist =true;
                        if (xp != nullptr) {
                            xp->fillRectangle(j*220/col, 40+i*360/row, 220/col, 360/row, curblock->getcolour());
                        }
                    }
                }
                if (is_blind && (j >= 3) && (j <= 9) && (i>= 3) && (i <= 9)) {
                    if (xp != nullptr) {
                        xp->fillRectangle(j*220/col, 40+i*360/row ,220/col,360/row, Xwindow::c::Black);
                    }
                    s1 += "?";
                } else if (exist == true) {
                    s1 += curblock->getName();
                    
                } else {
                    s1 += c->prettyprint();
                    c->draw();
                }
            }
            cout << s1 << endl;
        }
        // is_blind = false;
    } else {
        for (int i = 0; i < 18; ++i) {
            string s1 = "";
            for (int j=0; j < 11; ++j) {
                auto c = theGrid.at(i).at(j);
                s1 += c->prettyprint();
                c->draw();
            }
            cout << s1 << endl;
        }
    }
    cout << "-----------" << endl;
    if (xp != nullptr) {
        xp->fillRectangle(0, 400, 220, 3, Xwindow::c::Black);
    }
    cout << "Next:" << endl;
    if (xp != nullptr) {
        xp->drawString(10, 410, "Next:");
    }
    nextblock->print();
    cout<< "_______________" << endl;
    
}


void Grid::clearGrid() {
    vector<vector<shared_ptr<Cell>>> newGrid;
    theGrid = newGrid;
    this->init();
    countStep = 0;
    score = 0;
    clearedrows = 0;
    is_blind = false;
    level = nullptr;
}


void Grid::set_score(int n) {
    score = score + n;
    if (score >= hi) hi = score;
}


int Grid::get_score() {
    return score;
}


int Grid::get_hi() {
    return hi;
}


void Grid::set_blind() {
    is_blind = true;
}


void Grid::force(string s) {
    if (s == "Z") {
        nextblock = make_shared<ZShape>(this, 3, 0);
        nextblock->init();
    } else if (s == "S") {
        nextblock = make_shared<SShape>(this, 3, 0);
        nextblock->init();
    } else if (s == "T") {
        nextblock = make_shared<TShape>(this, 3, 0);
        nextblock->init();
    } else if (s == "L") {
        nextblock = make_shared<LShape>(this, 3, 0);
        nextblock->init();
    } else if (s == "I") {
        nextblock = make_shared<IShape>(this, 3, 0);
        nextblock->init();
    } else if (s == "J") {
        nextblock = make_shared<JShape>(this, 3, 0);
        nextblock->init();
    } else if (s == "O") {
        nextblock = make_shared<OShape>(this, 3, 0);
        nextblock->init();
    }
}


shared_ptr<Block> Grid::get_cur() {
    return curblock;
}


shared_ptr<Block> Grid::get_next() {
    return nextblock;
}


void Grid::set_cur(shared_ptr<Block> p) {
    curblock = p;
}


void Grid::set_next(shared_ptr<Block> p) {
    nextblock = p;
}


int Grid::getclearedrow() {
    return clearedrows;
}


int Grid::get_last_cleared() {
    return last_cleared;
}


std::shared_ptr<Level> Grid::get_level() {
    return level;
}


void Grid::set_level(std::shared_ptr<Level> l) {
    level = l;
}
