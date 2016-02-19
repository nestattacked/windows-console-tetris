#include"util.h"
#include<windows.h>
#include<conio.h>

int Util::getRand(int max_number){
    return rand()%max_number;
}

void Util::color(int n_color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n_color);
}

void Util::go(int x, int y){
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
