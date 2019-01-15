rmdir build /s /q
mkdir build
robocopy source build /e /xf * >nul
