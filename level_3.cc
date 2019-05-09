#include "level_3.h"
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


Level_3::Level_3(int lv): Level(lv) {}


shared_ptr<Block> Level_3::generateBlocks(Grid *g) {
    if (seedgiven == false) {
        srand (time(NULL));
    } else {
        srand (seed);
    }
    
    int x = rand() % 9;
    if (x < 2) {
        return ChartoBlock(g, "S");
    } else if (x < 4 ) {
        return ChartoBlock(g, "Z");
    } else if (x == 4) {
        return ChartoBlock(g, "L");
    } else if (x == 5) {
        return ChartoBlock(g, "O");
    } else if (x == 6) {
        return ChartoBlock(g, "T");
    } else if (x == 7) {
        return ChartoBlock(g, "I");
    } else  {
        return ChartoBlock(g, "J");
    }
}

//int get_level(){return 3;}
