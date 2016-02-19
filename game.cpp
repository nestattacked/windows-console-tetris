#include"game.h"
#include"util.h"
#include"modechooser.h"
#include"keymaroc.h"
#include<time.h>
#include<windows.h>
#include<iostream>
#include<conio.h>

using namespace std;

int Game::blocks[28][8] = {
{2, 1, 0, 0, 2, 0, 0, 1},
{2, 1, 0, 0, 2, 0, 0, 1},
{2, 1, 0, 0, 2, 0, 0, 1},
{2, 1, 0, 0, 2, 0, 0, 1},
{2, 1, 0, 1, 4, 1, 6, 1},
{2, 1, 2, 0, 2, 2, 2, 3},
{2, 1, 0, 1, 4, 1, 6, 1},
{2, 1, 2, 0, 2, 2, 2, 3},
{2, 1, 0, 0, 0, 1, 4, 1},
{2, 1, 2, 0, 4, 0, 2, 2},
{2, 1, 0, 1, 4, 1, 4, 2},
{2, 1, 2, 0, 0, 2, 2, 2},
{2, 1, 4, 0, 0, 1, 4, 1},
{2, 1, 2, 0, 2, 2, 4, 2},
{2, 1, 0, 1, 4, 1, 0, 2},
{2, 1, 0, 0, 2, 0, 2, 2},
{2, 1, 2, 0, 0, 1, 4, 1},
{2, 1, 2, 0, 4, 1, 2, 2},
{2, 1, 0, 1, 4, 1, 2, 2},
{2, 1, 2, 0, 0, 1, 2, 2},
{2, 1, 2, 0, 4, 0, 0, 1},
{2, 1, 2, 0, 4, 1, 4, 2},
{2, 1, 2, 0, 4, 0, 0, 1},
{2, 1, 2, 0, 4, 1, 4, 2},
{2, 1, 2, 0, 4, 1, 0, 0},
{2, 1, 2, 0, 0, 1, 0, 2},
{2, 1, 2, 0, 4, 1, 0, 0},
{2, 1, 2, 0, 0, 1, 0, 2}
};

Game::Game(){
    //set rand
    srand((unsigned)time(NULL));
    //set color
    system("color f2");
    //hide cursor
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.bVisible=false;
    cursor_info.dwSize = sizeof(cursor_info);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);

    //choose mode
    mode_number = ModeChooser::getMode();

    //draw game's UI
    cout<<"┏━━━━━━━━━━━━┓┏━━━━┓"<<endl;
    cout<<"┃                        ┃┃下一方块┃"<<endl;
    cout<<"┃                        ┃┣━━━━┫"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┃                        ┃┗━━━━┛"<<endl;
    cout<<"┃                        ┃┏━━━━┓"<<endl;
    cout<<"┃                        ┃┃  难度  ┃"<<endl;
    cout<<"┃                        ┃┣━━━━┫"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┃                        ┃┣━━━━┫"<<endl;
    cout<<"┃                        ┃┃  分数  ┃"<<endl;
    cout<<"┃                        ┃┣━━━━┫"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┃                        ┃┣━━━━┫"<<endl;
    cout<<"┃                        ┃┃  消息  ┃"<<endl;
    cout<<"┃                        ┃┣━━━━┫"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┃                        ┃┃        ┃"<<endl;
    cout<<"┗━━━━━━━━━━━━┛┗━━━━┛"<<endl;

    //init data
    for(int i=0;i<12;i++)
        for(int j=0;j<21;j++)
            space[j][i]=0;
    level = 1;
    score = 0;
    alive = 1;
    next_block_type = Util::getRand(28);
    getNewBlock();
    if(mode_number==2)
	{
		int n,m;
		for(n=20;n>6;n--){
			for(m=0;m<12;m++){
				if(Util::getRand(3)!=0)
					space[n][m]=1;
			}
		}
	}
    //draw mode statement
    showLevel();
    showScore();
    showMode();
    showMain();
    showRunningBlock();
}

void Game::start(){
    int index,times=0;
    while(1)
    {
        for(index=0;index<(11-level)*10;index++)
        {
            if(kbhit())
            {
                char key;
                key=getch();
                switch(key)
                {
                case LEFT:
                    left();
                    break;
                case RIGHT:
                    right();
                    break;
                case UP:
                    change();
                    break;
                case DOWN:
                    down();
                    if(!alive)
                    {
                        clearBlock();
                    }
                    break;
                case SPACEBAR:
                    spacebar();
                    clearBlock();
                    break;
                }
            }
            Sleep(10);
			if(mode_number==3){
				times++;
				if(times==800){
					int x1,y1;
					for(y1=0;y1<20;y1++){
						for(x1=0;x1<12;x1++){
							space[y1][x1]=space[y1+1][x1];
						}
					}
					for(x1=0;x1<12;x1++){
						space[y1][x1]=Util::getRand(2);
					}
					showMain();
					times=0;
				}
			}
        }
        down();
        if(!alive){
            clearBlock();
        }
    }
}

void Game::showLevel(){
    Util::go(30,11);
    cout<<level;
}

void Game::showScore(){
    Util::go(30,15);
    cout<<score;
}

void Game::showMode(){
    Util::go(30,19);
    switch(mode_number)
	{
	case 1:
		cout<<"正常模式";
		break;
	case 2:
		cout<<"残局模式";
		break;
	case 3:
		cout<<"死亡模式";
		break;
	default:
		break;
	}
}

void Game::showNextBlock(){
    for(int i=3;i<=6;i++){
        Util::go(30,i);
        cout<<"        ";
    }
    for(int i=0;i<4;i++){
        Util::go(blocks[next_block_type][2*i]+30,blocks[next_block_type][2*i+1]+3);
        cout<<"■";
    }
}

void Game::wipeRunningBlock(){
    for(int i=0;i<4;i++){
        Util::go(blocks[block_type][2*i]+2*block_positionx,blocks[block_type][2*i+1]+block_positiony);
        cout<<"  ";
    }
}

void Game::showRunningBlock(){
    for(int i=0;i<4;i++){
        Util::go(blocks[block_type][2*i]+2*block_positionx,blocks[block_type][2*i+1]+block_positiony);
        cout<<"■";
    }
}

void Game::showMain(){
    Util::color(0xf4);
    int i,j;
    for(i=0;i<21;i++){
        for(j=0;j<12;j++){
            Util::go(2*j+2,i+1);
            cout<<"  ";
            if(space[i][j]==1){
                Util::go(2*j+2,i+1);
                cout<<"■";
            }
        }
    }
    Util::color(0xf2);
}

void Game::getNewBlock(){
    block_positionx = 5;
    block_positiony = 1;
    block_type = next_block_type;
    next_block_type = Util::getRand(28);
    showNextBlock();
}

void Game::left(){
    wipeRunningBlock();
    int temp = block_positionx;
    block_positionx--;
    if(blockOut()||blockExist())
        block_positionx = temp;
    showRunningBlock();
}

void Game::right(){
    wipeRunningBlock();
    int temp = block_positionx;
    block_positionx++;
    if(blockOut()||blockExist())
        block_positionx = temp;
    showRunningBlock();
}

void Game::down(){
    wipeRunningBlock();
    int temp = block_positiony;
    block_positiony++;
    if(blockExist()||blockEnd()){
        alive = 0;
        block_positiony = temp;
        space[blocks[block_type][1] + block_positiony - 1][blocks[block_type][0]/2 + block_positionx - 1] = 1;
        space[blocks[block_type][3] + block_positiony - 1][blocks[block_type][2]/2 + block_positionx - 1] = 1;
        space[blocks[block_type][5] + block_positiony - 1][blocks[block_type][4]/2 + block_positionx - 1] = 1;
        space[blocks[block_type][7] + block_positiony - 1][blocks[block_type][6]/2 + block_positionx - 1] = 1;
        showMain();
    }
    else
        showRunningBlock();
}

void Game::clearBlock(){
    boom();
    showMain();
    showLevel();
    showScore();
    getNewBlock();//work here here here here here here
    showRunningBlock();
    alive = 1;
    if(blockExist()){
        Util::go(30,19);
        cout<<"  失败  ";
        Util::go(30,20);
        cout<<"按ESC键";
        Util::go(30,21);
        cout<<"退出游戏";
        while(1)
        {
            if(getch()==ESC)
            {
                exit(-1);
            }
        }
    }
}

void Game::spacebar(){
    while(alive){
        down();
    }
}

void Game::change(){
    wipeRunningBlock();
    int temp = block_type;
    int index = block_type%4;
    if(index==3)
        block_type-=3;
    else
        block_type++;
    if(blockOut()||blockEnd()||blockExist())
        block_type = temp;
    showRunningBlock();
}

int Game::blockEnd(){
    if(blocks[block_type][1]+block_positiony>21)
        return 1;
    if(blocks[block_type][3]+block_positiony>21)
        return 1;
    if(blocks[block_type][5]+block_positiony>21)
        return 1;
    if(blocks[block_type][7]+block_positiony>21)
        return 1;
    return 0;
}

int Game::blockExist(){
    return space[blocks[block_type][1]+block_positiony-1][blocks[block_type][0]/2+block_positionx-1]+
    space[blocks[block_type][3]+block_positiony-1][blocks[block_type][2]/2+block_positionx-1]+
    space[blocks[block_type][5]+block_positiony-1][blocks[block_type][4]/2+block_positionx-1]+
    space[blocks[block_type][7]+block_positiony-1][blocks[block_type][6]/2+block_positionx-1];
}

int Game::blockOut(){
    if(blocks[block_type][0]+2*block_positionx<2||blocks[block_type][0]+2*block_positionx>24)
        return 1;
    if(blocks[block_type][2]+2*block_positionx<2||blocks[block_type][2]+2*block_positionx>24)
        return 1;
    if(blocks[block_type][4]+2*block_positionx<2||blocks[block_type][4]+2*block_positionx>24)
        return 1;
    if(blocks[block_type][6]+2*block_positionx<2||blocks[block_type][6]+2*block_positionx>24)
        return 1;
    return 0;
}

void Game::boom(){
    int mark[21];
    int i,j,now;
    for(i=0;i<21;i++)
    {
        mark[i]=1;
        for(j=0;j<12;j++)
        {
            if(space[i][j]==0)
            {
                mark[i]=0;
            }
        }
		if(mark[i]==1)
		{
			score+=2;
		}
    }
    now=20;
    for(i=20;i>=0;i--)
    {
        if(mark[i]==0)
        {
            for(j=0;j<12;j++)
            {
                space[now][j]=space[i][j];
            }
            now--;
        }
    }
    while(now+1)
    {
        for(j=0;j<12;j++)
        {
            space[now][j]=0;
        }
        now--;
    }
	if(score>=level*50)
	{
		level++;
		if(level==11)
        {
            Util::go(30,19);
            cout<<"  通关  ";
            Util::go(30,20);
            cout<<"按ESC键";
            Util::go(30,21);
            cout<<"退出游戏";
            while(1)
            {
                if(getch()==ESC)
                {
                    exit(-1);
                }
            }
        }
	}
}
