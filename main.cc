#include "Block.h"
#include "Cell.h"
#include "Grid.h"
#include "IShape.h"
#include "JShape.h"
#include "TShape.h"
#include "SShape.h"
#include "OShape.h"
#include "ZShape.h"
#include "LShape.h"
#include "Single.h"
#include "level.h"
#include "level_0.h"
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include "level_4.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;


std::shared_ptr<Level> lvchange(int lv, string file);
void game(Grid *player, Grid *op, shared_ptr<Block> b, int step, int flag, int *turn);


int main(int argc, char *argv[]){
    Grid g1;
    Grid g2;
    int p = argc;
    for (int i = 0; i < p; ++i) {
        string argum = argv[i];
        if (argum == "-text") {
            g1.xp = nullptr;
            g2.xp = nullptr;
            p = -1;
            break;
        }
    }
    
    if (p > -1) {
        g1.xp = make_shared<Xwindow>();
        g2.xp = make_shared<Xwindow>();
    }
    
    g1.init();
    g2.init();
    auto lvplayer1 = make_shared<Level_0>(0, "sequence1.txt");
    auto lvplayer2 = make_shared<Level_0>(0, "sequence2.txt");
    g1.set_level(lvplayer1);
    g2.set_level(lvplayer2);
    
    // initialize level 0, with command files s1,s2
    int numarg = argc;
    for (int i = 0; i < numarg; ++i) {
        string argum = argv[i];
        if (argum == "-scriptfile1") {
            lvplayer1->setfile(argv[i + 1]); //change file for lv0
        } else if (argum  == "-scriptfile2") {
            lvplayer2->setfile(argv[i + 1]); //change file for lv0
        } else if (argum =="-startlevel") {
            int n = stoi(argv[i + 1]);
            g1.set_level(lvchange(n, "sequence1.txt"));
            g2.set_level(lvchange(n, "sequence2.txt"));
        } else if (argum == "-seed") {
            int n = stoi(argv[i + 1]);
            g1.get_level()->setseed(n);
            g2.get_level()->setseed(n);
        }
    }
    
    g1.set_cur(nullptr);
    g1.set_next(g1.get_level()->generateBlocks(&g1));
    g2.set_cur(nullptr);
    g2.set_next(g2.get_level()->generateBlocks(&g2));
    g1.set_cur(g1.get_next());
    g1.set_next(g1.get_level()->generateBlocks(&g1));
    g1.prettyprint();
    g2.prettyprint();
    
    // initialize blocks
    int turn = 1;
    int step = 1; // number of steps each round
    while (true) {
        if (turn % 2 == 1) { // player 1 takes action
            try {
                game(&g1, &g2, g1.get_cur(), step, 1, &turn);
            } catch (bool) {
                cout << "Player 1 loses" << endl;
                break;
            }
            
            turn++;
        } else { // player 2 takes action
            try {
                game(&g2, &g1, g2.get_cur(), step, 2, &turn);
            } catch (bool) {
                cout << "Player 2 loses" << endl;
                break;
            }
            
            turn++;
        }
    }
}


std::shared_ptr<Level> lvchange(int lv, string file) {
    if (lv <= 0) {
        auto newlv0 = make_shared<Level_0>(0,file);
        return newlv0;
    } else if (lv == 1) {
        auto newlv1 = make_shared<Level_1>(1);
        return newlv1;
    } else if (lv == 2) {
        auto newlv2 = make_shared<Level_2>(2);
        return newlv2;
    } else if (lv == 3) {
        auto newlv3 = make_shared<Level_3>(3);
        return newlv3;
    } else { // lv == 4
        auto newlv4 = make_shared<Level_4>(4);
        return newlv4;
    }
}


void game(Grid *player, Grid *op,  shared_ptr<Block> b, int step, int flag, int *turn) {
    if (step <= 0) return;
    if (player->gameOver()) throw true;
    
    string s;
    istream *in;
    in = &cin;
    while (*in >> s) {
        if (strncmp(s.c_str(), "restart", 2) == 0) {
            player->clearGrid();
            op->clearGrid();
            flag = 1;
            auto lvplayer1 = make_shared<Level_0>(0, "sequence1.txt");
            auto lvplayer2 = make_shared<Level_0>(0, "sequence2.txt");
            player->set_level(lvplayer1);
            op->set_level(lvplayer2);
            player->set_next(player->get_level()->generateBlocks(player));
            op->set_next(op->get_level()->generateBlocks(op));
            player->set_cur(player->get_next());
            player->set_next(player->get_level()->generateBlocks(player));
            player->prettyprint();
            op->prettyprint();
            --(*turn);
            break;
        } else if (strncmp(s.c_str(), "sequence", 1) == 0) {
            *in >> s;
            ifstream f{s};
            in = &f;
            continue; // read command from file
        } else if (s.length() == 1) {
            shared_ptr<Block> temp = player->get_level()->ChartoBlock(player, s);
            player->set_cur(temp);
            b = temp;
        } else if (strncmp(s.c_str(), "norandom", 1) == 0) {
            if ((player->get_level()->getlv() == 3) || (player->get_level()->getlv() == 4)) {
                cin >> s;
                player->set_level(lvchange(0, s));
                continue;
            }
        }
        
        // multiplier prefix
        else if ((s[0] >= '0') && (s[0] <= '9')) {
            int multiplier;
            string sub;
            if ((s[1] >= '0') && (s[1] <= '9')) {
                multiplier = stoi(s.substr(0, 2));
                sub = s.substr(2);
            } else {
                multiplier = stoi(s.substr(0, 1));
                sub = s.substr(1);
            }
            if (strncmp(sub.c_str(), "levelup", 6) == 0) {
                player->set_level(lvchange(min(player->get_level()->getlv() + multiplier, 4), ""));
            } else if (strncmp(sub.c_str(), "leveldown", 6) == 0) {
                player->set_level(lvchange(max(player->get_level()->getlv() - multiplier, 0), "sequence1.txt"));
            } else if (strncmp(sub.c_str(), "left", 3) == 0) {
                b->nLeft(multiplier);
            } else if (strncmp(sub.c_str(), "right", 2) == 0) {
                b->nRight(multiplier);
            } else if (strncmp(sub.c_str(), "down", 2) == 0) {
                b->nDown(multiplier);
            } else if (strncmp(sub.c_str(), "clockwise", 2) == 0) {
                b->nRotate(multiplier, "cw");
            } else if (strncmp(sub.c_str(), "counterclockwise", 2) == 0) {
                b->nRotate(multiplier, "ccw");
            }
        }
        
        else if (strncmp(s.c_str(), "levelup", 6) == 0)  {
            player->set_level(lvchange(player->get_level()->getlv() + 1, ""));
        } else if (strncmp(s.c_str(), "leveldown", 6) == 0) {
            player->set_level(lvchange(player->get_level()->getlv() - 1, "sequence1.txt"));
        } else if (strncmp(s.c_str(), "left", 3) == 0) {
            b->left();
        } else if (strncmp(s.c_str(), "right", 2) == 0) {
            b->right();
        } else if (strncmp(s.c_str(), "down", 2) == 0) {
            b->down();
        } else if (strncmp(s.c_str(), "clockwise", 2) == 0) {
            b->rotate("cw");
        } else if (strncmp(s.c_str(), "counterclockwise", 2) == 0) {
            b->rotate("ccw");
        }
        
        // level 3/4 heavy
        if ((player->get_level()->getlv() == 3)||(player->get_level()->getlv() == 4)) {
            b->down();
        }
        
        if (strncmp(s.c_str(), "drop", 2) == 0) {
            b->drop();
            player->recalculate();
            if (player->getclearedrow() >= 2){
                string effect_command;
                cin >> effect_command;
                if (effect_command == "blind"){
                    op->set_blind();
                } else if (effect_command == "heavy"){
                    op->get_next()->set_heavy();
                } else if (effect_command == "force"){
                    string type;
                    cin >> type;
                    op->force(type);
                }
            }
            
            // level 4 drop "*"
            if ((player->get_level()->getlv() == 4) && (player->get_last_cleared() % 5 == 0) && (player->get_last_cleared() != 0)) {
                auto temp = player->get_level()->ChartoBlock(player, "*");
                player->set_cur(temp);
                b = temp;
                b->drop();
                player->recalculate();
            }
            
            if (step == 1) {
                op->set_cur(op->get_next());
                op->set_next(op->get_level()->generateBlocks(op));
            } else {
                player->set_cur(player->get_next());
                player->set_next(player->get_level()->generateBlocks(player));
            }
            
            // print
            if (flag == 1) {
                // op->set_cur(op->get_next());
                // op->set_next (op->get_level()->generateBlocks(op));
                player->prettyprint();
                op->prettyprint();
            } else {
                // op->set_cur(op->get_next());
                // op->set_next(op->get_level()->generateBlocks(op));
                op->prettyprint();
                player->prettyprint();
            }
            break;
            // switch to the oponent's turn
        }
        
        if (flag == 1) {
            player->prettyprint();
            op->prettyprint();
        } else {
            op->prettyprint();
            player->prettyprint();
        }
    }
    
    game(player, op, player->get_cur(), step - 1, flag, turn);
}

