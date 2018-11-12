#include "System/Window/window.h"

Window::Window(const char* title, int width, int height, int bits, bool fullscreen)
{
  createWindow(title, width, height, bits, fullscreen);
}

Window::~Window()
{
  killWindow();
}

void Window::vsync(bool vsync)
{
  wglSwapIntervalEXT(vsync);
}

void Window::updateInput()
{
  if (input.getMouseLock())
  {
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);
    input.setLockCoords((int)(windowRect.left + windowRect.right) / 2, (int)(windowRect.top + windowRect.bottom) / 2);
    SetCursorPos(input.getLockX(), input.getLockY());
    input.resetDelta();
    ShowCursor(false);
  }
  else
    ShowCursor(true);
}
void Window::updateFrameBuffer()
{
  SwapBuffers(hDC);
}

bool Window::initGL()
{
  // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glShadeModel(GL_SMOOTH);
  glClearColor(0, 0.0f, 0, 1.0f);
  glClearDepth(1.0f);
  glDepthMask(GL_TRUE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);

  glDepthFunc(GL_LEQUAL);
  glCullFace(GL_BACK);
  return true;
}

bool Window::createWindow(const char* title, int width, int height, int bits, bool fullscreen)
{
  this->width = width;
  this->height = height;
  unsigned int PixelFormat;
  WNDCLASS wc;
  DWORD dwExStyle;
  DWORD dwStyle;

  RECT WindowRect;
  WindowRect.left = (long)0;
  WindowRect.right = (long)width;
  WindowRect.top = (long)0;
  WindowRect.bottom = (long)height;

  this->fullscreen = fullscreen;

  hInstance = GetModuleHandle(NULL);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = Window::WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "opengl";

  if (!RegisterClass(&wc))
  {
    MessageBoxA(NULL, "failed to register window class", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  if (fullscreen)
  {
    DEVMODEA dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth = width;
    dmScreenSettings.dmPelsHeight = height;
    dmScreenSettings.dmBitsPerPel = bits;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    if (ChangeDisplaySettingsA(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
      if (MessageBoxA(NULL, "the requested fullscreen mode is not supported by \n your video card. use windowed mode instead?", "opengl application", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
      {
        fullscreen = FALSE;
      }
      else
      {
        MessageBoxA(NULL, "the application will now close", "opengl application", MB_OK | MB_ICONSTOP);
        return FALSE;
      }
    }
  }
  if (fullscreen)
  {
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle = WS_POPUP;
  }
  else
  {
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle = WS_OVERLAPPEDWINDOW;
  }
  AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
  if (!(hWnd = CreateWindowExA(dwExStyle, "opengl", title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, NULL, NULL, hInstance, NULL)))
  {
    killWindow();
    MessageBoxA(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  SetPropA(hWnd, "opengl", this);
  static PIXELFORMATDESCRIPTOR pfd =
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,						//version number
    PFD_DRAW_TO_WINDOW |	//format must support window
    PFD_SUPPORT_OPENGL |	//format must support opengl
    PFD_DOUBLEBUFFER,		//must support dubble buffering
    PFD_TYPE_RGBA,			// request an rgba format
    (unsigned char)bits,					//select color depth
    0, 0, 0, 0, 0, 0,       //color bits ignored
    0,						//no alpha  buffer
    0,						//shift bit ignored
    0,						//no accumulation buffer
    0, 0, 0, 0,				//accumulation bits ignored
    32,						//32bit Z-Buffer (depth Buffer)
    0,						//no stencil buffer
    0,						//no Auxilliary buffer
    PFD_MAIN_PLANE,         //main drawing layer
    0,						//reserved
    0, 0, 0					//layer masks ignored
  };
  if (!(hDC = GetDC(hWnd)))
  {
    killWindow();
    MessageBoxA(NULL, "cant create a GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
  {
    killWindow();
    MessageBoxA(NULL, "cant find a suitable pixel format", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  if (!SetPixelFormat(hDC, PixelFormat, &pfd))
  {
    killWindow();
    MessageBoxA(NULL, "cant set the pixelformat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  if (!(hRC = wglCreateContext(hDC)))
  {
    killWindow();
    MessageBoxA(NULL, "cant create a GL rendering context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  if (!wglMakeCurrent(hDC, hRC))
  {
    killWindow();
    MessageBoxA(NULL, "can't activate the gl rendering context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  ShowWindow(hWnd, SW_SHOW);
  SetForegroundWindow(hWnd);
  SetFocus(hWnd);
  resize(width, height);
  glewInit();
  //now force a higher opengl context
  //now glew is init we can craete a higher context
  //if it is supported we butcher context and create a higher one
  if (WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
  {
    int iContextAttribs[] =
    {
       WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
       WGL_CONTEXT_MINOR_VERSION_ARB, 3,
       WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
       0 // End of attributes list
    };
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    hRC = wglCreateContextAttribsARB(hDC, 0, iContextAttribs);
    wglMakeCurrent(hDC, hRC);
  }
  if (!initGL())
  {
    killWindow();
    MessageBoxA(NULL, "initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
  // WindowHandler();
  return true;
}

void Window::resize(unsigned int width, unsigned int height)
{
  this->width = width;
  this->height = height;
  glViewport(0, 0, width, height);
}

void Window::handleMessages()
{
  MSG msg;
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

void Window::killWindow()
{
  done = true;
  if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}
	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBoxA(NULL, "Release of DC and RC failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))
		{
			MessageBoxA(NULL, "release Rendering Context failed.", "SHUTDOWN ERROR", MB_OK);
		}
		hRC = NULL;
	}
	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBoxA(NULL, "release device context failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}
	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBoxA(NULL, "destroying window failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}
	if (!UnregisterClassA("opengl", hInstance))
	{
		MessageBoxA(NULL, "error unregistering class", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  Window* pThis = static_cast<Window*>(GetPropA(hWnd, "opengl"));
  if (pThis)
    return pThis->realWndProc(hWnd, uMsg, wParam, lParam);
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Input * Window::getInput()
{
  return &input;
}
LRESULT CALLBACK Window::realWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
    case WM_CLOSE: 
    {
      done = true;
      return 0;
    }
    case WM_SIZE:
    {
      resize(LOWORD(lParam), HIWORD(lParam));
      return 0;
    }
    case WM_SIZING:
    {
      resize(LOWORD(lParam), HIWORD(lParam));
      return 0;
    }
    case WM_KEYDOWN:
    {
      input.setKey(wParam, true);
      return 0;
    }
    case WM_KEYUP: 
    {
      input.setKey(wParam, false);
      return 0;
    }
    case WM_MOUSEMOVE:
    {
      POINT pt;
      pt.x = GET_X_LPARAM(lParam);
      pt.y = GET_Y_LPARAM(lParam);
      ScreenToClient(hWnd, &pt);
      input.setMousePosition(pt.x, pt.y);
      return 0;
    }
    case WM_MOUSEWHEEL:
    {
      input.addMouseWheelDelta(GET_WHEEL_DELTA_WPARAM(wParam));
      return 0;
    }
    case WM_LBUTTONDOWN:
    {
      input.setMouseButton(0, true);
      return 0;
    }
    case WM_LBUTTONUP:
    {
      input.setMouseButton(0, false);
      return 0;
    }
    case WM_MBUTTONDOWN:
    {
      input.setMouseButton(1, true);      
      return 0;
    }
    case WM_MBUTTONUP:
    {
      input.setMouseButton(1, false);
      return 0;
    }
    case WM_RBUTTONDOWN:
    {
      input.setMouseButton(2, true);      
      return 0;
    }
    case WM_RBUTTONUP:
    {
      input.setMouseButton(2, false);      
      return 0;
    }
    default: 
    {
      break;
    }
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
