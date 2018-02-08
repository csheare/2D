#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "DNA.h"
#include "math.h"
#include "shape.h"
#include <vector>

const float PI = 3.14159265359;


void Shape::setPentagon(int radius){

  float angle = 2* PI / 5;
  //clear out points vector
  points.clear();

  int x = 0;
  int y = 0;
  for(int i =0; i < 5; i++){
    x = center.x + radius*sin(i*angle);
    y = center.y + radius*cos(i*angle);
    SDL_Point p = {x,y};
    points.push_back(p);
  }

}
void Shape::setHexagon(int radius){
  float angle = 2* PI / 6;
  //clear out points vector
  points.clear();

  int x = 0;
  int y = 0;
  for(int i =0; i < 6; i++){
    x = center.x + radius*sin(i*angle);
    y = center.y + radius*cos(i*angle);
    SDL_Point p = {x,y};
    points.push_back(p);
  }
}

void Shape::drawRectangle(SDL_Renderer* renderer,SDL_Point center,int width, int height, SDL_Color color){
  SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
  SDL_Rect *rect = new SDL_Rect();
  rect->x= center.x;
  rect->y = center.y;
  rect->w = width;
  rect->h = height;
  SDL_RenderDrawRect(renderer,rect);
}


void Shape::drawCircle(SDL_Renderer*  renderer,SDL_Point center,int radius, SDL_Color color){
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
/****
* This function draws a shape based on points in vector it uses a rotation matrix to rotated
* the shape
****/
void Shape::drawDouble(SDL_Renderer * renderer,float rotation,Shape s2){
  if(points.empty()){
    std::cout << "No points specified\n" << std::endl;
    return;
  }
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  int xr1 = 0;//rotated x
  int yr1 = 0;//rotated y
  int xr2 = 0;//rotated x
  int yr2 = 0;//rotated y
  for(unsigned int i = 0; i < points.size()-1;i++){

    xr1 = (points.at(i).x - center.x)*cos(rotation) - (points.at(i).y - center.y)*sin(rotation) + center.x;
    yr1 =(points.at(i).x - center.x)*sin(rotation) + (points.at(i).y - center.y)*cos(rotation) + center.y;
    xr2 = (points.at(i+1).x - center.x)*cos(rotation) - (points.at(i+1).y - center.y)*sin(rotation) +  center.x;
    yr2 = (points.at(i+1).x - center.x)*sin(rotation) + (points.at(i+1).y - center.y)*cos(rotation) + center.y;

    SDL_RenderDrawLine(renderer,xr1,yr1,xr2,yr2);

    if(i == points.size()-2){
        xr1 = (points.at(0).x - center.x)*cos(rotation) - (points.at(0).y - center.y)*sin(rotation) + center.x;
        yr1 = (points.at(0).x - center.x)*sin(rotation) + (points.at(0).y - center.y)*cos(rotation) + center.y;
        SDL_RenderDrawLine(renderer,xr1,yr1,xr2,yr2);
    }

  }
  for(unsigned int i = 0; i < s2.points.size()-1;i++){

    xr1 = (s2.points.at(i).x - center.x)*cos(rotation) - (s2.points.at(i).y - center.y)*sin(rotation) + center.x;
    yr1 =(s2.points.at(i).x - center.x)*sin(rotation) + (s2.points.at(i).y - center.y)*cos(rotation) + center.y;
    xr2 = (s2.points.at(i+1).x - center.x)*cos(rotation) - (s2.points.at(i+1).y - center.y)*sin(rotation) +  center.x;
    yr2 = (s2.points.at(i+1).x - center.x)*sin(rotation) + (s2.points.at(i+1).y - center.y)*cos(rotation) + center.y;

    SDL_RenderDrawLine(renderer,xr1,yr1,xr2,yr2);

    if(i == s2.points.size()-2){
        xr1 = (s2.points.at(0).x - center.x)*cos(rotation) - (s2.points.at(0).y - center.y)*sin(rotation) + center.x;
        yr1 = (s2.points.at(0).x - center.x)*sin(rotation) + (s2.points.at(0).y - center.y)*cos(rotation) + center.y;
        SDL_RenderDrawLine(renderer,xr1,yr1,xr2,yr2);
    }

  }
}

void Shape::draw(SDL_Renderer * renderer,float rotation){
  if(points.empty()){
    std::cout << "No points specified\n" << std::endl;
    return;
  }
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  int xr1 = 0;//rotated x
  int yr1 = 0;//rotated y
  int xr2 = 0;//rotated x
  int yr2 = 0;//rotated y
  for(unsigned int i = 0; i < points.size()-1;i++){

    xr1 = (points.at(i).x - center.x)*cos(rotation) - (points.at(i).y - center.y)*sin(rotation) + center.x;
    yr1 =(points.at(i).x - center.x)*sin(rotation) + (points.at(i).y - center.y)*cos(rotation) + center.y;
    xr2 = (points.at(i+1).x - center.x)*cos(rotation) - (points.at(i+1).y - center.y)*sin(rotation) +  center.x;
    yr2 = (points.at(i+1).x - center.x)*sin(rotation) + (points.at(i+1).y - center.y)*cos(rotation) + center.y;

    SDL_RenderDrawLine(renderer,xr1,yr1,xr2,yr2);

    if(i == points.size()-2){
        xr1 = (points.at(0).x - center.x)*cos(rotation) - (points.at(0).y - center.y)*sin(rotation) + center.x;
        yr1 = (points.at(0).x - center.x)*sin(rotation) + (points.at(0).y - center.y)*cos(rotation) + center.y;
        SDL_RenderDrawLine(renderer,xr1,yr1,xr2,yr2);
    }
  }
}
  std::vector<SDL_Point> Shape::getPoints(){
    return points;
  }
  void Shape::addPoints(std::vector<SDL_Point> vec){

    points.insert(points.end(),vec.begin(),vec.end());

  }
  void Shape::rotatePoints(int rotation){
    std::vector<SDL_Point> rotVec;
    int xr1 = 0;//rotated x
    int yr1 = 0;//rotated y
    for(unsigned int i = 0; i < points.size();i++){
      xr1 = (points.at(i).x - center.x)*cos(rotation) - (points.at(i).y - center.y)*sin(rotation) + center.x;
      yr1 =(points.at(i).x - center.x)*sin(rotation) + (points.at(i).y - center.y)*cos(rotation) + center.y;
      SDL_Point point = {xr1,yr1};
        rotVec.push_back(point);
    }
    points = rotVec;
  }
  std::ostream& operator<<(std::ostream & out, const Shape& s){
    out <<  s.getX() << s.getY();
    return out;
  }
