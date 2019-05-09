#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>
#include <memory>


class Grid;
class Block;

class Level {
    int lv;
    
protected:
    int seed = 0;
    bool seedgiven = false;
    
public:
    Level(int lv);
    std::shared_ptr<Block> ChartoBlock(Grid *g, std::string c);
    virtual std::shared_ptr<Block> generateBlocks(Grid *g) = 0;
    void setseed(int s);
    int getlv();
    virtual ~Level();
};

#endif

