#ifndef __LEVEL_4_H__
#define __LEVEL_4_H__
#include "level.h"

class Level_4: public Level {
public:
    Level_4(int lv);
    std::shared_ptr<Block> generateBlocks(Grid *g) override;
    //  int get_level() override;
};

#endif

