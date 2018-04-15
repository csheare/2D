#ifndef DRAWABLEINTERFACE__H
#define DRAWABLEINTERFACE__H


class DrawableInterface{
public:

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;
  
};


#endif
