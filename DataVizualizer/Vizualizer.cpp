#include <graphics.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include "avltree.h"
#define noOfDS 2

using namespace std;


struct dataStructure
{
    char *name;
    int xStart, xEnd;
}dataStructures[noOfDS];

float maxX,maxY;

void printArrow(int x, int y,int width,int color)
{
    setcolor(color);
    line(x+width/2,y,x+width/2,y-10);
    line(x+width/2,y,x+width/2-3,y-3);
    line(x+width/2,y,x+width/2+3,y-3);
}

bool searchInTree(node * root,int noInserted, int startX,int startY,int gap)
{
    if(root==NULL)
        return false;
    char c[5];
    sprintf(c,"%d",root->data);
    printArrow(startX,startY,textwidth(c),15);
    Sleep(1000);
    if(root->data==noInserted)
    {
        printArrow(startX,startY,textwidth(c),4);
        settextstyle(3,HORIZ_DIR,4);
        outtextxy(maxX/2-100,maxY/2-100,"ELEMENT FOUND");
        Sleep(1000);
        settextstyle(3,HORIZ_DIR,2);
        return true;
    }
    else if(root->data>noInserted)
        return searchInTree(root->left,noInserted,startX-gap,startY+50,gap/2);
    else
        return searchInTree(root->right,noInserted,startX+gap,startY+50,gap/2);
}

void printTree(tree avlTree, node * root,int startX, int startY,int gap,int prevX,int prevY)
{
    /*avlTree.levelOrder(root);
    int j=0;
    for(int i=1;i<=avlTree.arraySize;i++)
    {
        int startX=maxX/2-40*(int)pow(2,i-2);
        int startY=250+40*(i-1);
        for(int k=1;k<=pow(2,i-1);k++)
        {
            char c[4];
            if(avlTree.levelOrderArray[j]>0)
                sprintf(c,"%d",avlTree.levelOrderArray[j]);
            else
                sprintf(c," ");
            outtextxy(startX,startY,c);
            startX+=40;
            j++;
        }
    }*/
    if(root==NULL)
        return;
    char c[5];
    sprintf(c,"%d",root->data);
    outtextxy(startX,startY,c);
    int h=textheight(c);
    int w=textwidth(c);
    if(prevX>0 && prevY>0)
        line(prevX,prevY,startX+w/2,startY);
    printTree(avlTree,root->left,startX-gap,startY+50,gap/2,startX+w/2,startY+h);
    printTree(avlTree,root->right,startX+gap,startY+50,gap/2,startX+w/2,startY+h);
}

int printOperations()
{
    settextstyle(3,HORIZ_DIR,3);
    setcolor(7);
    int flag=-1;
    POINT cursorPosition;
    GetCursorPos(&cursorPosition);
    int height=textheight("A");
    if(cursorPosition.x>=200 && cursorPosition.x<=200+textwidth("Insert new Key") && cursorPosition.y>=100 && cursorPosition.y<=100+height)
    {
        setcolor(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON))
            {
                flag=0;
                Sleep(400);
            }
    }
    outtextxy(200,100,"Insert new Key");
    setcolor(7);
    if(cursorPosition.x>=200+maxX/4 && cursorPosition.x<=200+maxX/4+textwidth("Search a Key") && cursorPosition.y>=100 && cursorPosition.y<=100+height)
    {
        setcolor(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON))
            {
                flag=1;
                Sleep(400);
            }
    }
    outtextxy(200+maxX/4,100,"Search a Key");
    setcolor(7);
    if(cursorPosition.x>=200+maxX/2 && cursorPosition.x<=200+maxX/2+textwidth("Delete a Key") && cursorPosition.y>=100 && cursorPosition.y<=100+height)
    {
        setcolor(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON))
            flag=2;
    }
    outtextxy(200+maxX/2,100,"Delete a Key");
    return flag;
}

int printBackButton()
{
    int flag=-1;
    POINT cursorPosition;
    GetCursorPos(&cursorPosition);
    if(cursorPosition.x>=20 && cursorPosition.x<=70 && cursorPosition.y>=30 && cursorPosition.y<=55)
    {
        setcolor(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON))
            flag=0;
    }
    line(20,40,40,30);
    line(40,30,40,35);
    line(40,35,70,25);

    line(20,40,40,50);
    line(40,50,40,45);
    line(40,45,70,55);

    line(70,25,70,55);
    return flag;
}

void AVLTREE()
{
    int pageNo=0;
    tree avlTree;
    int temp;
    node*root=NULL;
    int noInserted,c;
    while(1)
    {
        setactivepage(pageNo);
        setvisualpage(1-pageNo);
        cleardevice();
        setcolor(12);
        if(printBackButton()==0)
            break;
        switch(printOperations())
        {
        case 0:
            noInserted=0;
            while((c=(int)getch())!=13)
            {
                if(c>=48 && c<=57)
                    noInserted=noInserted*10+c-48;
            }
            root= avlTree.insertNode(root,noInserted);
            Sleep(200);
            //for(int i=0;i<pow(2,avlTree.arraySize)-1;i++)
              //  cout<<" "<<avlTree.levelOrderArray[i];
            break;
        case 1:
            noInserted=0;
            while((c=(int)getch())!=13)
            {
                if(c>=48 && c<=57)
                    noInserted=noInserted*10+c-48;
            }
            setvisualpage(pageNo);
            printTree(avlTree,root,maxX/2,maxY/2,160,-1,-1);
            if(!searchInTree(root,noInserted,maxX/2,maxY/2,160))
                {
                    settextstyle(3,HORIZ_DIR,4);
                    outtextxy(maxX/2-100,maxY/2-100,"NOT FOUND");
                    Sleep(1000);
                    settextstyle(3,HORIZ_DIR,2);
                }
            setvisualpage(1-pageNo);
        }
        printTree(avlTree,root,maxX/2,maxY/2,160,-1,-1);
        //Sleep(1000);
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
        setcolor(WHITE);
        if(cursorPosition.x>=maxX-50 && cursorPosition.x<=maxX-25 && cursorPosition.y>=10 && cursorPosition.y<=35)
        {
             setcolor(GREEN);
             if(GetAsyncKeyState(VK_LBUTTON))
                flag=9;
        }
        line(maxX-50,10,maxX-25,35);
        line(maxX-50,35,maxX-25,10);
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
    case 9:
        exit(0);
    }

    goto GAMESTART;

    getch();

    closegraph();
}
