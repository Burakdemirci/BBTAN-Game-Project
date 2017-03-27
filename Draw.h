/**********************************************/
/* Burak Demirci                              */
/* burakdemirci@gtu.edu.tr                    */
/* 141044091                                  */
/* Yaz Odevi                                  */
/**********************************************/

// Cizim icin kullanilacak fonksiyonlari icerir .
#include "ReflectionRule.h"
#ifndef Draw_H
#define Draw_H

void DrawGameScreen();
void DrawDortgen(int x,int y,int number,int color,int flag);
void DrawUcgen(int x,int y,int number,int ucgen, int color,int flag);
void Avatar(int x);
void DrawBall(float x , float y ,int flag );
void DrawRandomCircle(int x, int y,int flag);
void DrawVerticalCircle(int x, int y,int flag);
void DrawHorizantalCircle(int x, int y,int flag);
void DrawAddCircle(int x, int y,int flag);
void DrawArrow(float x, float y , int derece,int length);
void DrawTheGame(int avatarX,triangle_T *Ucgen, rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball);
#endif // Draw_H
