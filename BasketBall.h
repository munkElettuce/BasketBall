#ifndef BASKETBALL_H
#define BAASKETBALL_H

#include <Adafruit_SSD1306.h>
#include <math.h>
#include <Arduino.h>
#include <Background.h>
#define OLED_HEIGHT 64
#define OLED_WIDTH 128

/**
 * @brief this header file will define the behavior of the ball and its parabolic path 
 * ball center (x,y)=(2*radius,2*radius)
 * the parabola Y co ords peaks are y={48,56,64}
 * todo first we will throw the ball by hard coded co ords then we can bring in the input from switches
 * todo for next code session:aftercalling the drawPath once it should clear the previous path before drawing new one 
 * Basket center (x,y)=(116,48) basketRadius=8
 * ball path 1:y = -0.0097x^2 + 0.8022x + 7.9856 the correct path to  the basket
 */

class BasketBall: public Playground {
  /**
   * *centerX and centerY are the current center co ords for the ball
   * *ball paths is the array of parabol each element of the aarray has array of co eff of that particular parabola only one path will lead to basket ={{x^2,x^1,x^0},...}
   */
    private:
        Adafruit_SSD1306*  _display;
    public:
    unsigned int centerX,centerY,radius,orgCenterX,orgCenterY;
    double ballPaths[3][3]={{-0.0093610,1.5311,-3.6500},{-0.0063776,1.1735,-0.97959},{0,1,0}};

    void begin(Adafruit_SSD1306* display,unsigned int centerX=8,unsigned int centerY=8,unsigned int radius=4){
      this->_display=display;
        this->centerX=centerX;
        this->centerY=centerY;
        this->radius=radius;
        this->orgCenterX=centerX;
        this->orgCenterY=centerY;
        
    }
    
    void drawCircle(unsigned int xCoOrd,unsigned int yCoOrd,unsigned int radius){
            
          unsigned int centerX = xCoOrd;
          unsigned int centerY = yCoOrd;

          int x = radius - 1;
          int y = 0;
          int dx = 1;
          int dy = 1;
          int error = dx - (radius << 1);

          while (x >= y) {
            _display->drawPixel(centerX + x, centerY + y, WHITE);
            _display->drawPixel(centerX + y, centerY + x, WHITE);
            _display->drawPixel(centerX - y, centerY + x, WHITE);
            _display->drawPixel(centerX - x, centerY + y, WHITE);
            _display->drawPixel(centerX - x, centerY - y, WHITE);
            _display->drawPixel(centerX - y, centerY - x, WHITE);
            _display->drawPixel(centerX + y, centerY - x, WHITE);
            _display->drawPixel(centerX + x, centerY - y, WHITE);

            if (error <= 0) {
              y++;
              error += dy;
              dy += 2;
            }

            if (error > 0) {
              x--;
              dx += 2;
              error += dx - (radius << 1);
            }
          }

          
        }
        void drawFilledCircle() {
          for(int i=1;i<=this->radius;i++){
            drawCircle(this->centerX,this->centerY,i);
          }
        }
        unsigned int calculateCenterY(double* parabolaPath,unsigned int currentCenterX){
          /**
           * @brief 
           * *pass the parabola path and the next x co ord i.e. currentCenterX+1 to get the next CenterY along the parabolaPath
           */
          unsigned int y=round(parabolaPath[0]*currentCenterX*currentCenterX+parabolaPath[1]*currentCenterX+parabolaPath[2]);
          return y;
        }
        void drawPath(double* parabolaPath,unsigned int startX=8,unsigned int pathOffset=8,unsigned int endX=80){
          /**
           * will draw discreted parabola to select to shoot
           * only draw half width of the display
           */
          for(unsigned int i=startX;i<=endX;i+=pathOffset){
            _display->drawPixel(i,calculateCenterY(parabolaPath,i),WHITE);
          }

        }

        unsigned int moveBall(double* parabolaPath,unsigned int startX,unsigned int endX=108){
          
          while(this->centerX!=endX){
            _display->clearDisplay(); //after selecting a path display is cleared
            setupBackground(this->_display,this->radius);//clearing the display the background is set up
            
            this->centerX++;//update/increment the current centerX of the ball
            this->centerY=calculateCenterY(parabolaPath,this->centerX);//get the updated centerY along the chosen parabola path

            
            drawFilledCircle();
            _display->display();
          }
          return this->centerX;
        }
        
        
        bool shoot(unsigned int parabolaPathIndex,unsigned int destinationX){
          unsigned int ballX=moveBall(ballPaths[parabolaPathIndex],this->orgCenterX);

           
          
          _display->clearDisplay();//after throwing the ball revert back everything to its original position after a delay
          delay(3000);
          setupBackground(this->_display,this->radius);
          this->centerX=this->orgCenterX;
          this->centerY=this->orgCenterY;
          drawFilledCircle();
          _display->display();

          if(destinationX==ballX){
            return true;//ball has reached the basket
          }
          return false;
        }
};

#endif