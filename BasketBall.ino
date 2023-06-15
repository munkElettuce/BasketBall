
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include <BasketBall.h>
#include <Background.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define BB_RADIUS 4

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

int* temp;
unsigned int basketCenterX,basketCenterY,basketRadius;

void setup(){
  Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
  BasketBall ball;
  ball.begin(&display,2*BB_RADIUS,2*BB_RADIUS,BB_RADIUS);
  


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();


  Playground basketBallGround;
  temp=basketBallGround.setupBackground(BB_RADIUS,10,&display);
  
  
  ball.drawFilledCircle();
  ball.drawPath(ball.ballPaths[0]);
  display.display();
  Serial.begin(9600);
}

void loop(){
  
}