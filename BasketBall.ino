#include <BasketBall.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define BB_RADIUS 4

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


unsigned int basketCenterX,basketCenterY,basketRadius;

void setup(){
  Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  Playground basketBall;
  basketBall.begin(&display);
  basketBall.drawFilledCircle(2*BB_RADIUS,2*BB_RADIUS,BB_RADIUS);
  unsigned int basketY=basketBall.setupPole(OLED_WIDTH-2*BB_RADIUS,2*BB_RADIUS,BB_RADIUS,10);  
  //basketY is the Y co ordinate of basket
  unsigned int basketX=OLED_WIDTH-(2*BB_RADIUS+4);//offset is set to 4 to separate basket from pole
  //basketX is the X co ordinate of Basket
  basketBall.drawThickLineY(basketX,basketY,2*BB_RADIUS,3);

  basketRadius=2*BB_RADIUS;
  basketCenterX=basketX-basketRadius;
  basketCenterY=basketY;
  basketBall.setBasket(basketCenterX,basketCenterY,basketRadius);
  
  display.display();
  // display.drawLine(2,2,12,12,WHITE);
}

void loop(){
}