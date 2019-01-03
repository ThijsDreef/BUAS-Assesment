#ifndef INPUT__
#define INPUT__
#include <iostream>
#include <string>
#include <vector>


class Input
{
private:
  int delta = 0;
  bool keys[256];
  bool mouse[3];
  float dx, dy;
  int x, y;
  int lockX;
  int lockY;
  int screenX, screenY;
  bool lockMouse = false;
public:
  Input ();
  int getMouseWheelDelta();
  bool getMouseLock();
  void addMouseWheelDelta(int d);
  void setLockCoords(int lx, int ly);
  void setMouseLock(bool lock);
  void setMouseButton(int button, bool down);
  void setKey(int keyCode, bool down);
  void setMousePosition(int ix, int iy);
  bool getKeyDown(int keyCode);
  bool getMouseButtonDown(int buttonCode);
  void setScreenSize(int width, int height);
  float getDx();
  float getDy();
  float getNx();
  float getNy();
  void resetDelta();
  int getLockX();
  int getLockY();
  int getMouseX();
  int getMouseY();
  virtual ~Input ();
};
#endif
