#include "System/Graphics/Resources/buffer.h"

Buffer::Buffer(const std::string & name, unsigned int target)
{
  bufferName = name;
  glGenBuffers(1, &bufferId);
  this->target = target;
}

void Buffer::bufferData(unsigned int size, const GLvoid* data, unsigned int usage)
{
  glBindBuffer(target, bufferId);
  bufferSize = size;
  glBufferData(target, size, data, usage);
}

std::string Buffer::getName()
{
  return bufferName;
}

void Buffer::bufferSubData(unsigned int offset, unsigned int dataSize, const void* data)
{
  glBindBuffer(target, bufferId);
  glBufferSubData(target, offset, dataSize, data);
}

void Buffer::invalidateBuffer()
{
  glInvalidateBufferData(bufferId);
}

const unsigned int Buffer::getBufferId()
{
  return bufferId;
}

void Buffer::bindBuffer()
{
  glBindBuffer(target, bufferId);
}

Buffer::~Buffer()
{
 glDeleteBuffers(1, &bufferId);
}
