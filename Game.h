/**********************************************/
/* Burak Demirci                              */
/* burakdemirci@gtu.edu.tr                    */
/* 141044091                                  */
/* Yaz Odevi                                  */
/**********************************************/


#ifndef Game_H
#define Game_H
//#include "ReflectionRule.h"

typedef struct Vertical_t
{
    int flag;
    float x,y;
    int check;
}Vertical_T;

typedef struct Horizontal_t
{
    int flag;
    float x,y;
    int check;
}Horizontal_T;

typedef struct RandomBall_t
{
    int flag;
    float x,y;
    int check;
}RandomBall_T;

typedef struct AddBall_t
{
    int flag;
    float x,y;
}AddBall_T;

typedef struct ball_t{
    int flag;
    float x,y;
    int derece;
}ball_T;
typedef struct triangle_t{
    int flag;
    float x,y;
    int count;
    int type;
    int oldCount;
}triangle_T;

typedef struct rectangle_t{
    int flag;
    float x,y;
    int count;
    int oldCount;
}rectangle_T;

typedef struct gamecomp_t{

    int
    Dson,
    Uson,
    AdSon,
    YatSon,
    DikSon,
    RandSon;
}gamecomp_T;

int GameScreen();
void PongSong();
int CheckBall(ball_T *ball , int BallCount);
int Temiz(triangle_T *Ucgen,rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball, ball_T *ball);
int BallMoving(float avatarX,int i ,ball_T *ball,triangle_T *Ucgen, rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball, int Dson,int Uson,int OldBallCount);
void PrepareNewGame(triangle_T *Ucgen,rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball, ball_T *ball);
#endif // Game_H
