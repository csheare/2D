#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "DNA.h"
#include "math.h"
#include "shape.h"
const float PI = 3.14159;

DNA::DNA(SDL_Renderer* r): renderer(r){};

void DNA::drawPurine(SDL_Point center,int radius,SDL_Color color,int rotation){
  Shape p(center,color);
  p.setHexagon(radius);

  SDL_Point pentShift = {(int)(center.x+ radius ),(int)(center.y-1.3*radius)};
  Shape p2(pentShift,color);
  p2.setPentagon(radius-5);
  p2.rotatePoints(PI/3);
  p.drawDouble(renderer,rotation,p2);

}

void DNA::drawPyrimidine(SDL_Point center,int radius,SDL_Color color,int rotation){
  Shape p(center,color);
  p.setPentagon(radius);
  p.draw(renderer,rotation);
}

void DNA::drawCytosine(SDL_Point center,int radius,SDL_Color color,int rotation){
  drawPyrimidine(center,radius,color,rotation);
}
void DNA::drawThymine(SDL_Point center,int radius,SDL_Color color,int rotation){
  drawPyrimidine(center,radius,color,rotation);
}
void DNA::drawGuanine(SDL_Point center,int radius,SDL_Color color,int rotation){
  drawPurine(center,radius,color,rotation);
}
void DNA::drawAdenine(SDL_Point center,int radius,SDL_Color color,int rotation){
  drawPurine(center,radius,color,rotation);
}

void DNA::drawBackbone(SDL_Point center, int radius,float startAngle, float endAngle, SDL_Color bcolor,SDL_Color cyt,SDL_Color ad,SDL_Color thy,SDL_Color guan){//angles in in radians
    SDL_SetRenderDrawColor(renderer, bcolor.r, bcolor.g, bcolor.b, bcolor.a);

    startAngle = startAngle * PI /180;//convert to radians
    endAngle = endAngle* PI /180;//convert to radians

    //check
    if(startAngle > endAngle){
      endAngle += 2* PI ;
    }

    //calc mid point
    float midAngle = (startAngle + endAngle)/2;

    //inital x and y
    int xi = radius * cos(startAngle);
    int yi = radius * sin(startAngle);

    //get base of comparison by subtracting the startAngle from the midpoint angle
    float base = fabs(midAngle - startAngle);
    int count = 0;

    for(float theta = startAngle;theta<endAngle; theta+=.0001){//maybe .01
        float scalarProp = (fabs(midAngle-theta)/base)*.01 + .99;

        int dx1 = scalarProp * radius * cos(theta) - xi ;
        int dy1 = scalarProp * radius * sin(theta) - yi;

        SDL_SetRenderDrawColor(renderer, bcolor.r, bcolor.g, bcolor.b, bcolor.a);//red
        SDL_RenderDrawPoint(renderer, center.x + dx1 +radius, center.y - dy1 +radius);
        SDL_RenderDrawPoint(renderer, center.x - dx1 +radius, center.y + dy1 + radius);

        int dx2 = (scalarProp * radius * cos(PI/2 +theta) - xi);
        int dy2 = (scalarProp * radius * sin(PI/2 + theta) - yi);


        SDL_RenderDrawPoint(renderer, center.x + dx2 +2*radius, center.y + dy2);
        SDL_RenderDrawPoint(renderer, center.x - dx2, center.y - dy2 + 2*radius);

        if(count%1000 == 0.0){

          int x1 = center.x + dx1 +radius;
          int y1 = center.y - dy1 +radius;
          int x2 = center.x + dx2 +2*radius;
          int y2 = center.y + dy2;

          int x3 = center.x - dx1 +radius;
          int y3 = center.y + dy1 + radius;
          int x4 = center.x - dx2;
          int y4 = center.y - dy2 + 2*radius;

          //Adenine
          SDL_SetRenderDrawColor(renderer, ad.r, ad.g, ad.b, ad.a);
          SDL_RenderDrawLine(renderer,x1,y1,(x1+x2)/2,(y1+y2)/2);

          //Thymine
          SDL_SetRenderDrawColor(renderer, thy.r, thy.g, thy.b, thy.a);
          SDL_RenderDrawLine(renderer,(x1+x2)/2,(y1+y2)/2,x2,y2);

          //Cytosine
          SDL_SetRenderDrawColor(renderer, cyt.r, cyt.g, cyt.b, cyt.a);
          SDL_RenderDrawLine(renderer,x3,y3,(x3+x4)/2,(y3+y4)/2);

          //Guanine
          SDL_SetRenderDrawColor(renderer, guan.r, guan.g, guan.b, guan.a);
          SDL_RenderDrawLine(renderer,(x3+x4)/2,(y3+y4)/2,x4,y4);

          count = 0;
        }
        count++;
    }
}
