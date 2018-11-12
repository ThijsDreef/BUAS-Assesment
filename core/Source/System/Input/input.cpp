#include "System/Input/input.h"

Input::Input()
{
  for (unsigned int i = 0; i < 256; i++)
    keys[i] = false;
  for (unsigned int i = 0; i < 2; i++)
    mouse[i] = false;
}

Input::~Input()
{

}

int Input::getMouseWheelDelta()
{
  return delta;
}

void Input::resetDelta()
{
  dx *= 0.6;
  dy *= 0.6;
  delta = 0;
}

float Input::getDx()
{
  return dx;
}

float Input::getDy()
{
  return dy;
}

bool Input::getMouseLock()
{
  return lockMouse;
}

void Input::setLockCoords(int lx, int ly)
{
  lockX = lx;
  lockY = ly;
}

int Input::getLockX()
{
  return lockX;
}

int Input::getLockY()
{
  return lockY;
}

void Input::setMouseLock(bool lock)
{
  lockMouse = lock;
}

bool Input::getKeyDown(int keyCode)
{
  return keys[keyCode];
}

bool Input::getMouseButtonDown(int buttonCode)
{
  return mouse[buttonCode];
}

int Input::getMouseX()
{
  return x;
}

int Input::getMouseY()
{
  return y;
}

void Input::setMousePosition(int ix, int iy)
{
  dx += (lockX - x) * 0.1;
  dy += (lockY - y) * 0.1;
  dx = (dx > 10) ? 10 : (dx < -10) ? -10 : dx;
  dy = (dy > 10) ? 10 : (dy < -10) ? -10 : dy;
  x = ix;
  y = iy;
}

void Input::setKey(int keyCode, bool down)
{
  keys[keyCode] = down;
}

void Input::addMouseWheelDelta(int d)
{
  delta += d;
}

void Input::setMouseButton(int button, bool down)
{
  mouse[button] = down;
}