#include "level.h"
#include "Block.h"
#include "Grid.h"
#include "IShape.h"
#include "JShape.h"
#include "TShape.h"
#include "SShape.h"
#include "OShape.h"
#include "ZShape.h"
#include "LShape.h"
#include "Single.h"

using namespace std;


Level::Level(int lv): lv{lv} {}


int Level::getlv() {
    return lv;
}


void Level::setseed(int s) {
    seed = s;
    seedgiven = true;
}


shared_ptr<Block> Level::ChartoBlock(Grid *g, string c) {
    if (c == "S") {
        auto s =  make_shared<SShape>(g, 3, 0);
        s->init();
        return  s;
    } else if (c == "I") {
        auto i  = make_shared<IShape>(g, 3, 0);
        i->init();
        return i;
    } else if (c == "J") {
        auto j =  make_shared<JShape>(g, 3, 0);
        j->init();
        return j;
    } else if (c == "L") {
        auto l =  make_shared<LShape>(g, 3, 0);
        l->init();
        return  l;
    } else if (c == "O") {
        auto o =  make_shared<OShape>(g, 3, 0);
        o->init();
        return  o;
    } else if (c == "Z") {
        auto z =  make_shared<ZShape>(g, 3, 0);
        z->init();
        return  z;
    } else if (c=="*") {
        auto sing =  make_shared<Single>(g, 0, 5);
        sing->init();
        return  sing;
    } else  {
        auto t = make_shared<TShape>(g, 3, 0);
        t->init();
        return t;
    }
}


Level::~Level() {}
