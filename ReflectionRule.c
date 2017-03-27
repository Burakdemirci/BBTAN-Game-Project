/**********************************************/
/* Burak Demirci                              */
/* burakdemirci@gtu.edu.tr                    */
/* 141044091                                  */
/* Yaz Odevi                                  */
/**********************************************/

#include <stdio.h>
#include <math.h>
#include "ReflectionRule.h"
#include "Game.h"
#define PI 3.1415
float x,y;

Reflect_T *Reflect(int derece)
{
    Reflect_T *New;
    New=(Reflect_T*)malloc(sizeof(Reflect_T));
    float Radyan=derece*PI/180;
    New->x=(float)cos(Radyan);
    New->y=(float)sin(Radyan);
    return New;
}

int ReflectionGameScreen(float ballX, float ballY)
{

    if(ballX<=34+5 || ballX>=466-5)
    {
        return -1;
    }else if(ballY<=56+5)
    {
        return -2;
    }else if(ballY>=600-5)
    {
        return -5;
    }
    return 0;
}
int ReflectionRectangle(float ballX,float ballY,rectangle_T *Rect,int k)
{
    x=ballX;
    y=ballY;
    if(x>=Rect[k].x-6 && x<=Rect[k].x+56 && y>=Rect[k].y-6 && y<=Rect[k].y+56)
    {
        if(x>=Rect[k].x-6 && x<=Rect[k].x-4)
        {
            Rect[k].count--;
            return -1;
        }
        if(x<=Rect[k].x+56 && x>Rect[k].x+54)
        {
            Rect[k].count--;
            return -1;
        }

        if(y>=Rect[k].y-6 && y<=Rect[k].y-4)
        {
            Rect[k].count--;
            return-2;
        }
        if(y<=Rect[k].y+56 && y>Rect[k].y+54)
        {
            Rect[k].count--;
            return-2;
        }
    }
    else
    {
        return 0;
    }
}

int ReflectionTriangle(float ballX,float ballY,triangle_T *triang,int k)
{
    x=ballX;
    y=ballY;
    if(triang[k].type==3)
    {
        int c=50;
        float TempX=triang[k].x,TempY=triang[k].y;
        while(c!=0)
        {
             if(TempX<=x && TempX+1.5>=x && TempY<=y && TempY+1.5>=y )
             {
                 triang[k].count--;
                 return -3;
             }
            c--;
            TempX++;
            TempY++;
        }
        c=50;
        TempX=triang[k].x;
        TempY=triang[k].y;
        while(c!=0)
        {
            if( (x>=TempX-1 && x<TempX) && y<=TempY+51 && y>TempY)
            {
                if(x>=TempX && x<TempX+1)
                {
                    triang[k].count--;
                    return -1;
                }
                if(y<=TempY+50 && y>TempY+49)
                {
                    triang[k].count--;
                    return -2;
                }
            }
            TempX++;
            TempY++;
            c--;
        }
    }
    // Diger Ucgenlerin yansimasi
    //
    //
    //   BURAYA GELECEK
    //
    //
}

int ReflectionRandBall(float ballX, float ballY, RandomBall_T *randball, int k)
{
    int degre=0;
    Reflect_T *D;
    x=ballX;
    y=ballY;
    while(degre<360)
    {
        D=Reflect(degre);
        if(x<randball[k].x+13*D->x  && x>randball[k].x-13*D->x && y<randball[k].y-13*D->y && y>randball[k].x+13*D->y)
        {
            randball[k].check=-2;
            printf("CARPTI\n");
            return -7;
        }
        degre++;
    }
    return 0;
}

int  ReflectionVertical(float ballX ,float ballY , Vertical_T *dikey , int k)
{
    int degre=0;
    Reflect_T *D;
    x=ballX;
    y=ballY;
    while(degre<360)
    {
        D=Reflect(degre);
        if(x<dikey[k].x+13*D->x  && x>dikey[k].x-13*D->x && y<dikey[k].y-13*D->y && y>dikey[k].y+13*D->y)
        {
            dikey[k].check=-2;
            printf("CARPTI\n");
            al_draw_line(dikey[k].x-2,117,dikey[k].x+2,600,al_map_rgb(31,31,63),4);
            al_flip_display();
            return -8;
        }
        degre++;
    }
    return 0;
}

int ReflectionHorizontal(float ballX, float ballY , Horizontal_T *yatay, int k)
{
    int degre=0;
    Reflect_T *D;
    x=ballX;
    y=ballY;
    while(degre<360)
    {
        D=Reflect(degre);
        if(x<yatay[k].x+13*D->x  && x>yatay[k].x-13*D->x && y<yatay[k].y-13*D->y && y>yatay[k].y+13*D->y)
        {
            yatay[k].check=-2;
            printf("CARPTI\n");
            al_draw_line(34,yatay[k].y-2,466,yatay[k].y+2,al_map_rgb(31,31,63),4);
            al_flip_display();
            return -9;
        }
        degre++;
    }
    return 0;
}

int ReflectAddBall(float ballX, float ballY, AddBall_T *addball, int k)
{
    int degre=0;
    Reflect_T *D;
    x=ballX;
    y=ballY;
    while(degre<360)
    {
        D=Reflect(degre);
        if(x<=addball[k].x+13*D->x  && x>=addball[k].x-13*D->x && y<=addball[k].y-13*D->y && y>=addball[k].y+10*D->y)
        {
            addball[k].flag=-1;
            al_flip_display();
            return 1;
        }
        degre++;
    }
    return 0;
}
