/*
  Name: Martin Cardozo
  Copyright:
  Author: Martin Cardozo
  Date: 12/06/08 11:17
  Description: Particula Genérica
*/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Particle {   

public:
       
  //CONSTRUCTOR
  Particle(int XC, int YC, int elasticityY, int minXC, int maxXC, int minYC, int maxYC, int lifeTimeC, float amplitudeC, float forceC, int redC, int greenC, int blueC);
  
  //FUNCTIONS      
  bool move();
  void checkBounds();
  bool checkLife();    
 
  //VARIABLES
  float X;
  float Y;
  
  int red;
  int green;
  int blue;
  
private:
  
  //FUNCTIONS
  float randAmplitude(float max);

  //VARIABLES
  int elasticity;
  int minX;
  int maxX;
  int minY;
  int maxY;
  int lifeTime;  
  float weight;
  float gravity;
  float amplitude;
  float force; 
};

/************************
      CONSTRUCTOR
************************/

Particle::Particle(int XC, int YC, int elasticityC, int minXC, int maxXC, int minYC, int maxYC, int lifeTimeC, float amplitudeC, float forceC, int redC, int greenC, int blueC)
{                       
  X          = XC;
  Y          = YC;
  elasticity = elasticityC;
  minX       = minXC;
  maxX       = maxXC;
  minY       = minYC;
  maxY       = maxYC;
  amplitude  = randAmplitude(amplitudeC)/5000;
  force      = float(forceC + MathFunc.randFloat(50)/5000);
  weight     = MathFunc.randFloat(1)/5000;
  force     += weight;
  lifeTime   = lifeTimeC;
  red        = redC;
  green      = greenC;
  blue       = blueC;
  gravity    = 0;
};

/************************
     PUBLIC METHODS
************************/

bool Particle::move(){
    if (!checkLife()){return false;}
    checkBounds();
    X += amplitude;
    Y -= force;
    //gravity += .3f;
    //Y += gravity;
};

void Particle::checkBounds(){
     if (Y < minY){force *= -1;}
              
     if (Y > maxY){
         force = elasticity--;
         gravity = 0;
     }
                   
     if (X < minX){amplitude *= -1;} 
              
     if (X > maxX){amplitude *= -1;}
};

bool Particle::checkLife(){
     if (!(lifeTime--) || !elasticity){return false;}
     return true;
};

/************************
     PRIVATE METHODS
************************/

float Particle::randAmplitude(float max){
    if (rand()%2){
        return -(MathFunc.randFloat(max));
    }else{
        return   MathFunc.randFloat(max);
    }
};
