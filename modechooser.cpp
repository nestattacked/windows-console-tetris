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
    cout<<"����������������������������"<<endl;
	cout<<"��       ����˹����       ��"<<endl;
	cout<<"��                        ��"<<endl;
	cout<<"��            ��ͨ        ��"<<endl;
	cout<<"��            �о�        ��"<<endl;
	cout<<"��            ����        ��"<<endl;
	cout<<"�ĩ�������������������������"<<endl;
	cout<<"��    �� �� ѡ��ģʽ      ��"<<endl;
	cout<<"��                        ��"<<endl;
	cout<<"��       �ո��ȷ��       ��"<<endl;
	cout<<"�ĩ�������������������������"<<endl;
	cout<<"��       ��Ϸ����         ��"<<endl;
	cout<<"��  ��           �任     ��"<<endl;
	cout<<"��  ������       �ƶ�     ��"<<endl;
	cout<<"��  space        �������� ��"<<endl;
	cout<<"������Ϸ��Ϣ��ʾ�����½ǣ���"<<endl;
	cout<<"�ĩ�������������������������"<<endl;
	cout<<"��  code by nestattacked  ��"<<endl;
	cout<<"��  qq:283349242          ��"<<endl;
	cout<<"����������������������������"<<endl;

	//print choose arrow
	int positionx = 9, positiony = 3;
	Util::go(positionx,positiony);
	Util::color(0xf0);
	cout<<"��";

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
	    cout<<"��";
	}

}
