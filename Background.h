

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <Adafruit_SSD1306.h>


#define OLED_HEIGHT 64
#define OLED_WIDTH 128


class Playground{
    private:
        Adafruit_SSD1306*  _display;
    public:
        // Playground(){
        //     _display=nullptr;
        // }
        void begin(Adafruit_SSD1306* display){
            _display=display;
        }
        
        int setupPole(unsigned int baseX,unsigned int baseY,unsigned int radius=4,unsigned int factor=8){
            //radius of the ball is passed as a parameter to keep the aspect ratios and for convinient
            //this function will draw the base of the pole and will return the y co ord of the tip of the pole where you can place your basket to your basket ball
            _display->drawLine(baseX,baseY,baseX,baseY+factor*radius+4,WHITE);
            return baseY+factor*radius;
        }
        
        void setBasketBar(unsigned int startX,unsigned int startY,unsigned int radius, unsigned int factor=3){
            int diameter=2*radius;
            unsigned int endX=startX-diameter;
            unsigned int endY=startY;
            _display->drawLine(startX,startY,endX,endY,WHITE);//base line (middle line is drawn)
            unsigned int up=endY;//up pointer will take care of drawin upper lines wrt base lines
            unsigned int down=endY;//down pointer is responsible for lower lines wrt base line
            //base line is drawn now factor -1 lines should be drawn

            for(int i=0;i<=factor/2;i++){
                up++;
                down--;
                _display->drawLine(startX,up,endX,up,WHITE);
                _display->drawLine(startX,down,endX,down,WHITE);
            }
        }

        void setBasketNet(unsigned int basketCenterX,unsigned int basketCenterY,unsigned int basketRadius){
            _display->drawLine(basketCenterX,basketCenterY,basketCenterX+basketRadius,basketCenterY,WHITE);
            //basePole is at (128-4,64-4)=>casket is at right most 
            unsigned int leftX=basketCenterX+(basketRadius-1);//ttrying to draw net from center to the left and right with offset leftX is nearer to 128 and rightX is kinda far away from OLED_WIDTTH
            unsigned int rightX=basketCenterX-(basketRadius-1);
            unsigned int commonY=basketCenterY;//commonYis used to adjust the y altitude and draw horizontal nets one for each loop so two horizontal lines for two loops
            
            //lets fraw the vertical nets
            for(int i=0;i<2;i++){
                
                _display->drawLine(leftX,basketCenterY,leftX,basketCenterY-basketCenterY/4,WHITE);
                _display->drawLine(rightX,basketCenterY,rightX,basketCenterY-basketCenterY/4,WHITE);
                leftX=rightX=basketCenterX;
                commonY=basketCenterY-(basketCenterY/4)/2;
            }

            //now onto the horizontal nets
            _display->drawLine(basketCenterX+basketRadius-1,commonY,basketCenterX-basketRadius+1,commonY,WHITE);
        }

        void setupBackground(Adafruit_SSD1306* display,unsigned int radius,unsigned int poleFactor=10){
          
          /**
           * todo : user has to call this function once to set the background
           * *poleX & poleY are the base co ords for the basketball pole
           * *poleFactor is a factor that determines height of the pole using radius of the ball height=factor*radius
           *  @param basketCenterY has the y co or for the basket to setup
           *  @param basketCenterX is the same as base of the pole but with an offset (4)
           */


          this->begin(display);
          unsigned int poleX,poleY,basketCenterX,basketCenterY,basketRadius;//base for basketball pole
          
          poleX=OLED_WIDTH-2*radius;//poleX=128-2*4=120

          poleY=2*radius;//poleY=8;

          basketCenterY=this->setupPole(poleX,poleY,radius,poleFactor);
          
          

          basketRadius=2*radius;
          poleX=OLED_WIDTH-2*radius-4;//-4 is the offset separates pole and basket
          basketCenterX=poleX-basketRadius;

          this->setBasketBar(poleX,basketCenterY,2*radius);
          this->setBasketNet(basketCenterX,basketCenterY,basketRadius);
          this->_display->display();
          
          Serial.println(basketCenterX);
          Serial.println(basketCenterY);
          Serial.println(basketRadius);
          
          
          // return std::make_tuple(basketCenterX,basketCenterY,basketRadius);
        }

};

#endif