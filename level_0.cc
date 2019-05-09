#include "level_0.h"
#include "Block.h"
#include "Grid.h"
#include "IShape.h"
#include "JShape.h"
#include "TShape.h"
#include "SShape.h"
#include "OShape.h"
#include "ZShape.h"
#include "LShape.h"
using namespace std;


Level_0::Level_0(int lv, string file): Level(lv), file{file} {}


void Level_0::setfile(string s) {
    file = s;
}


void Level_0::setblock() {
    ifstream f{file};
    getline(f,blocks);
}


shared_ptr<Block> Level_0::generateBlocks(Grid *g) {
    stringstream ss(blocks);
    char c1;
    if (!(ss >> c1)) {
        setblock();
        ss.str("");
        ss.clear();
        ss << blocks;
        ss >> c1;
    }
    size_t pos = blocks.find(c1);
    blocks = blocks.substr(pos+1); // move through the blocks
    string name;
    name.push_back(c1);
    return ChartoBlock(g, name);
} // delete currblock in recalculate


// int Level_0::get_level() {return 0;}

