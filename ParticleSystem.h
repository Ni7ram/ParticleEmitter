/*
  Name: Martin Cardozo
  Copyright: 
  Author: Martin Cardozo 
  Date: 12/06/08 11:17
  Description: Sistema de Partículas
*/

/************************
      INCLUDES
************************/

#include "Particle.h"

#include <allegro.h>
#include <vector>

/************************
        CLASS
************************/

class ParticleSystem { 
        
public:
  
  //CONSTRUCTOR
  ParticleSystem (int maxParticlesC, int XC, int YC, int forceC, int amplitudeC, int minXC, int maxXC, int minYC, int maxYC, int elasticityC, int lifeTimeC, int sizeC);
  
  //FUNCTIONS
  void start();
  void stop();
  void kill();
  void changeColor();
  void draw();
  void changePointer(int Pointer);
  
  void incrementMaxParticles();
  void decrementMaxParticles();
  void incrementElasticity();
  void decrementElasticity();
  void incrementLifeTime();
  void decrementLifeTime();
  void incrementSize();
  void decrementSize();
  
  //GETTERS/SETTERS
  void setForce(int Value);
  void setAmplitude(int Value);
  void setElasticity(int Value);
  void setMaxParticles(int Value);
  void setLifeTime(int Value);
  void setNewLocation(int pointX, int pointY);
  void setBounds(int minX, int maxX, int minY, int maxY);
  
  //VARIABLES
  float force;
  float amplitude;  
  int minX;
  int maxX;
  int minY;
  int maxY;
  
  int orMinX;
  int orMaxX;
  int orMinY;
  int orMaxY;
  
private: 
  
  //FUNCTIONS
  void addParticle();
  void renewArray();
  
  //VARIABLES
  vector <Particle*> ArrayP; //MAIN ARRAY

  int pointer;
  int X;
  int Y;
  int color;
  int cantParticles;
  int maxParticles;
  int elasticity; //KEEP CONSTANT DURING TESTING
  int lifeTime;  
  int size;
  
  BITMAP* Buffer;
  BITMAP* chngParameters;
  BITMAP* BG;
};

/************************
      CONSTRUCTOR
************************/

ParticleSystem::ParticleSystem (int maxParticlesC, int XC, int YC, int forceC, int amplitudeC, int minXC, int maxXC, int minYC, int maxYC, int elasticityC, int lifeTimeC, int sizeC)
{                               
  maxParticles   = maxParticlesC;
  X              = XC;
  Y              = YC;
  force          = forceC;
  amplitude      = amplitudeC;
  orMinX         = minXC;
  orMaxX         = maxXC;
  orMinY         = minYC;
  orMaxY         = maxYC;
  minX           = minXC;
  maxX           = maxXC;
  minY           = minYC;
  maxY           = maxYC;
  elasticity     = elasticityC; 
  lifeTime       = lifeTimeC;
  size           = sizeC;
  color          = 0;
  pointer        = 1;

  Buffer         = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
  chngParameters = load_bitmap("chngParameters.bmp",0);
  BG             = load_bitmap("BG.bmp",0);
};

/************************
     PUBLIC METHODS
************************/

void ParticleSystem::start(){
     for (int i = 0; i<maxParticles; i++){
         addParticle();
     }
};

void ParticleSystem::kill(){
     maxParticles = 0;
};

void ParticleSystem::changeColor(){
     if (color<4){color++;}else{color = 0;}
};

void ParticleSystem::draw(){
     //set_trans_blender(0, 0, 0, 255); //TRANSPARENCY
     set_add_blender(0, 0, 0, 255);
     drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
     for (int i = 0; i<ArrayP.size(); i++){
         if (ArrayP[i]->move()){
             circlefill(Buffer, int(ArrayP[i]->X), int(ArrayP[i]->Y), size, makecol(ArrayP[i]->red, ArrayP[i]->green, ArrayP[i]->blue));
         }else{
             ArrayP.erase(ArrayP.begin()+i);
             cantParticles--;
         }
     }
     drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);

     renewArray();
     //GUI
     
     blit(BG, Buffer, 0, 0, 0, 0, minX, SCREEN_HEIGHT);     
     //blit(BG, Buffer, 0, 0, maxX, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
     //rectfill(Buffer, 0, 0, minX , SCREEN_HEIGHT, makecol(70,70,70));  
     rectfill(Buffer, maxX, 0, SCREEN_WIDTH , SCREEN_HEIGHT, makecol(70,70,70));   
     blit(BG, Buffer, 0, 0, 0, 0, SCREEN_WIDTH, 50);
     
     rect(Buffer, minX, minY, maxX-1, maxY-1, makecol(255,255,255));
     if (pointer == 1){
         masked_blit(chngParameters, Buffer, 0, 0, mouse_x-10, mouse_y-10, 20, 20);
     }else{
         circlefill(Buffer, mouse_x, mouse_y, 2, makecol(255,255,255));
     }
     textprintf_ex(Buffer, font, 10, 10, makecol(255,255,255), -1, "Particles: %i", ArrayP.size());
	 textprintf_ex(Buffer, font, 10, 20, makecol(255,255,255), -1, "Max Particles: %i", maxParticles);
	 textprintf_ex(Buffer, font, 10, 30, makecol(255,255,255), -1, "Life Time: %i", lifeTime);
	 //textprintf_ex(Buffer, font, minX + 10, 60, makecol(255,255,255), -1, "Force: %.2f", force);
	 //textprintf_ex(Buffer, font, minX + 10, 70, makecol(255,255,255), -1, "Amplitude: %.2f", amplitude);
     blit(Buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
     clear(Buffer);
};

void ParticleSystem::changePointer(int Pointer){
     pointer = Pointer;
};

void ParticleSystem::incrementMaxParticles(){
    for(int i=0; i<50; i++){
        maxParticles ++;
        addParticle();
    }
};

void ParticleSystem::decrementMaxParticles(){
     if (maxParticles>0) {maxParticles--;}
};

void ParticleSystem::incrementElasticity(){
     elasticity ++;
};

void ParticleSystem::decrementElasticity(){
     if (elasticity>1) {elasticity--;}
};

void ParticleSystem::incrementLifeTime(){
     lifeTime += 10;
};

void ParticleSystem::decrementLifeTime(){
     if (lifeTime>0){lifeTime -= 10;}
};

void ParticleSystem::incrementSize(){
     size++; 
}; 

void ParticleSystem::decrementSize(){
     if (size>1) size--;
};

/************************
     GETTERS/SETTERS
************************/

void ParticleSystem::setForce(int Value){
     if (Value<100 && Value>-100){force = Value/10;}
};

void ParticleSystem::setAmplitude(int Value){
     if (Value>0){
         amplitude = Value/10;
     }else{
         amplitude = 1;
     }
};

void ParticleSystem::setElasticity(int Value){
     elasticity = Value;
};

void ParticleSystem::setMaxParticles(int Value){
     maxParticles = Value;
};

void ParticleSystem::setLifeTime(int Value){
     lifeTime = Value;
};

void ParticleSystem::setNewLocation(int pointX, int pointY){
     X = pointX;
     Y = pointY;
};

void ParticleSystem::setBounds(int minXP, int maxXP, int minYP, int maxYP){
     if ((orMinX - minXP)>1 && (orMinX - minXP)<250){
         minX  = orMinX - minXP;
         maxX  = orMaxX + minXP; //original minx (malisimo)
     }
     minY  = orMinY;
     maxY  = orMaxY;
};

/************************
     PRIVATE METHODS
************************/

void ParticleSystem::addParticle(){
     int tmpColor = rand()%255;
     switch (color){
            case 0: //VIOLET           
                ArrayP.push_back(new Particle(X, Y, elasticity, minX, maxX, minY, maxY, lifeTime, amplitude, force, 175, tmpColor, 255));
                break;
            case 1: //GREEN
                ArrayP.push_back(new Particle(X, Y, elasticity, minX, maxX, minY, maxY, lifeTime, amplitude, force, tmpColor, 255, tmpColor));
                break;
            case 2: //BLUE
                ArrayP.push_back(new Particle(X, Y, elasticity, minX, maxX, minY, maxY, lifeTime, amplitude, force, tmpColor, tmpColor, 255));
                break;
            case 3: //RED
                ArrayP.push_back(new Particle(X, Y, elasticity, minX, maxX, minY, maxY, lifeTime, amplitude, force, 255, tmpColor, tmpColor));
                break;
            case 4: //WHITE
                ArrayP.push_back(new Particle(X, Y, elasticity, minX, maxX, minY, maxY, lifeTime, amplitude, force, tmpColor, tmpColor, tmpColor));
                break;
     }
     cantParticles++;
};

void ParticleSystem::renewArray(){
     if (cantParticles < maxParticles){
         int tmpInt = maxParticles - cantParticles;
         for (int i=0; i<tmpInt; i++){
             addParticle();
         }
     }
};
