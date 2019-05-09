#include "Block.h"

Block::Block(Grid *g, int x, int y): g{g}, lb_x{x}, lb_y{y} {} 

bool Block::get_heavy() {
    return is_heavy;
}

void Block::set_heavy() {
    is_heavy = true;
}
