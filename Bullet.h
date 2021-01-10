bool GameActive = true;
//Bullet for Tank
static const int Max_Bullet = 5;
static const double Bullet_Speed = 5.0;
int Life1 = 3;
int Life2 = 3;

struct BulletInfo
{
    bool IsActive = false;
    int X_Pos=0, Y_Pos=0;
    double angle=0.0;
    clock_t ReleaseTime = 0;
};

BulletInfo Bullet1[Max_Bullet];
BulletInfo Bullet2[Max_Bullet];
clock_t LastBulletFired1 = clock();
clock_t LastBulletFired2 = clock();

void NewBullet1()
{
    clock_t CurrentTime = clock();
    int TimeInterval = int ((CurrentTime - LastBulletFired1)/CLOCKS_PER_SEC);
    if(TimeInterval<1)
        return;

    int i;

    for(i=0;i<Max_Bullet;i++)
    {
        if(Bullet1[i].IsActive==false)
        {
            break;
        }
    }

    if(i==Max_Bullet)
        return;

    Bullet1[i].IsActive = true;
    Bullet1[i].angle = angle1 - M_PI_4;
    Bullet1[i].X_Pos = Tank1X + (int)(35.0*cos(angle1-M_PI_4));
    Bullet1[i].Y_Pos = Tank1Y - (int)(35.0*sin(angle1-M_PI_4));
    Bullet1[i].ReleaseTime = CurrentTime;
    LastBulletFired1 = CurrentTime;
}

void NewBullet2()
{
    clock_t CurrentTime = clock();
    int TimeInterval = int ((CurrentTime - LastBulletFired2)/CLOCKS_PER_SEC);
    if(TimeInterval<1)
        return;

    int i;

    for(i=0;i<Max_Bullet;i++)
    {
        if(Bullet2[i].IsActive==false)
        {
            break;
        }
    }

    if(i==Max_Bullet)
        return;

    Bullet2[i].IsActive = true;
    Bullet2[i].angle = angle2 - M_PI_4;
    Bullet2[i].X_Pos = Tank2x + (int)(35.0*cos(angle2-M_PI_4));
    Bullet2[i].Y_Pos = Tank2y - (int)(35.0*sin(angle2-M_PI_4));
    Bullet2[i].ReleaseTime = CurrentTime;
    LastBulletFired2 = CurrentTime;
}

void MoveBullet1()
{
    clock_t CurrentTime = clock();
    int BulletSurvivalTime;
    setlinestyle(SOLID_LINE, 0, 3);

    for(int i=0; i<Max_Bullet; i++)
        {
            if(Bullet1[i].IsActive == true)
            {
                BulletSurvivalTime = int ((CurrentTime - Bullet1[i].ReleaseTime)/CLOCKS_PER_SEC);
                if(BulletSurvivalTime > 10)
                {
                    Bullet1[i].IsActive = false;
                    continue;
                }


                    Bullet1[i].X_Pos += (int)(Bullet_Speed * cos(Bullet1[i].angle));
                    Bullet1[i].Y_Pos -= (int)(Bullet_Speed * sin(Bullet1[i].angle));

                    if(getpixel(Bullet1[i].X_Pos, Bullet1[i].Y_Pos) == BLACK &&
                   (getpixel(Bullet1[i].X_Pos+2, Bullet1[i].Y_Pos+2) == BLACK || getpixel(Bullet1[i].X_Pos-2, Bullet1[i].Y_Pos+2) == BLACK ||
                    getpixel(Bullet1[i].X_Pos+2, Bullet1[i].Y_Pos-2) == BLACK || getpixel(Bullet1[i].X_Pos-2, Bullet1[i].Y_Pos-2) == BLACK))
                    {
                        Bullet1[i].X_Pos -= (int)(Bullet_Speed * cos(Bullet1[i].angle));

                        if(getpixel(Bullet1[i].X_Pos, Bullet1[i].Y_Pos) == 0)
                        {
                            // DEFLECTING FROM HORIZONTAL SURFACE
                            Bullet1[i].Y_Pos += (int)(Bullet_Speed * sin(Bullet1[i].angle));
                            Bullet1[i].angle = -Bullet1[i].angle;
                        }
                        else
                        {
                            // DEFLEFCTING FROM VERTICAL SURFACE
                            Bullet1[i].Y_Pos += (int)(Bullet_Speed * sin(Bullet1[i].angle));
                            Bullet1[i].angle = M_PI - Bullet1[i].angle;
                        }

                    }
                 if(/*getpixel(Bullet1[i].X_Pos, Bullet1[i].Y_Pos) == GREEN &&*/
                   (getpixel(Bullet1[i].X_Pos+2, Bullet1[i].Y_Pos+2) == GREEN || getpixel(Bullet1[i].X_Pos-2, Bullet1[i].Y_Pos+2) == GREEN ||
                    getpixel(Bullet1[i].X_Pos+2, Bullet1[i].Y_Pos-2) == GREEN || getpixel(Bullet1[i].X_Pos-2, Bullet1[i].Y_Pos-2) == GREEN))
                {
                    Bullet1[i].IsActive = false ;
                    Life2 = Life2 - 1 ;
                    if(Life2<1)
                    GameActive = false;

                    Tank2x = 1300;
                    Tank2y = 140;
                    angle2=(-M_PI_4 -M_PI_2);
                    degree2=-180;
                }
                if(/*getpixel(Bullet1[i].X_Pos, Bullet1[i].Y_Pos) == RED &&*/
                  (getpixel(Bullet1[i].X_Pos+2, Bullet1[i].Y_Pos+2) == RED || getpixel(Bullet1[i].X_Pos-2, Bullet1[i].Y_Pos+2) == RED ||
                   getpixel(Bullet1[i].X_Pos+2, Bullet1[i].Y_Pos-2) == RED || getpixel(Bullet1[i].X_Pos-2, Bullet1[i].Y_Pos-2) == RED))
                {
                    Bullet1[i].IsActive = false ;
                    Life1 = Life1 - 1 ;
                    if(Life1<1)
                    GameActive = false;

                    Tank1X = 300;
                    Tank1Y = 540;
                    angle1=M_PI_4;
                    degree1=0;
                }

                    circle(Bullet1[i].X_Pos, Bullet1[i].Y_Pos,2);

            }
        }

}


void MoveBullet2()
{
    clock_t CurrentTime = clock();
    int BulletSurvivalTime;
    setlinestyle(SOLID_LINE, 0, 3);

    for(int i=0; i<Max_Bullet; i++)
        {
            if(Bullet2[i].IsActive == true)
            {
                BulletSurvivalTime = int ((CurrentTime - Bullet2[i].ReleaseTime)/CLOCKS_PER_SEC);
                if(BulletSurvivalTime > 10)
                {
                    Bullet2[i].IsActive = false;
                    continue;
                }


                    Bullet2[i].X_Pos += (int)(Bullet_Speed * cos(Bullet2[i].angle));
                    Bullet2[i].Y_Pos -= (int)(Bullet_Speed * sin(Bullet2[i].angle));

                  if(getpixel(Bullet2[i].X_Pos, Bullet2[i].Y_Pos) == BLACK &&
                   (getpixel(Bullet2[i].X_Pos+2, Bullet2[i].Y_Pos+2) == BLACK || getpixel(Bullet2[i].X_Pos-2, Bullet2[i].Y_Pos+2) == BLACK ||
                    getpixel(Bullet2[i].X_Pos+2, Bullet2[i].Y_Pos-2) == BLACK || getpixel(Bullet2[i].X_Pos-2, Bullet2[i].Y_Pos-2) == BLACK))
                    {
                        Bullet2[i].X_Pos -= (int)(Bullet_Speed * cos(Bullet2[i].angle));

                        if(getpixel(Bullet2[i].X_Pos, Bullet2[i].Y_Pos) == 0)
                        {
                            // DEFLECTING FROM HORIZONTAL SURFACE
                            Bullet2[i].Y_Pos += (int)(Bullet_Speed * sin(Bullet2[i].angle));
                            Bullet2[i].angle = -Bullet2[i].angle;
                        }
                        else
                        {
                            // DEFLEFCTING FROM VERTICAL SURFACE
                            Bullet2[i].Y_Pos += (int)(Bullet_Speed * sin(Bullet2[i].angle));
                            Bullet2[i].angle = M_PI - Bullet2[i].angle;
                        }

                    }
                 if(/*getpixel(Bullet2[i].X_Pos, Bullet2[i].Y_Pos) == GREEN &&*/
                   (getpixel(Bullet2[i].X_Pos+2, Bullet2[i].Y_Pos+2) == GREEN || getpixel(Bullet2[i].X_Pos-2, Bullet2[i].Y_Pos+2) == GREEN ||
                    getpixel(Bullet2[i].X_Pos+2, Bullet2[i].Y_Pos-2) == GREEN || getpixel(Bullet2[i].X_Pos-2, Bullet2[i].Y_Pos-2) == GREEN))
                {
                    Bullet2[i].IsActive = false ;
                    Life2 = Life2 - 1 ;
                    if(Life2<1)
                    GameActive = false;

                    Tank2x = 1300;
                    Tank2y = 140;
                    angle2=(-M_PI_4 -M_PI_2);
                    degree2=-180;
                }
                if(/*getpixel(Bullet2[i].X_Pos, Bullet2[i].Y_Pos) == RED &&*/
                  (getpixel(Bullet2[i].X_Pos+2, Bullet2[i].Y_Pos+2) == RED || getpixel(Bullet2[i].X_Pos-2, Bullet2[i].Y_Pos+2) == RED ||
                   getpixel(Bullet2[i].X_Pos+2, Bullet2[i].Y_Pos-2) == RED || getpixel(Bullet2[i].X_Pos-2, Bullet2[i].Y_Pos-2) == RED))
                {
                    Bullet2[i].IsActive = false ;
                    Life1 = Life1 - 1 ;
                    if(Life1<1)
                    GameActive = false;

                    Tank1X = 300;
                    Tank1Y = 540;
                    angle1=M_PI_4;
                    degree1=0;
                }

                    circle(Bullet2[i].X_Pos, Bullet2[i].Y_Pos,2);

            }
        }

}
//Life Bar
void LifeBar()
{
    settextstyle(9,HORIZ_DIR,2);
    setcolor(BLACK);
    outtextxy(40,50,"LIVES");
    setfillstyle(SOLID_FILL, RED);

    if(Life1==3)
    {
        bar(200,50,210,70);
        bar(215,50,225,70);
        bar(230,50,240,70);
    }
    if(Life1==2)
    {
        bar(200,50,210,70);
        bar(215,50,225,70);
    }
    if(Life1==1)
    {
        bar(200,50,210,70);
    }

    setfillstyle(SOLID_FILL, GREEN);

    if(Life2==3)
    {
        bar(1260,50,1270,70);
        bar(1275,50,1285,70);
        bar(1290,50,1300,70);
    }
    if(Life2==2)
    {
        bar(1260,50,1270,70);
        bar(1275,50,1285,70);
    }
    if(Life2==1)
    {
        bar(1260,50,1270,70);
    }

}
