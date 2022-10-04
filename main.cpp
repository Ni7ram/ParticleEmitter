/*
  Name: Martin Cardozo
  Copyright: 
  Author: Martin Cardozo 
  Date: 12/06/08 11:17
  Description: Clase usada para testear a la clase ParticleSystem.h
*/

/************************
 INCLUDES/GLOBAL STATICS
************************/
#include <allegro.h>

using namespace std;

#include "MathHelper.h"

//STATICS
MathHelper MathFunc;
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

#include "ParticleSystem.h"

/************************
    PRIVATE VARIABLES
************************/

//FUNCTIONS
void init();  
void deinit();
void checkInput();

//VARIABLES
ParticleSystem* Particulas;

int XInicial; 
int deltaX;
int YInicial;
int deltaY;
int difX;
int difY;

//KEY VARIABLES
bool CONTROL; 
bool MINUS;
bool PLUS;
bool Z;
bool X;
bool Q;
bool W;
bool S;

/************************
         TIMER
************************/

//volatile double elapsed_time = 0;
//void __inc_elapsed_time() { elapsed_time += .001; }
//END_OF_FUNCTION(__inc_elapsed_time);

/************************
      MAIN FUNCTION
************************/

int main() {
	init();
	
    Particulas = new ParticleSystem(0, 0, 0, 0, 0, 0, SCREEN_WIDTH, 50, SCREEN_HEIGHT, 5, 30, 1); 
    //maxParticles, X, Y, force, amplitude, minX, maxX, minY, maxY, elasticity, life, size
	Particulas->start();

    while (!key[KEY_ESC]) {
        checkInput();
		Particulas->draw();
	}

	deinit();
	return 0;
};
END_OF_MAIN()


/************************
    PRIVATE FUNCTIONS
************************/

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	install_timer();
	install_keyboard();
	install_mouse();
	
	//LOCK_VARIABLE(elapsed_time);
    //LOCK_FUNCTION(__inc_elapsed_time);
    //install_int_ex(__inc_elapsed_time, BPS_TO_TIMER(10)); 
};

void deinit() {
	clear_keybuf();
};

void checkInput(){ 
     //INCREMENTS/DECREMENTS
         if (key[KEY_PLUS_PAD] && !PLUS){Particulas->incrementLifeTime();}
         if (key[KEY_MINUS_PAD] && !MINUS){Particulas->decrementLifeTime();}
         if (key[KEY_Z] && !Z){Particulas->decrementElasticity(); Z = true;}
         if (key[KEY_X] && !X){Particulas->incrementElasticity(); X = true;}
         if (key[KEY_Q] && !Q){Particulas->decrementSize(); Q = true;}
         if (key[KEY_W] && !W){Particulas->incrementSize(); W = true;}
                       //- RELEASE KEY -//
         if (!key[KEY_PLUS_PAD]){PLUS = false;}
         if (!key[KEY_MINUS_PAD]){MINUS = false;}
         if (!key[KEY_Z]){Z = false;}
         if (!key[KEY_X]){X = false;}
         if (!key[KEY_Q]){Q = false;}
         if (!key[KEY_W]){W = false;}
     //KILL
         if (key[KEY_A]){Particulas->kill();}
     //COLOR
         if (key[KEY_S]){if (!S){Particulas->changeColor();S = true;}}
         if (!key[KEY_S]){S = false;}
     //RESIZE SCREEN/CHANGE PARAMETERS
         if (key[KEY_LCONTROL]){CONTROL = true;}
         if (!key[KEY_LCONTROL]){CONTROL = false;}
         if (mouse_b & 1){ //RIGHT CLICK
             Particulas->changePointer(0);
             Particulas->incrementMaxParticles();
             Particulas->setNewLocation(mouse_x, mouse_y);
         }
         if (mouse_b & 2){ //LEFT CLICK
            Particulas->changePointer(1);
            if (!XInicial) {XInicial = mouse_x;}
            if (!YInicial) {YInicial = mouse_y;}
            deltaX = (XInicial - mouse_x)+ difX;
            deltaY = (YInicial - mouse_y)+ difY;
            if (CONTROL){Particulas->setBounds(deltaX,deltaX,0,SCREEN_HEIGHT);}
            Particulas->setAmplitude(deltaX);
            Particulas->setForce(deltaY);       
         }
         if (!mouse_b & 1){
             Particulas->changePointer(0);
             Particulas->setNewLocation(mouse_x, mouse_y);
             difX     = deltaX;
             difY     = deltaY;
             XInicial = 0; 
             YInicial = 0;
         }
};
