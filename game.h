#ifndef _GAME_
#define _GAME_

class Game{
public:
    Game();
    void start();
private:
    int score;
    int level;
    int mode_number;
    int space[21][12];
    int alive;
    int block_type;
    int block_positionx,block_positiony;//logical position
    int next_block_type;
    static int blocks[28][8];

    void getNewBlock();

    void showScore();
    void showLevel();
    void showMode();
    void showNextBlock();
    void showRunningBlock();
    void wipeRunningBlock();
    void showMain();

    void left();
    void right();
    void down();
    void change();
    void spacebar();
    void clearBlock();

    int blockEnd();
    int blockExist();
    int blockOut();

    void boom();
};

#endif
