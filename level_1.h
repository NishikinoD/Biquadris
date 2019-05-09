#ifndef __LEVEL_1_H__
#define __LEVEL_1_H__
#include "level.h"


class Level_1: public Level {
public:
    Level_1(int lv);
    std::shared_ptr<Block> generateBlocks(Grid *g) override;
    // int get_level() override;
};

#endif

