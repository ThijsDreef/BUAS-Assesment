#ifndef WINDOW__
#define WINDOW__
#include <thread>
#include <iostream>
#include <vector>
#include <System/Window/glew.h>
#include <System/Window/wglew.h>
#include <Windows.h>
#include <WindowsX.h>
#include "System/Input/input.h"

class Window
{
private:
  int updateMouse = 0;
  Input input;
  HINSTANCE hInstance;
  bool fullscreen = false;
  HGLRC hRC = NULL;
  HDC hDC = NULL;
  HWND hWnd =NULL;
  int width = 0;
  int height = 0;
  bool createWindow(const char* title, int width, int height, int bits, bool fullscreen);
public:
  bool done = false;
  bool initGL();
  Window (const char* title, int width, int height, int bits, bool fullscreen);
  void resize(unsigned int width, unsigned int height);
  void handleMessages();
  void vsync(bool vsync);
  void updateFrameBuffer();
  void updateInput();
  void killWindow();
  virtual ~Window ();
  Input * getInput();
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK realWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
#endif
