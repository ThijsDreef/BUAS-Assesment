#include "System/Engine/EngineObjects/InstancedTransform.h"

InstancedTransform::InstancedTransform(Object * object) : Component(object), matrixBuffer("matrices", GL_ARRAY_BUFFER)
{

}

InstancedTransform::~InstancedTransform() 
{
    	
}

void InstancedTransform::addToInstance(Transform * t) 
{
    t->shouldRender = false;
    instances.push_back(t);
    bufferData.push_back(Matrix<float>());
}

void InstancedTransform::prepareBuffer(Matrix<float> & view, Matrix<float> & p) 
{
    for (unsigned int i = 0; i < instances.size(); i++) 
    {
        if (instances[i]->isDead()) {
            instances[i]->setRemoved();
            instances.erase(instances.begin() + i);
        }
        // MatrixBufferObject o = instances[i]->getBuffer(view, p);
        bufferData[i] = instances[i]->getModelMatrix();
    }
    matrixBuffer.bufferData(sizeof(Matrix<float>) * bufferData.size(), &bufferData[0], GL_STATIC_DRAW);
}

std::string & InstancedTransform::getModel() 
{
    return instances[0]->model;
}

unsigned int InstancedTransform::getBufferId() 
{
    return matrixBuffer.getBufferId();
}

unsigned int InstancedTransform::getTransformSize() 
{
    return instances.size();
}

std::string InstancedTransform::getMaterial(unsigned int idGroup)
{
    return instances[0]->materials[idGroup];
}