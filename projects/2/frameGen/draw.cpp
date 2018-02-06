#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "draw.h"
#include "math.h"

const float PI = 3.14159;

Draw::Draw(SDL_Renderer* r): renderer(r){};

void Draw::drawCircle(
  SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void Draw::drawRect(SDL_Point center, int width, int height, SDL_Color color){
  SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
  SDL_Rect *rect = new SDL_Rect();
  rect->x= center.x;
  rect->y = center.y;
  rect->w = width;
  rect->h = height;
  SDL_RenderDrawRect(renderer,rect);
  //do i need to free rect?
}
void Draw::drawHexagon(SDL_Point tip,int width,int height,SDL_Color color){
      drawRect(tip,width/2,height,color);

      SDL_SetRenderDrawColor(renderer,255,255,255,0);
      SDL_RenderDrawLine(renderer,tip.x+(width/2)-1,tip.y-1, tip.x+(width/2)-1,tip.y+height-1);
      SDL_RenderDrawLine(renderer,tip.x,tip.y, tip.x,tip.y+height);

      //right triangle
      SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
      SDL_RenderDrawLine(renderer,tip.x+(width/2)-2,tip.y, tip.x+(width),tip.y+(height/2));
      SDL_RenderDrawLine(renderer,tip.x+(width),tip.y+(height/2),tip.x+(width/2)-2,tip.y+height);
      //left triangle
      SDL_RenderDrawLine(renderer,tip.x,tip.y, tip.x-(width/2),tip.y+(height/2));
      SDL_RenderDrawLine(renderer,tip.x-(width/2),tip.y+(height/2),tip.x,tip.y+height);
}

void Draw::drawPurine(SDL_Point tip,int width,int height,SDL_Color color){
      drawHexagon(tip,width,height,color);
      SDL_Point p1 ={(int)(tip.x+(width/2)-2),(int)(tip.y+height)};
      SDL_Point p2 ={(int)(tip.x+(width))-10,(int)(tip.y+1.25*height)+10};
      SDL_Point p3 ={(int)(tip.x+(width/2)-2)+10,(int)(tip.y+1.75*height)+10};
      SDL_Point p4 ={(int)(tip.x)-5,(int)(tip.y+1.75*height)+10};
      SDL_Point p5 ={(int)tip.x,(int)(tip.y+height)};
      SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
      SDL_RenderDrawLine(renderer,p1.x,p1.y,p2.x,p2.y);
      SDL_RenderDrawLine(renderer,p2.x,p2.y,p3.x,p3.y);
      SDL_RenderDrawLine(renderer,p3.x,p3.y,p4.x,p4.y);
      SDL_RenderDrawLine(renderer,p4.x,p4.y,p5.x,p5.y);
}

void Draw::drawPyrimidine(SDL_Point center,int width,int height,SDL_Color color){
    drawHexagon(center,width,height,color);
}

void Draw::drawCytosine(SDL_Point tip,int width,int height,SDL_Color color){
  drawPurine(tip,width,height,color);
}
void Draw::drawThymine(SDL_Point tip,int width,int height,SDL_Color color){
  drawPurine(tip,width,height,color);
}
void Draw::drawGuanine(SDL_Point tip,int width,int height,SDL_Color color){
  drawPyrimidine(tip,width,height,color);
}
void Draw::drawAdenine(SDL_Point tip,int width,int height,SDL_Color color){
  drawPyrimidine(tip,width,height,color);
}



void Draw::drawDNA(SDL_Point center, int radius,float startAngle, float endAngle, SDL_Color bcolor,SDL_Color cyt,SDL_Color ad,SDL_Color thy,SDL_Color guan){//angles in in radians
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
        //std::cout <<"1) X is: "<< dx << ", Y is: " << dy<< std::endl;

        SDL_SetRenderDrawColor(renderer, bcolor.r, bcolor.g, bcolor.b, bcolor.a);//red
        SDL_RenderDrawPoint(renderer, center.x + dx1 +radius, center.y - dy1 +radius);
        SDL_RenderDrawPoint(renderer, center.x - dx1 +radius, center.y + dy1 + radius);

        int dx2 = (scalarProp * radius * cos(PI/2 +theta) - xi);
        int dy2 = (scalarProp * radius * sin(PI/2 + theta) - yi);
        //std::cout <<"2) X is: "<< dx << ", Y is: " << dy<< std::endl;

        SDL_RenderDrawPoint(renderer, center.x + dx2 +2*radius, center.y + dy2);
        SDL_RenderDrawPoint(renderer, center.x - dx2, center.y - dy2 + 2*radius);

        if( count%1000 == 0.0){

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
