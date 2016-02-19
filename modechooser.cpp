#include"modechooser.h"
#include"util.h"
#include"keymaroc.h"
#include<iostream>
#include<windows.h>
#include<conio.h>

using namespace std;

int ModeChooser::getMode(){
    //draw chooser UI
    system("cls");
    cout<<"┏━━━━━━━━━━━━┓"<<endl;
	cout<<"┃       俄罗斯方块       ┃"<<endl;
	cout<<"┃                        ┃"<<endl;
	cout<<"┃            普通        ┃"<<endl;
	cout<<"┃            残局        ┃"<<endl;
	cout<<"┃            死亡        ┃"<<endl;
	cout<<"┠━━━━━━━━━━━━┫"<<endl;
	cout<<"┃    ↑ ↓ 选择模式      ┃"<<endl;
	cout<<"┃                        ┃"<<endl;
	cout<<"┃       空格键确认       ┃"<<endl;
	cout<<"┠━━━━━━━━━━━━┫"<<endl;
	cout<<"┃       游戏操作         ┃"<<endl;
	cout<<"┃  ↑           变换     ┃"<<endl;
	cout<<"┃  ←↓→       移动     ┃"<<endl;
	cout<<"┃  space        快速下落 ┃"<<endl;
	cout<<"┃（游戏信息显示在右下角）┃"<<endl;
	cout<<"┠━━━━━━━━━━━━┫"<<endl;
	cout<<"┃  code by nestattacked  ┃"<<endl;
	cout<<"┃  qq:283349242          ┃"<<endl;
	cout<<"┗━━━━━━━━━━━━┛"<<endl;

	//print choose arrow
	int positionx = 9, positiony = 3;
	Util::go(positionx,positiony);
	Util::color(0xf0);
	cout<<"→";

	//wait for user's operation
	while(1){
	    char key = getch();
        Util::go(positionx,positiony);
	    cout<<"  ";
	    switch(key){
        case UP:
            if(positiony>3)
                positiony--;
            break;
        case DOWN:
            if(positiony<5)
                positiony++;
            break;
        case SPACEBAR:
            system("cls");
            Util::color(0xf2);
            return positiony-2;
            break;
        default:
            break;
	    }
	    Util::go(positionx,positiony);
	    cout<<"→";
	}

}
