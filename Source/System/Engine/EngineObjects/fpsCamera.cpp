#include "System/Engine/EngineObjects/fpsCamera.h"

FpsCamera::FpsCamera(Input * input, Object * object) : Camera(object)
{
    this->input = input;
}

void FpsCamera::update() 
{
    //87 w
    //65 a
    //83 s
    //68 d
    Vec3<float> force;
    if (input->getKeyDown(87)) {
        force[2] -= 0.2f;
    } else if (input->getKeyDown(65)) {
        force[0] -= 0.2f;
    } else if (input->getKeyDown(68)) {
        force[0] += 0.2f;
    } else if (input->getKeyDown(83)) {
        force[2] += 0.2f;
    }
    Vec3<float> rotationSpeed;
    rotationSpeed[0] = (input->getDy()) * 0.5;
    rotationSpeed[1] = (input->getDx()) * 0.5;
    rotation += rotationSpeed;
    Matrix<float> other;
    matrix.setAxisrotation(rotation[0], X);
    other.setAxisrotation(rotation[1], Y);
    matrix = other.multiplyByMatrix(matrix);
    force = matrix.multiplyByVector(force);
    position += force;


}

Matrix<float> & FpsCamera::getMatrix()
{
    Matrix<float> other;
    matrix.setAxisrotation(-rotation[0], X);
    other.setAxisrotation(-rotation[1], Y);
    matrix = matrix.multiplyByMatrix(other);
    camera.translateMatrix(-position);
    camera = matrix.multiplyByMatrix(camera);
    return camera;
}

FpsCamera::~FpsCamera()
{

}

Vec3<float> & FpsCamera::getPos()
{
    return position;
}