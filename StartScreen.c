/**********************************************/
/* Burak Demirci                              */
/* burakdemirci@gtu.edu.tr                    */
/* 141044091                                  */
/* Yaz Odevi                                  */
/**********************************************/

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define ScreenHeight 500
#define ScreenWeight 650

void StartScreen()
{
	//Ekran olusturma
    ALLEGRO_DISPLAY* display;

    int x=331,y=366,MoveSpeed=3;
    int check=1,MenuCheck=0;

    //Allegro Setup Hata Messaji
    if(!al_init())
    {
    	al_show_native_message_box(NULL,NULL,NULL,"Allegro yuklenemedi! ",NULL,NULL);
	}

    display = al_create_display(ScreenHeight,ScreenWeight);
    al_set_window_position(display,350,50);
    al_set_window_title(display,"BB-TAN GAME ");

    //Allegro Ekran olusturulamadi hatasi
    if(!display)
	{
    	al_show_native_message_box(NULL,NULL,NULL,"Ekran olusturulamadi! ",NULL,NULL);
	}

    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();

    //Muzik Baslangic
    al_reserve_samples(1);
    ALLEGRO_SAMPLE *song =al_load_sample("intro.wav");
    al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    //Muzik Son

    MenuCheck=menu();
    al_destroy_sample(song);
    //pointer silindi
     al_destroy_display(display);
    //............

    //Menu Secimine gore yonlendirme
    switch(MenuCheck)
    {
        case 1:
            GameScreen();
            break;
        case -1:
            break;
    }
}

int menu()
{
    int x=1;
    int check=1;
    int ReturnValue=0;
    int a=285,b=387;

    //Eklentiler
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();

    //Menu yazisinin tasarlanasi
    ALLEGRO_COLOR  white =al_map_rgb(255,255,255);
    ALLEGRO_COLOR yellow=al_map_rgb(243,249,87);

    ALLEGRO_FONT *font=al_load_font("Pong.ttf",32,NULL);
    ALLEGRO_FONT *fontC=al_load_font("Pong.ttf",42,NULL);
    //...........

    ALLEGRO_EVENT_QUEUE *Event_Queue=al_create_event_queue();
    al_register_event_source(Event_Queue,al_get_keyboard_event_source());
    StartIcon();
    al_draw_text(fontC,yellow,295,370,0,"START GAME");
    al_draw_text(font,white,295,420,0,"QUIT GAME");
    al_draw_filled_circle(a,b,5,white);
    al_flip_display();

    // Menu secme dongusu
    while(check)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(Event_Queue,&event);
        if(x==1)
        {
            //Harekti gostermek icin ekran siyaha boyanıyor
            al_clear_to_color(al_map_rgb(0,0,0));
            //Yeni ekran olusturuldu
            StartIcon();
            //Menu yazilari
            al_draw_text(fontC,yellow,295,370,0,"START GAME");
            al_draw_text(font,white,295,420,0,"QUIT GAME");
            al_draw_filled_circle(a,b,5,white);
            al_flip_display();
        }

        if(x==2)
        {
             al_clear_to_color(al_map_rgb(0,0,0));
             StartIcon();
             al_draw_text(font,white,295,370,0,"START GAME");
             al_draw_text(fontC,yellow,295,420,0,"QUIT GAME");
             al_draw_filled_circle(a,b+53,5,white);
             al_flip_display();
        }

        if(event.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN:
                    if(x<2)
                    {
                        x++;
                    } break;

                case ALLEGRO_KEY_UP:
                    if(x>1)
                    {
                        x--;
                    } break;
                case ALLEGRO_KEY_ESCAPE:
                    check=0;
                    ReturnValue=-1;
                    break;
                case ALLEGRO_KEY_ENTER:
                     switch(x)
                     {
                        case 1:
                            check=0;
                            ReturnValue=1;
                            break;
                        case 2:
                            check=0;
                            ReturnValue=-1;
                            break;
                     }
            }
        }
    }
    //...........................................
    //Pointer silindi ve Gerekli deger donduruldu
    al_destroy_event_queue(Event_Queue);
    al_destroy_font(fontC);
    al_destroy_font(font);

    return ReturnValue;
}


void StartIcon()
{
    //Eklentiler..
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    //RENK TANIMLAMALARI
    ALLEGRO_COLOR red=al_map_rgb(235,14,44);
    ALLEGRO_COLOR yellow=al_map_rgb(243,249,87);
    ALLEGRO_COLOR white =al_map_rgb(255,255,255);
    //........

    // Icon ve yazinin tasarlanmasi
    ALLEGRO_BITMAP *icon1=al_load_bitmap("icon1.png");

	ALLEGRO_FONT *font1,*font2;
	font1 = al_load_font("orbitron-black.ttf",42,NULL);
	font2 = al_load_font("orbitron-bold.ttf",15,NULL);

	al_draw_text(font1,yellow,250,170,ALLEGRO_ALIGN_CENTER,"BB-TAN & GTU");
	al_draw_text(font2,red,70,215,ALLEGRO_ALIGN_LEFT,"BURAK");

    al_draw_line(70 ,162,400,162,red,3.0);
    al_draw_line(403,163,410,163,yellow,5.0);
    al_draw_line(418,163,425,163,yellow,5.0);
    al_draw_line(140,220,430,220,red,2.0);
    al_draw_bitmap(icon1,90,298,NULL);
    //.............

    //Tasarlanan Yaziyi ve resimleri gosterir
    al_flip_display();

    //Pointerler silindi
    al_destroy_bitmap(icon1);
    al_destroy_font(font1);
    al_destroy_font(font2);
}


