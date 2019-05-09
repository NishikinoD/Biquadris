# Biquadris
University of Waterloo CS 246 F18 Final Project

## Intro
A Latinization of the game Tetris, expanded for two player competition.
Biquadris differs from Tetris in one significant way: **_it is not real-time_**. You have as much time
as you want to decide where to place a block. Players will take turns dropping blocks, one at a
time. A player's turn ends when he/she has dropped a block onto the board (unless this triggers
a special action; see below).

## How to play 
acceptalbe commands:  
- **left**: move the current block one unit left
- **right**: move the current block one unit right 
- **down**: move the current block one unit downward
- **drop**: drop the current block
- **clockwise**: rotate the current block 90 degrees clockwise
- **counterclockwise**: rotate the current block 90 degrees counterclockwise
- **levelup**: increase difficulty
- **leveldown**: decrease difficulty
- **restart**: clear the board and restart the game

## Special Actions
If a player, upon dropping a block, clears two or more rows simultaneously, a special action is
triggered.  
- **blind**: The player's board, from columns 3-9, and from rows 3-12, is covered with question marks (?), until the player drops a block; then the display reverts to normal.
- **heavy**: movements of the blocks apply twice for every single command
- **force X**: change your opponent's current block to the one you choose
    (values for X: L, J, S, Z, I, O, T)
    
## Other Features
  Only as much of a command as is necessary to distinguish it from other commands needs to be
entered. For example, **lef** is enough to distinguish the **left** command from the **levelup** command.

## Copyright
_© 2018 Jianqiao Zong, Huaqing Fang, Yifan Li All Rights Reserved_
