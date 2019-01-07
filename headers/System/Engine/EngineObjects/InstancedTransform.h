#ifndef INSTANCEDTRANSFORM__
#define INSTANCEDTRANSFORM__
#include "System/Engine/EngineObjects/component.h"
#include "System/Engine/EngineObjects/transform.h"
#include "System/Graphics/Resources/buffer.h"



class InstancedTransform : public Component
{
protected:
    std::vector<Transform*> instances;
    Buffer matrixBuffer;
    
    std::vector<Matrix<float>> bufferData;
public:
    std::string & getModel();
    InstancedTransform(Object * object);
    virtual ~InstancedTransform();
    std::string getMaterial(unsigned int group);
    void addToInstance(Transform * t);
    virtual void prepareBuffer(Matrix<float> & view, Matrix<float> & p);
    unsigned int getBufferId();
    unsigned int getTransformSize();
};

#endif