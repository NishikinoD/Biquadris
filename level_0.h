#ifndef __LEVEL_0_H__
#define __LEVEL_0_H__
#include <fstream>
#include <string>
#include <sstream>
#include "level.h"
#include <string>


class Level_0: public Level {
    std::string blocks = "";
    std::string file;
    
public:
    Level_0(int lv, std::string file);
    void setfile(std::string s);
    void setblock();
    std::shared_ptr<Block> generateBlocks(Grid *g) override;
    // int get_level() override;
};

#endif
