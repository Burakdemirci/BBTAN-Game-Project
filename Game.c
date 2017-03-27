/**********************************************/
/* Burak Demirci                              */
/* burakdemirci@gtu.edu.tr                    */
/* 141044091                                  */
/* Yaz Odevi                                  */
/**********************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Main.h"
#include "Game.h"
#include "Draw.h"
#include "ReflectionRule.h"

#define FPS 0.015
#define ScreenHeight 500
#define ScreenWeight 650
#define BallMax 200
#define y1  117
#define x1 39
#define x2 39+61
#define x3 39+61*2
#define x4 39+61*3
#define x5 39+61*4
#define x6 39+61*5
#define x7 39+61*6

int GameScreen()
{
    //Ekran olusturma
    ALLEGRO_DISPLAY* display;
    //Allegro Setup Hata Messaji
    if(!al_init())
    {
    	al_show_native_message_box(NULL,NULL,NULL,"Allegro Yuklenemedi!",NULL,NULL);
	}
    display = al_create_display(ScreenHeight,ScreenWeight);
    al_set_window_position(display,350,50);
    al_set_window_title(display,"BB-TAN GAME ");
    //AllegroEkran olusturulamadi hatasi
    if(!display)
	{
    	al_show_native_message_box(NULL,NULL,NULL,"Ekran olusturulamadi!",NULL,NULL);
	}

    al_init_primitives_addon();
    DrawGameScreen();
    al_flip_display();
    Game();
    //pointer silindi
    al_destroy_display(display);
    return 0;
}


int Game()
{
    int done=0,length=0;
    int MainCount=1,GameControl=-1;
    int derece=10;
    int ArrowCheck=1;
    int StartKey=0,AvatarKey=1;
    int avatarX,EndGame=0;
    int temiz=0,i=1,j,Dson=0,Uson=0;
    int GameCount=1,BallCount=1,OldBallCount=1,Num=0;
    float ballX,ballY=595;
    float arrowY=580;
    Reflect_T *New;
    //Oyunda kullanilacak icerikler icin array  islemi
    ball_T  ball[BallMax];
    rectangle_T  Dortgen[40];
    triangle_T  Ucgen[40];
    Vertical_T  Vertical[8];
    Horizontal_T Horizontal[8];
    AddBall_T addball[8];
    RandomBall_T ranball[8];
    gamecomp_T GC[1];
    GC[0].AdSon=0;
    GC[0].Dson=0;
    GC[0].DikSon=0;
    GC[0].RandSon=0;
    GC[0].Uson=0;
    GC[0].YatSon=0;
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER *timer=al_create_timer(FPS);
    ALLEGRO_EVENT_QUEUE *EventQueue=al_create_event_queue();
    al_register_event_source(EventQueue,al_get_keyboard_event_source());
    al_register_event_source(EventQueue,al_get_timer_event_source(timer));
    DrawGameScreen();
    while(!done)
    {
        if(EndGame==1)
        {
            display=al_create_display(0,0);
            al_show_native_message_box(display,"Message Box","GAME IS OVER",NULL,NULL,ALLEGRO_MESSAGEBOX_WARN);
            al_flip_display();
            done=1;
        }
        if(!temiz)
        { //Baslangicta butun degerlerin -1 atanarak hazir hale getirme islemi
            temiz=Temiz(Ucgen,Dortgen,Vertical,Horizontal,addball,ranball,ball);
            ball[0].flag=1;//Ilk topun kullanilabilmesi icin flag degeri 1 atanir
            ballX=(float)(Random(422)+39); //Random olarak ilk topun ve Avatarin yeri belirlenir
            avatarX=(int)ballX-20;
        }
        if(AvatarKey)
        {
            RandomComponent(GC,GameCount,Ucgen,Dortgen,Vertical,Horizontal,addball,ranball);
        }
        AvatarKey=0;
        ALLEGRO_EVENT event;
        al_wait_for_event(EventQueue,&event);
        DrawTheGame(avatarX,Ucgen,Dortgen,Vertical,Horizontal,addball,ranball);
        ArrowCheck=1;
        //Klavye
        if(event.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                if(length<=100)
                {
                    length+=5;
                }
                DrawArrow(ballX,arrowY,derece,length);
                break;
            case ALLEGRO_KEY_DOWN:
                if(length>=0)
                {
                   length-=5;
                }
                DrawArrow(ballX,arrowY,derece,length);
                break;
            case ALLEGRO_KEY_RIGHT:
                if(derece>=10)
                {
                    derece-=5;
                }
                DrawArrow(ballX,arrowY,derece,length);
                break;
            case ALLEGRO_KEY_LEFT:
                if(derece<=170)
                {
                    derece+=5;
                }
                DrawArrow(ballX,arrowY,derece,length);
                break;
            case ALLEGRO_KEY_ENTER:
                ArrowCheck=0;
                StartKey=1;
                break;
            case ALLEGRO_KEY_ESCAPE:
                display=al_create_display(0,0);
                done=al_show_native_message_box(display,"Message Box","Question","Are you really want to quit",NULL,ALLEGRO_MESSAGEBOX_QUESTION |ALLEGRO_MESSAGEBOX_YES_NO);
               // al_destroy_display(display);
                break;
            }
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        DrawTheGame(avatarX,Ucgen,Dortgen,Vertical,Horizontal,addball,ranball);

        if(ArrowCheck)
        {
            DrawArrow(ballX,arrowY,derece,length);
        }

        if(StartKey)
        {
            i=0;
            for(j=0; j<BallMax; j++)
            {
                ball[j].x=ballX;
                ball[j].y=ballY;
                ball[j].derece=derece;
            }
            j=0;
            while(StartKey==1)
            {
                 DrawTheGame(avatarX,Ucgen,Dortgen,Vertical,Horizontal,addball,ranball);
                 GameControl=BallMoving(avatarX,i,ball,Ucgen,Dortgen,Vertical,Horizontal,addball,ranball,Dson,Uson,OldBallCount);
                 if(GameControl==1)
                 {
                     //Top Sayisini artir
                    // BallCount++;
                 }
                 al_clear_to_color(al_map_rgb(0,0,0));
                 StartKey=CheckBall(ball,BallCount);
                 if(StartKey==-5)
                 {
                     PrepareNewGame(Ucgen,Dortgen,Vertical,Horizontal,addball,ranball,ball);
                 }
            }
            OldBallCount=BallCount;
            if(StartKey==-5)
            {
                i=0;
                while(i<40)
                {
                    if(Dortgen[i].flag==-1)
                    {
                        GC[0].Dson=i;
                        Dson=i;
                        i=150;
                    }
                    else
                    {
                        Dortgen[i].y+=61;
                        if(Dortgen[i].y>=500)
                        {
                            EndGame=1;
                        }
                    }
                    i++;
                }
                i=0;
                while(i<40)
                {
                    if(Ucgen[i].flag==-1)
                    {
                        GC[0].Uson=i;
                        Uson=i;
                        i=150;
                    }
                    else
                    {
                        Ucgen[i].y+=61;
                        if(Ucgen[i].y>=500)
                        {
                            EndGame=1;
                        }
                    }
                    i++;
                }
                i=0;
                while(i<8)
                {
                    if(Horizontal[i].flag==-1)
                    {
                        GC[0].YatSon=i;
                        i=150;
                    }
                    else
                    {
                        Horizontal[i].y+=61;
                    }
                    i++;
                }
                i=0;
                while(i<8)
                {
                    if(Vertical[i].flag==-1)
                    {
                       GC[0].DikSon=i;
                        i=150;
                    }
                    else
                    {
                        Vertical[i].y+=61;
                    }
                    i++;
                }
                i=0;
                while(i<8)
                {
                    if(ranball[i].flag==-1)
                    {
                        GC[0].RandSon=i;
                        i=150;
                    }
                    else
                    {
                        ranball[i].y+=61;
                    }
                    i++;
                }
                i=0;
                while(i<8)
                {
                    if(addball[i].flag==-1)
                    {
                        GC[0].AdSon=i;
                        i=150;
                    }
                    else
                    {
                        addball[i].y+=61;
                    }
                    i++;
                }
                i=0;
                while(i<BallCount)
                {
                    ball[i].flag=1;
                    i++;
                }
                GameCount++;
                AvatarKey=1;
                StartKey=0;
            }
      }
   }
   al_destroy_display(display);
   return 0;
}

int BallMoving(float avatarX,int i,ball_T *ball,triangle_T *Ucgen, rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball, int Dson,int Uson,int OldBallCount)
{
    int ReturnValue=0;
    int k=0;
    al_flip_display();//Topun hizli hareket etmesi icin bu fonksiyonu burada kullandim
    Reflect_T *New=Reflect(ball[i].derece);
    ball[i].x+=New->x;
    ball[i].y-=New->y;
    DrawBall(ball[i].x,ball[i].y,ball[i].flag);
    al_flip_display();
    ReturnValue=ReflectionGameScreen(ball[i].x,ball[i].y);
    switch(ReturnValue)
    {
        case -1:
            ball[i].derece=180-ball[i].derece;
            break;
        case -2:
            ball[i].derece=360-ball[i].derece;
            break;
        case -5:
            ball[i].flag=-1;
            return -5;
    }
    while(k<=Dson)
    {
        if(Dortgen[k].flag!=-1)
        {
            ReturnValue=ReflectionRectangle(ball[i].x,ball[i].y,Dortgen,k);
            switch(ReturnValue)
            {
                case -1:
                    ball[i].derece=180-ball[i].derece;
                    break;
                case -2:
                    ball[i].derece=360-ball[i].derece;
                    break;
            }
        }
        k++;
    }
    k=0;
    while(k<=Uson)
    {
        if(Ucgen[k].flag!=-1)
        {
            ReturnValue=ReflectionTriangle(ball[i].x,ball[i].y,Ucgen,k);
            switch(ReturnValue)
            {
                case -1:
                    ball[i].derece=180-ball[i].derece;
                    break;
                case -2:
                    ball[i].derece=360-ball[i].derece;
                    break;
                case -3:
                    if(ball[i].derece<=90 && ball[i].derece<=0)
                    {
                        ball[i].derece+=90;
                    }
                    if(ball[i].derece>90 && ball[i].derece<180)
                    {
                        ball[i].derece-=90;
                    }
                    if(ball[i].derece>=180 && ball[i].derece<=270)
                    {
                        ball[i].derece=360+270-ball[i].derece;
                    }
                    if(ball[i].derece>270 && ball[i].derece<=360)
                    {
                        ball[i].derece=360+270-ball[i].derece;
                    }
                    break;
            }
        }
        k++;
    }
    k=0;
    ReturnValue=0;
    while(k<8)
    {
        if(addball[k].flag!=-1)
        {
            ReturnValue=ReflectAddBall(ball[i].x,ball[i].y,addball,k);
            if(ReturnValue==1)
            {
                return 1;
            }
        }
        k++;
    }
    k=0;
    while(k<8)
    {
        if(ranball[k].flag!=-1)
        {
            ReflectionRandBall(ball[i].x,ball[i].y,ranball,k);
            ball[i].derece=rand()%360;
        }
        k++;
    }
    k=0;
    while(k<8)
    {
        if(yatay[k].flag!=-1)
        {
            ReflectionHorizontal(ball[i].x,ball[i].y,yatay,k);
            // Yatayda sayilarin azalmasini burada yapilacak
            //
            //                   1
        }
        k++;
    }
    k=0;
    while(k<8)
    {
        if(dikey[k].flag!=-1)
        {
            ReflectionVertical(ball[i].x,ball[i].y,dikey,k);
            // Dikeyde sayilarin azalmasini burada yapilacak
            //
            //
            //               2
        }
        k++;
    }
    al_flip_display();
}

void RandomComponent(gamecomp_T *GC,int GameCount,triangle_T *Ucgen,rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball)
{
    int flag[7]={0,0,0,0,0,0,0};
    int TotalComp=0,DortgenNum=0,UcgenNum=0,TempNum=-1,Save;
    int i,j,Num=0;
    TotalComp=Random(6)+1; //Ekrana ilk basta kac tane eleman konulacagini belirleme
    Save=TotalComp;
    while(TotalComp!=0)
    {
        TempNum=rand()%2;
        if(TempNum==1)
        {
            DortgenNum++;
        }
        else
        {
            UcgenNum++;
        }
        TotalComp--;
    }
    i=1;
    while(i<=7)
    {
        TempNum=rand()%7+1;
        switch(TempNum)
        {
         case 1:
             if(flag[0]==0)
             {
                flag[0]=i;
             }
             else
             {
               i--;
             } break;
         case 2:
            if(flag[1]==0)
            {
                flag[1]=i;
            }
            else
            {
                i--;
            } break;
         case 3:
            if(flag[2]==0)
            {
                flag[2]=i;
            }
            else
            {
                i--;
            } break;
         case 4:
            if(flag[3]==0)
            {
                flag[3]=i;
            }
            else
            {
                i--;
            } break;
         case 5:
            if(flag[4]==0)
            {
                flag[4]=i;
            }
            else
            {
                i--;
            } break;
        case 6:
           if(flag[5]==0)
           {
              flag[5]=i;
           }
           else
           {
                i--;
           } break;
        case 7:
            if(flag[6]==0)
            {
                flag[6]=i;
            }
            else
            {
                i--;
            } break;
        }
        i++;
        for(j=0; j<7; j++)
        {
            if(flag[j]!=0)
            {
                Num++;
            }
            else
            {
                Num--;
            }
        }
        if(Num==6)
        {
            i=40;
        }
    }// ilk while son
    i=0;
    Num=DortgenNum;
    while(DortgenNum!=0)
    {
        switch(flag[i])
        {
        case 1:
            Dortgen[GC[0].Dson].x=x1;
            Dortgen[GC[0].Dson].y=y1;
            Dortgen[GC[0].Dson].count=GameCount;
            Dortgen[GC[0].Dson].oldCount=GameCount;
            Dortgen[GC[0].Dson].flag=1;
            break;
        case 2:
            Dortgen[GC[0].Dson].x=x2;
            Dortgen[GC[0].Dson].y=y1;
            Dortgen[GC[0].Dson].count=GameCount;
            Dortgen[GC[0].Dson].oldCount=GameCount;
            Dortgen[GC[0].Dson].flag=1;
            break;
        case 3:
            Dortgen[GC[0].Dson].x=x3;
            Dortgen[GC[0].Dson].y=y1;
            Dortgen[GC[0].Dson].count=GameCount;
            Dortgen[GC[0].Dson].oldCount=GameCount;
            Dortgen[GC[0].Dson].flag=1;
            break;
        case 4:
            Dortgen[GC[0].Dson].x=x4;
            Dortgen[GC[0].Dson].y=y1;
            Dortgen[GC[0].Dson].count=GameCount;
            Dortgen[GC[0].Dson].oldCount=GameCount;
            Dortgen[GC[0].Dson].flag=1;
            break;
        case 5:
            Dortgen[GC[0].Dson].x=x5;
            Dortgen[GC[0].Dson].y=y1;
            Dortgen[GC[0].Dson].count=GameCount;
            Dortgen[GC[0].Dson].oldCount=GameCount;
            Dortgen[GC[0].Dson].flag=1;
            break;
        case 6:
            Dortgen[GC[0].Dson].x=x6;
            Dortgen[GC[0].Dson].y=y1;
            Dortgen[GC[0].Dson].count=GameCount;
            Dortgen[GC[0].Dson].oldCount=GameCount;
            Dortgen[GC[0].Dson].flag=1;
            break;
        case 7:
            Dortgen[GC[0].Dson].x=x7;
            Dortgen[GC[0].Dson].y=y1;
            Dortgen[GC[0].Dson].count=GameCount;
            Dortgen[GC[0].Dson].oldCount=GameCount;
            Dortgen[GC[0].Dson].flag=1;
            break;
        }
        GC[0].Dson++;
        i++;
        DortgenNum--;
    }
    i=Num;
    while(UcgenNum!=0)
    {
        switch(flag[i])
        {
        case 1:
            Ucgen[GC[0].Uson].x=x1;
            Ucgen[GC[0].Uson].y=y1;
            Ucgen[GC[0].Uson].count=GameCount;
            Ucgen[GC[0].Uson].oldCount=GameCount;
            Ucgen[GC[0].Uson].flag=1;
            break;
        case 2:
            Ucgen[GC[0].Uson].x=x2;
            Ucgen[GC[0].Uson].y=y1;
            Ucgen[GC[0].Uson].count=GameCount;
            Ucgen[GC[0].Uson].oldCount=GameCount;
            Ucgen[GC[0].Uson].flag=1;
            break;
        case 3:
            Ucgen[GC[0].Uson].x=x3;
            Ucgen[GC[0].Uson].y=y1;
            Ucgen[GC[0].Uson].count=GameCount;
            Ucgen[GC[0].Uson].oldCount=GameCount;
            Ucgen[GC[0].Uson].flag=1;
            break;
        case 4:
            Ucgen[GC[0].Uson].x=x4;
            Ucgen[GC[0].Uson].y=y1;
            Ucgen[GC[0].Uson].count=GameCount;
            Ucgen[GC[0].Uson].oldCount=GameCount;
            Ucgen[GC[0].Uson].flag=1;
            break;
        case 5:
            Ucgen[GC[0].Uson].x=x5;
            Ucgen[GC[0].Uson].y=y1;
            Ucgen[GC[0].Uson].count=GameCount;
            Ucgen[GC[0].Uson].oldCount=GameCount;
            Ucgen[GC[0].Uson].flag=1;
            break;
        case 6:
            Ucgen[GC[0].Uson].x=x6;
            Ucgen[GC[0].Uson].y=y1;
            Ucgen[GC[0].Uson].count=GameCount;
            Ucgen[GC[0].Uson].oldCount=GameCount;
            Ucgen[GC[0].Uson].flag=1;
            break;
        case 7:
            Ucgen[GC[0].Uson].x=x7;
            Ucgen[GC[0].Uson].y=y1;
            Ucgen[GC[0].Uson].count=GameCount;
            Ucgen[GC[0].Uson].oldCount=GameCount;
            Ucgen[GC[0].Uson].flag=1;
            break;
        }
        Ucgen[GC[0].Uson].type=rand()%4+1;
        GC[0].Uson++;
        i++;
        UcgenNum--;
    }
    switch(flag[6])
    {
    case 1:
        addball[GC[0].AdSon].x=x1+28;
        addball[GC[0].AdSon].y=y1+28;
        addball[GC[0].AdSon].flag=1;
        break;
    case 2:
        addball[GC[0].AdSon].x=x2+28;
        addball[GC[0].AdSon].y=y1+28;
        addball[GC[0].AdSon].flag=1;
        break;
    case 3:
        addball[GC[0].AdSon].x=x3+28;
        addball[GC[0].AdSon].y=y1+28;
        addball[GC[0].AdSon].flag=1;
        break;
    case 4:
        addball[GC[0].AdSon].x=x4+28;
        addball[GC[0].AdSon].y=y1+28;
        addball[GC[0].AdSon].flag=1;
        break;
    case 5:
        addball[GC[0].AdSon].x=x5+28;
        addball[GC[0].AdSon].y=y1+28;
        addball[GC[0].AdSon].flag=1;
        break;
    case 6:
        addball[GC[0].AdSon].x=x6+28;
        addball[GC[0].AdSon].y=y1+28;
        addball[GC[0].AdSon].flag=1;
        break;
    case 7:
        addball[GC[0].AdSon].x=x7+28;
        addball[GC[0].AdSon].y=y1+28;
        addball[GC[0].AdSon].flag=1;
        break;
    }
    if(Save<6)
    {
        TempNum=rand()%4;
        if(TempNum==1)
        {
            switch(flag[5])
            {
            case 1:
                ranball[GC[0].RandSon].x=x1+28;
                ranball[GC[0].RandSon].y=y1+28;
                ranball[GC[0].RandSon].flag=1;
                break;
            case 2:
                ranball[GC[0].RandSon].x=x2+28;
                ranball[GC[0].RandSon].y=y1+28;
                ranball[GC[0].RandSon].flag=1;
                break;
            case 3:
                ranball[GC[0].RandSon].x=x3+28;
                ranball[GC[0].RandSon].y=y1+28;
                ranball[GC[0].RandSon].flag=1;
                break;
            case 4:
                ranball[GC[0].RandSon].x=x4+28;
                ranball[GC[0].RandSon].y=y1+28;
                ranball[GC[0].RandSon].flag=1;
                break;
            case 5:
                ranball[GC[0].RandSon].x=x5+28;
                ranball[GC[0].RandSon].y=y1+28;
                ranball[GC[0].RandSon].flag=1;
                break;
            case 6:
                ranball[GC[0].RandSon].x=x6+28;
                ranball[GC[0].RandSon].y=y1+28;
                ranball[GC[0].RandSon].flag=1;
                break;
            case 7:
                ranball[GC[0].RandSon].x=x7+28;
                ranball[GC[0].RandSon].y=y1+28;
                ranball[GC[0].RandSon].flag=1;
                break;
            }//Switch Son::
        }//if Son::
        if(TempNum==2)
        {
            switch(flag[5])
            {
            case 1:
                yatay[GC[0].YatSon].x=x1+28;
                yatay[GC[0].YatSon].y=y1+28;
                yatay[GC[0].YatSon].flag=1;
                break;
            case 2:
                yatay[GC[0].YatSon].x=x2+28;
                yatay[GC[0].YatSon].y=y1+28;
                yatay[GC[0].YatSon].flag=1;
                break;
            case 3:
                yatay[GC[0].YatSon].x=x3+28;
                yatay[GC[0].YatSon].y=y1+28;
                yatay[GC[0].YatSon].flag=1;
                break;
            case 4:
                yatay[GC[0].YatSon].x=x4+28;
                yatay[GC[0].YatSon].y=y1+28;
                yatay[GC[0].YatSon].flag=1;
                break;
            case 5:
                yatay[GC[0].YatSon].x=x5+28;
                yatay[GC[0].YatSon].y=y1+28;
                yatay[GC[0].YatSon].flag=1;
                break;
            case 6:
                yatay[GC[0].YatSon].x=x6+28;
                yatay[GC[0].YatSon].y=y1+28;
                yatay[GC[0].YatSon].flag=1;
                break;
            case 7:
                yatay[GC[0].YatSon].x=x7+28;
                yatay[GC[0].YatSon].y=y1+28;
                yatay[GC[0].YatSon].flag=1;
                break;
            }//Switch Son::
        }// if Son::
        if(TempNum==3)
        {
            switch(flag[5])
            {
            case 1:
                dikey[GC[0].DikSon].x=x1+28;
                dikey[GC[0].DikSon].y=y1+28;
                dikey[GC[0].DikSon].flag=1;
                break;
            case 2:
                dikey[GC[0].DikSon].x=x2+28;
                dikey[GC[0].DikSon].y=y1+28;
                dikey[GC[0].DikSon].flag=1;
                break;
            case 3:
                dikey[GC[0].DikSon].x=x3+28;
                dikey[GC[0].DikSon].y=y1+28;
                dikey[GC[0].DikSon].flag=1;
                break;
            case 4:
                dikey[GC[0].DikSon].x=x4+28;
                dikey[GC[0].DikSon].y=y1+28;
                dikey[GC[0].DikSon].flag=1;
                break;
            case 5:
                dikey[GC[0].DikSon].x=x5+28;
                dikey[GC[0].DikSon].y=y1+28;
                dikey[GC[0].DikSon].flag=1;
                break;
            case 6:
                dikey[GC[0].DikSon].x=x6+28;
                dikey[GC[0].DikSon].y=y1+28;
                dikey[GC[0].DikSon].flag=1;
                break;
            case 7:
                dikey[GC[0].DikSon].x=x7+28;
                dikey[GC[0].DikSon].y=y1+28;
                dikey[GC[0].DikSon].flag=1;
                break;
            }//Switch Son::
        }// if Son ::
    }// Genel if Son

    return;
}

int CheckBall(ball_T *ball , int BallCount)
{
    int i=0;
    while(i<BallCount)
    {
        if(ball[i].flag!=-1)
        {
            return 1;
        }
        i++;
    }
    return -5;
}

//Bu fonksiyon baslangictan sonraki yeni etap icin düzenleme yapar
void PrepareNewGame(triangle_T *Ucgen,rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball, ball_T *ball)
{
    int i=0,k=150;
    while(i<40)
    {
        if(Ucgen[i].flag==-1)
        {
            k=i+1;
            while(k<40)
            {
                if(Ucgen[k].flag!=-1)
                {
                    Ucgen[i].count=Ucgen[k].count;
                    Ucgen[i].oldCount=Ucgen[k].oldCount;
                    Ucgen[i].type=Ucgen[k].type;
                    Ucgen[i].flag=Ucgen[k].flag;
                    Ucgen[i].x=Ucgen[k].x;
                    Ucgen[i].y=Ucgen[k].y;
                    k=150;
                }

                k++;
            }

        }

        if(k<40)
        {
            i=150;
        }
        i++;
    }

    i=0;
    k=150;

    while(i<40)
    {
        if(Dortgen[i].flag==-1)
        {
            k=i+1;
            while(k<40)
            {
                if(Dortgen[k].flag!=-1)
                {
                    Dortgen[i].count=Dortgen[k].count;
                    Dortgen[i].flag=Dortgen[k].flag;
                    Dortgen[i].oldCount=Dortgen[k].oldCount;
                    Dortgen[i].x=Dortgen[k].x;
                    Dortgen[i].y=Dortgen[k].y;
                    k=150;
                }
                k++;
            }
        }
        if(k<40)
        {
            i=150;
        }
        i++;
    }

    i=0;
    k=150;
    while(i<8)
    {
        if(yatay[i].check==-2)
        {
           yatay[i].flag=-1;
           yatay[i].check=-1;
        }
        if(yatay[i].flag==-1)
        {
            k=i+1;
            while(k<8)
            {
                if(yatay[k].flag!=-1)
                {
                    yatay[i].check=yatay[k].check;
                    yatay[i].flag=yatay[k].flag;
                    yatay[i].x=yatay[k].x;
                    yatay[i].y=yatay[k].y;
                    k=150;
                }
                k++;
            }
        }
        if(k<8)
        {
            i=150;
        }
        i++;
    }
    i=0;
    k=150;
    while(i<8)
    {
        if(dikey[i].check==-2)
        {
           dikey[i].flag=-1;
           dikey[i].check=-1;
        }
        if(dikey[i].flag==-1 || dikey[i].check==-1)
        {
            k=i+1;
            dikey[i].flag=-1;
            while(k<8)
            {
                if(dikey[k].flag!=-1)
                {
                    dikey[i].check=dikey[k].check;
                    dikey[i].flag=dikey[k].flag;
                    dikey[i].x=dikey[k].x;
                    dikey[i].y=dikey[k].y;
                    k=150;
                }
                k++;
            }
        }
        if(k<8)
        {
            i=150;
        }
        i++;
    }
    i=0;
    k=150;
    while(i<8)
    {
        if(ranball[i].check==-2)
        {
           ranball[i].flag=-1;
           ranball[i].check=-1;
        }
        if(ranball[i].flag==-1 || ranball[i].check==-1)
        {
            k=i+1;
            ranball[i].flag=-1;
            while(k<8)
            {
                if(ranball[k].flag!=-1)
                {
                    ranball[i].check=ranball[k].check;
                    ranball[i].flag=ranball[k].flag;
                    ranball[i].x=ranball[k].x;
                    ranball[i].y=ranball[k].y;
                    k=150;
                }
                k++;
            }
        }
        if(k<8)
        {
            i=150;
        }
        i++;
    }
    i=0;
    k=150;
    while(i<8)
    {
        if(addball[i].flag==-1)
        {
            k=i+1;
            while(k<8)
            {
                if(addball[k].flag!=-1)
                {
                    addball[i].flag=addball[k].flag;
                    addball[i].x=addball[k].x;
                    addball[i].y=addball[k].y;
                    k=150;
                }
                k++;
            }
        }
        if(k<8)
        {
            i=150;
        }
        i++;
    }
    return ;
}
//Baslangicta butun degerlerin -1 atanmasi
int Temiz(triangle_T *Ucgen,rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball, ball_T *ball)
{
    int temiz=0,load=0;
    while(!temiz)
    {
        Ucgen[load].flag=-1;
        Dortgen[load].flag=-1;
        if(load<8)
        {
            dikey[load].flag=-1;
            dikey[load].check=-1;
            yatay[load].flag=-1;
            yatay[load].check=-1;
            ranball[load].flag=-1;
            ranball[load].check=-1;
            addball[load].flag=-1;
        }
        load++;
        if(load>40)
        {
            temiz=1;
        }
    }
    load=1;
    while(load<=BallMax)
    {
        ball[load].flag=-1;
        load++;
    }
    return temiz;
}

void PongSong()
{
    al_install_audio();
    al_init_acodec_addon();

    //Muzik Baslangic
    al_reserve_samples(1);
    ALLEGRO_SAMPLE *song =al_load_sample("pong.wav");
    al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
   //Muzik Son
   return;
}
