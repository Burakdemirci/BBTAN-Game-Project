/**********************************************/
/* Burak Demirci                              */
/* burakdemirci@gtu.edu.tr                    */
/* 141044091                                  */
/* Yaz Odevi                                  */
/**********************************************/

// Topun yansima kurali

#ifndef ReflectionRule_H
#define ReflectionRule_H
#include "Game.h"

typedef struct Reflect_t{

    float x;
    float y;

} Reflect_T;



Reflect_T *Reflect(int derece);
int ReflectionRectangle(float ballX,float ballY,rectangle_T *Rect, int k);
int ReflectionTriangle(float ballX,float ballY,triangle_T *triang,int k);
int ReflectionGameScreen(float ballX, float ballY);
int ReflectionRandBall(float ballX, float ballY, RandomBall_T *randball, int k);
int ReflectionVertical(float ballX ,float ballY , Vertical_T *dikey , int k);
int ReflectionHorizontal(float ballX, float ballY , Horizontal_T *yatay, int k);
int ReflectAddBall(float ballX, float ballY, AddBall_T *addball, int k);

#endif // ReflectionRule_H

