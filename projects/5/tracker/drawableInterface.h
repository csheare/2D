#ifndef DRAWABLEINTERFACE__H
#define DRAWABLEINTERFACE__H


class DrawableInterface{
public:

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;

  virtual float getScale() const  = 0;
  virtual void  setScale(float s) = 0;
  virtual int getScaledWidth() const = 0;
  virtual int getScaledHeight() const = 0;
  virtual const SDL_Surface* getSurface() const = 0;

  virtual const std::string& getName() const = 0;
  virtual void setName(const std::string& n) = 0;

  virtual const Image* getImage() const = 0;

  virtual float getX() const  = 0;
  virtual void  setX(float x) = 0;

  virtual float getY() const  = 0;
  virtual void  setY(float y) = 0;

  virtual const Vector2f& getVelocity() const = 0;
  virtual void  setVelocity(const Vector2f& vel) = 0;
  virtual const Vector2f& getPosition() const   = 0;
  virtual void  setPosition(const Vector2f& pos) = 0;

  virtual float getVelocityX() const = 0;
  virtual void setVelocityX(float vx) = 0;
  virtual float getVelocityY() const  = 0;
  virtual void  setVelocityY(float vy) = 0;

  virtual int getWorldWidth() const = 0;
  virtual int getWorldHeight() const = 0;

};


#endif
