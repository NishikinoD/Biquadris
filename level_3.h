#ifndef __LEVEL_3_H__
#define __LEVEL_3_H__
#include "level.h"

class Level_3: public Level {
public:
    Level_3(int lv);
    std::shared_ptr<Block> generateBlocks(Grid *g) override;
    //int get_level() override;
};


#endif

