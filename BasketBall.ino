
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Background.h>
#include <BasketBall.h>




#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define BB_RADIUS 4

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
BasketBall ball;
Playground basketBallGround;
void setup(){
 
  
  
  ball.begin(&display,2*BB_RADIUS,2*BB_RADIUS,BB_RADIUS);


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();


  
  
  display.drawLine(64,48,64,64,WHITE);
  
  
  // ball.drawPath(ball.ballPaths[0]);
  // ball.tempDo();
  for(int i=0;i<10;i++){

    display.clearDisplay();
    ball.drawFilledCircle();
    basketBallGround.setupBackground(&display,BB_RADIUS,10);
    ball.drawPath(ball.ballPaths[i%3]);
    
    display.display();
    delay(1000);
  }

  bool isThrown=ball.shoot(1,116);
  // display.display();
  Serial.begin(9600);
}

void loop(){
  
   
}