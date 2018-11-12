#ifndef FPSCAMERA__
#define FPSCAMERA__
#include "System/Engine/EngineObjects/camera.h"
#include "System/Input/input.h"
class FpsCamera : public Camera {
private:
    Input * input;
    Matrix<float> matrix;
    Vec3<float> position;
    Vec3<float> rotation;
public:
    void update();
    Vec3<float> & getPos();
    Matrix<float> & getMatrix();
    FpsCamera(Input * input, Object * object);
    virtual ~FpsCamera();
};

#endif