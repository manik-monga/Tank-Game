#include<graphics.h>
#include<windows.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include"map.h"
#include"Tank.h"
#include"Bullet.h"
#include"PowerUps.h"

void Menu()
{
    //Home Screen window
    initwindow(900,600,"HOME",100,100);
    POINT CursorPosition;

    while(1)
    {
        settextstyle(9,HORIZ_DIR,5);
        setcolor(RED);
        outtextxy(200,100,"TANK GAME");
        settextstyle(9,HORIZ_DIR,1);
        setcolor(WHITE);
        outtextxy(300,200,"MENU");
        outtextxy(220,250,"1. START");
        outtextxy(220,300,"2. HOW TO PLAY");

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            GetCursorPos(&CursorPosition);
            //Mouse Click To start the game
            if((CursorPosition.x>=350 && CursorPosition.x<=430) && (CursorPosition.y>=370 && CursorPosition.y<=390))
            {
                Loading:
                //loading screen
                for(int i=0; i<455; i++)
                {
                    delay(10);
                    setfillstyle(SOLID_FILL,10);
                    rectangle(250,450,550,470);
                    bar(250,450,250+2*i,470);
                    settextstyle(9,HORIZ_DIR,1);
                    outtextxy(320,500,"LOADING . . .");

                    if(i>150)
                    {
                        delay(100);
                        return ;
                    }
                }
            }
            //Mouse click for Instructions
            if((CursorPosition.x>=350 && CursorPosition.x<=510) && (CursorPosition.y>=420 && CursorPosition.y<=440))
            {
                //INSTRUCTIONS Window
                initwindow(900,600,"INSTRUCTIONS",100,100,false,false);
                while(1)
                {
                    outtextxy(50,50,"PLAYER 1:");
                    outtextxy(50,90,"W - Move Up");
                    outtextxy(50,130,"A - Left");
                    outtextxy(50,170,"S - Bottom");
                    outtextxy(50,210,"D - Right");
                    outtextxy(50,250,"Left Control - Fire");

                    outtextxy(550,50,"PLAYER 2:");
                    outtextxy(550,90,"UP Arrow Key - Move Up");
                    outtextxy(550,130,"Left Arrow Key - Left");
                    outtextxy(550,170,"Down Arrow Key - Bottom");
                    outtextxy(550,210,"Right Arrow Key - Right");
                    outtextxy(550,250,"Right Control - Fire");
                    outtextxy(750,470,"START >>");

                    if(GetAsyncKeyState(VK_LBUTTON))

                    {   GetCursorPos(&CursorPosition);
                        //mouse click to start the game from instructions window
                        if((CursorPosition.x>=850 && CursorPosition.x<=920) && (CursorPosition.y>=590 && CursorPosition.y<=610))
                        {
                            goto Loading ;
                        }
                    }
                }
            }

         }

    }
}


int main()
{
    Again:
    GameActive = true;
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    Menu();

    initwindow(width, height,"Stuart Tank",-3, 0, false, true);
    int page=0;

    while(GameActive)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        T1Coordinates();
        T2Coordinates();
        DrawMap();

        if(GetAsyncKeyState('W'))
        {
            MoveFront();
            T1Coordinates();
            if(ConditionCheck()==0)
            {
                MoveBack();
                T1Coordinates();
            }
        }
        if(GetAsyncKeyState('S'))
        {
            MoveBack();
            T1Coordinates();
            if(ConditionCheck()==0)
            {
                MoveFront();
                T1Coordinates();
            }
        }
       if(GetAsyncKeyState('D'))
        {
            angle1 -= M_PI/45.0;
            degree1 -=4;                   //4 degree
            T1Coordinates();
             if(ConditionCheck()==0)
            {
                angle1 += M_PI/45.0;
                degree1 +=4;
                T1Coordinates();
            }
        }
        if(GetAsyncKeyState('A'))
        {
            angle1 += M_PI/45.0;
            degree1 +=4;                  //4 degree
            T1Coordinates();
            if(ConditionCheck()==0)
            {
                angle1 -= M_PI/45.0;
                degree1 -=4;
                T1Coordinates();
            }
        }
        if(GetAsyncKeyState(VK_LCONTROL))
        {
            NewBullet1();
        }
         if(GetAsyncKeyState(VK_UP))
        {
            MoveFront2();
            T2Coordinates();
            if(ConditionCheck2()==0)
            {
                MoveBack2();
                T2Coordinates();
            }
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            MoveBack2();
            T2Coordinates();
            if(ConditionCheck2()==0)
            {
                MoveFront2();
                T2Coordinates();
            }
        }
       if(GetAsyncKeyState(VK_RIGHT))
        {
            angle2 -= M_PI/45.0;
            degree2 -=4;                   //4 degree
            T2Coordinates();
             if(ConditionCheck2()==0)
            {
                angle2 += M_PI/45.0;
                degree2 +=4;
                T2Coordinates();
            }
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            angle2 += M_PI/45.0;
            degree2 +=4;                  //4 degree
            T2Coordinates();
            if(ConditionCheck2()==0)
            {
                angle2 -= M_PI/45.0;
                degree2 -=4;
                T2Coordinates();
            }
        }
        if(GetAsyncKeyState(VK_RCONTROL))
        {
            NewBullet2();
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            GameActive = false;
        }
        DrawTank();
        DrawTank2();
        MoveBullet1();
        MoveBullet2();
        HealthUp();
        LifeBar();
        page=1-page;
        delay(10);
     }

    getch();
    closegraph();
    Tank1X = 300 , Tank1Y = 540;
    Tank2x = 1300 , Tank2y = 140;
    angle1=M_PI_4;
    angle2=(-M_PI_2 -M_PI_4);
    degree1=0;
    degree2=-180;
    Life1 = 3;
    Life2 = 3;
    goto Again;

}
