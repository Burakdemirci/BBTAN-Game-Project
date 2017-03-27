/**********************************************/
/* Burak Demirci                              */
/* burakdemirci@gtu.edu.tr                    */
/* 141044091                                  */
/* Yaz Odevi                                  */
/**********************************************/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "ReflectionRule.h"

void DrawGameScreen()
{
    ALLEGRO_COLOR red=al_map_rgb(235,14,44);
    al_draw_rectangle(34,56,466,600,red,1); //Ana cerceve
    //al_flip_display();
}
void DrawDortgen(int x,int y,int number,int color, int flag)
{
    if(flag==-1)
    {
        return;
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    //Renklerin Tanimlanmasi
    ALLEGRO_COLOR  yellow=al_map_rgb(243,249,87);
    ALLEGRO_COLOR  red=al_map_rgb(235,14,44);
    ALLEGRO_COLOR  orange=al_map_rgb(216,164,8);
    ALLEGRO_COLOR  blue=al_map_rgb(50,9,234);
    ALLEGRO_COLOR  ten=al_map_rgb(255,212,170);
    ALLEGRO_COLOR  lightYellow=al_map_rgb(255,255,178);
    ALLEGRO_COLOR  renk;

    //Hata masaji
    if(color<1 || color>6)
    {
        printf("Draw.c Dortgen > Renk kodu hatasi\n");
    }

    //Renk secim islemi
    switch(color)
    {
    case 1:
        renk=red; break;
    case 2:
        renk=orange; break;
    case 3:
        renk=ten; break;
    case 4:
        renk=yellow; break;
    case 5:
        renk=lightYellow; break;
    case 6:
        renk=blue; break;
    }

    ALLEGRO_FONT *font=al_load_font("orbitron-black.ttf",12,NULL);
	al_draw_textf(font,renk,x+23,y+20,ALLEGRO_ALIGN_CENTER,"%d",number);
    al_draw_rectangle(x,y,x+50,y+50,renk,3);
	//al_flip_display();
    al_destroy_font(font);
	color=0;
	return ;
}

void DrawUcgen(int x,int y,int number,int ucgen, int color, int flag)
{
    if(flag==-1)
    {
        return;
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font=al_load_font("orbitron-black.ttf",12,NULL);

    //Renklerin tanimlanmasi
    ALLEGRO_COLOR  yellow=al_map_rgb(243,249,87);
    ALLEGRO_COLOR  red=al_map_rgb(235,14,44);
    ALLEGRO_COLOR  orange=al_map_rgb(216,164,8);
    ALLEGRO_COLOR  blue=al_map_rgb(50,9,234);
    ALLEGRO_COLOR  ten=al_map_rgb(255,212,170);
    ALLEGRO_COLOR  lightYellow=al_map_rgb(255,255,178);
    ALLEGRO_COLOR  renk;
    //::::::::::::::::::::::::::::::::::::::::

    //Hata mesajlari
    if(color<1 || color>6)
    {
        printf("Draw.c Ucgen > Renk kodu hatasi\n");
    }
    if(ucgen<1 || ucgen>4)
    {
        printf("Draw.c Ucgen > Ucgen kodu hatasi\n");
    }

    // Ucgen ve yazinin renklerinin belirlenmesi
    switch(color)
    {
    case 1:
        renk=red; break;
    case 2:
        renk=orange; break;
    case 3:
        renk=ten; break;
    case 4:
        renk=yellow; break;
    case 5:
        renk=lightYellow; break;
    case 6:
        renk=blue; break;
    }

    //Ucgen Secimi
    switch(ucgen)
    {
        case 1:
            al_draw_textf(font,renk,x+15,y+5,ALLEGRO_ALIGN_CENTER,"%d",number);
            al_draw_triangle(x,y,x+50,y,x,y+50,renk,3);
            break;
        case 2:
            al_draw_textf(font,renk,x+30,y+5,ALLEGRO_ALIGN_CENTER,"%d",number);
            al_draw_triangle(x,y,x+50,y,x+50,y+50,renk,3);
            break;
        case 3:
            al_draw_textf(font,renk,x+15,y+34,ALLEGRO_ALIGN_CENTER,"%d",number);
            al_draw_triangle(x,y,x,y+50,x+50,y+50,renk,3);
            break;
        case 4:
            al_draw_textf(font,renk,x+33,y+35,ALLEGRO_ALIGN_CENTER,"%d",number);
            al_draw_triangle(x+50,y,x+50,y+50,x,y+50,renk,3);
            break;
    }

    color=0;
    ucgen=0;
	//al_flip_display();
	al_destroy_font(font);
	return ;
}

void Avatar(int x)
{
    //Eklentiler..
    al_init_primitives_addon();
    al_init_image_addon();

    // Icon ve yazinin tasarlanmasi
    ALLEGRO_BITMAP *avatar=al_load_bitmap("avatar.png");

    al_draw_bitmap(avatar,x,568,NULL);
    //Pointerler silindi
    al_destroy_bitmap(avatar);
}


void DrawAddCircle(int x, int y,int flag)
{
    if(flag==-1)
    {
        return;
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_COLOR  yellow=al_map_rgb(243,249,87);
    ALLEGRO_FONT *font=al_load_font("pong.ttf",30,NULL);
    al_draw_circle(x,y,10,yellow,2);
    al_draw_text(font,yellow,x,y-14,ALLEGRO_ALIGN_CENTER,"+");
   // al_flip_display();
    al_destroy_font(font);
}

void DrawHorizantalCircle(int x, int y,int flag)
{
    if(flag==-1)
    {
        return;
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_COLOR blue=al_map_rgb(81,208,239);
    ALLEGRO_FONT *font=al_load_font("orbitron-black.ttf",12,NULL);
    al_draw_circle(x,y,10,blue,2);
    al_draw_text(font,blue,x,y-5,ALLEGRO_ALIGN_CENTER,"- -");
   // al_flip_display();
    al_destroy_font(font);
}

void DrawVerticalCircle(int x, int y,int flag)
{
    if(flag==-1)
    {
        return;
    }
    al_init_primitives_addon();
    ALLEGRO_COLOR cyan=al_map_rgb(78,229,179);
    al_draw_circle(x,y,10,cyan,2);
    al_draw_line(x,y+2,x,y+8,cyan,2);
    al_draw_line(x,y,x,y-7,cyan,2);

   // al_flip_display();
}

void DrawRandomCircle(int x, int y,int flag)
{
    if(flag==-1)
    {
        return;
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_COLOR darkPink=al_map_rgb(237,40,112);
    ALLEGRO_FONT *font=al_load_font("orbitron-black.ttf",23,NULL);
    al_draw_circle(x,y,10,darkPink,2);
    al_draw_text(font,darkPink,x,y-6,ALLEGRO_ALIGN_CENTER,"*");
   // al_flip_display();
    al_destroy_font(font);
}

void DrawBall(float x , float y ,int flag )
{
    if(flag==-1)
    {
        return;
    }
    al_init_primitives_addon();
    ALLEGRO_COLOR white =al_map_rgb(255,255,255);
    al_draw_filled_circle(x,y,5,white);
}

void DrawArrow(float x, float y , int derece ,int length)
{
    int count=200+length;
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_COLOR white=al_map_rgb(255,255,255);
    ALLEGRO_COLOR  orange=al_map_rgb(216,164,8);
    ALLEGRO_FONT *font=al_load_font("orbitron-bold.ttf",20,NULL);
    Reflect_T *Arrow=(Reflect_T *)malloc(sizeof(Reflect_T));
    Arrow=Reflect(derece);
    x-=2;
    while(count!=0)
    {
        x+=Arrow->x;
        y-=Arrow->y;
        if(x<30 || x>460)
        {
           Arrow=Reflect(derece=180-derece);
        }
        al_draw_text(font,white,x,y,NULL,".");
        al_flip_display();
        count--;
    }

    al_destroy_font(font);
}

void DrawTheGame(int avatarX,triangle_T *Ucgen, rectangle_T *Dortgen,Vertical_T *dikey,Horizontal_T *yatay, AddBall_T *addball,RandomBall_T *ranball)
{
    int i=0;
    DrawGameScreen();
    Avatar(avatarX);
    while(i<40)
    {
        if(Dortgen[i].count<=0)
        {
            Dortgen[i].flag=-1;
        }
        if(Ucgen[i].count<=0)
        {
            Ucgen[i].flag=-1;
        }
        DrawDortgen(Dortgen[i].x,Dortgen[i].y,Dortgen[i].count,1,Dortgen[i].flag);
        DrawUcgen(Ucgen[i].x,Ucgen[i].y,Ucgen[i].count,Ucgen[i].type,1,Ucgen[i].flag);
        if(i<8)
        {
            DrawVerticalCircle(dikey[i].x,dikey[i].y,dikey[i].flag);
            DrawHorizantalCircle(yatay[i].x,yatay[i].y,yatay[i].flag);
            DrawAddCircle(addball[i].x,addball[i].y,addball[i].flag);
            DrawRandomCircle(ranball[i].x,ranball[i].y,ranball[i].flag);
        }
        i++;
    }
    al_flip_display();
    return;
}

