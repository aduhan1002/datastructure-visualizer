#include <graphics.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#define noOfDS 2

using namespace std;


struct dataStructure
{
    char *name;
    int xStart, xEnd;
}dataStructures[noOfDS];

float maxX,maxY;

void printBackButton()
{
    line(20,40,40,30);
    line(40,30,40,35);
    line(40,35,70,25);

    line(20,40,40,50);
    line(40,50,40,45);
    line(40,45,70,55);

    line(70,25,70,55);
}

void AVLTREE()
{
    int pageNo=0;
    while(1)
    {
        setactivepage(pageNo);
        setvisualpage(1-pageNo);
        cleardevice();
        printBackButton();
        Sleep(1000);
        pageNo=1-pageNo;
    }
}

int start()
{
    int pageNo=0;
    int flag=-1;
    while(1)
    {
        setactivepage(pageNo);
        setvisualpage(1-pageNo);
        cleardevice();

        settextstyle(COMPLEX_FONT,HORIZ_DIR,3);
        setcolor(WHITE);
        outtextxy(maxX/2-(textwidth("CHOOSE DATATYPE")/2),20,"CHOOSE DATATYPE");
        settextstyle(3,HORIZ_DIR,2);

        int heightStart=55;
        int heightEnd=heightStart+textheight("A");

        POINT cursorPosition;
        GetCursorPos(&cursorPosition);

        for(int i=0;i<noOfDS;i++)
        {
            setcolor(12);
            if(cursorPosition.x>=dataStructures[i].xStart && cursorPosition.x<=dataStructures[i].xEnd && cursorPosition.y>=heightStart && cursorPosition.y<=heightEnd)
                {
                    setcolor(GREEN);
                    if(GetAsyncKeyState(VK_LBUTTON))
                        flag=i;
                }
            outtextxy(dataStructures[i].xStart,55,dataStructures[i].name);
        }
        pageNo=1-pageNo;
        if(flag!=-1)
            return flag;
    }
}

void fillDataStructures()
{
    settextstyle(3,HORIZ_DIR,2);
    dataStructures[0].name=new char[9];
    strcpy(dataStructures[0].name,"AVL Tree");
    dataStructures[0].xStart=15;
    dataStructures[0].xEnd=15+textwidth("AVL Tree");

    dataStructures[1].name=new char[15];
    strcpy(dataStructures[1].name,"RED-BLACK Tree");
    dataStructures[1].xStart=dataStructures[0].xEnd+25;
    dataStructures[1].xEnd=dataStructures[1].xStart+textwidth("RED-BLACK Tree");
}

int main()
{
    int gd = DETECT, gm;

    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    //char driver[]="C:\\TC\\BGI";
    //initgraph(&gd, &gm, driver);

    initwindow(screenWidth, screenHeight, "",-3,-3);

    maxX=getmaxx();
    maxY=getmaxy();

    fillDataStructures();

    GAMESTART:
    switch(start())
    {
    case 0:
        AVLTREE();
        break;
    case 1:
        //REDBLACKTREE();
        break;
    }

    goto GAMESTART;

    getch();

    closegraph();
}
