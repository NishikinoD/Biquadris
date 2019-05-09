#include "level_2.h"
#include "Block.h"
#include "Grid.h"
#include "IShape.h"
#include "JShape.h"
#include "TShape.h"
#include "SShape.h"
#include "OShape.h"
#include "ZShape.h"
#include "LShape.h"
#include <stdlib.h>
#include <time.h>

using namespace std;


Level_2::Level_2(int lv): Level(lv) {}


shared_ptr<Block> Level_2::generateBlocks(Grid *g) {
    if (seedgiven == false) {
        srand (time(NULL));
    } else {
        srand (seed);
    }
    
    int x = rand() % 7;
    if (x == 0) {
        return ChartoBlock(g, "I");
    } else if (x == 1 ) {
        return ChartoBlock(g, "J");
    } else if (x == 2) {
        return ChartoBlock(g, "L");
    } else if (x == 3) {
        return ChartoBlock(g, "O");
    } else if (x == 4) {
        return ChartoBlock(g, "T");
    } else if (x == 5) {
        return ChartoBlock(g, "S");
    } else { // x == 6
        return ChartoBlock(g, "Z");
    }
}

// int get_level() {return 2;}
