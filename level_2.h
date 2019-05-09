#ifndef __LEVEL_2_H__
#define __LEVEL_2_H__
#include "level.h"

class Level_2: public Level {
public:
    Level_2(int lv);
    std::shared_ptr<Block> generateBlocks(Grid *g) override;
    //int get_level() override;
};

#endif

