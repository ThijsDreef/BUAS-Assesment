#ifndef VEC3__
#define VEC3__
#include <cmath>

template<class T>
struct Vec3
{
private:
  T components[3];
public:
  Vec3 (T x, T y, T z)
  {
    components[0] = x;
    components[1] = y;
    components[2] = z;
  }
  Vec3 ()
  {
    for (int i = 0; i < 3; i ++)
      components[i] = 0;
  };
  T& operator[] (int i)
  {
    return components[i];
  }
  Vec3<T> operator*(Vec3<T> other)
  {
    Vec3<T> vec3;
    for (int i = 0; i < 3; i++)
      vec3[i] = components[i] * other[i];
    return vec3;
  }
  Vec3<T> operator+(Vec3<T> other)
  {
    Vec3<T> vec3;
    for (int i = 0; i < 3; i++)
      vec3[i] = components[i] + other[i];
    return vec3;
  }
  Vec3<T> operator-(Vec3<T> other)
  {
    Vec3<T> vec3;
    for (int i = 0; i < 3; i++)
      vec3[i] = components[i] - other[i];
    return vec3;
  }
  Vec3<T> operator/(Vec3<T> other)
  {
    Vec3<T> vec3;
    for (int i = 0; i < 3; i++)
      vec3[i] = components[i] / other[i];
    return vec3;
  }
  void operator +=(Vec3<T> other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] += other[i];
  }
  void operator -=(Vec3<T> other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] -= other[i];
  }
  void operator /=(Vec3<T> other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] /= other[i];
  }
  void operator *=(Vec3<T> other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] *= other[i];
  }
  Vec3<T> operator-()
  {
    Vec3<T> other;
    for (unsigned int i = 0; i < 3; i++)
      other[i] = -components[i];
    return other;
  }
  Vec3<T> operator* (T other)
  {
    Vec3<T> vec3;
    for (unsigned int i = 0; i < 3; i++)
      vec3[i] = components[i] * other;
    return vec3;
  }
  Vec3<T> operator- (T other)
  {
    Vec3<T> vec3;
    for (unsigned int i = 0; i < 3; i++)
      vec3[i] = components[i] - other;
    return vec3;
  }
  Vec3<T> operator/ (T other)
  {
    Vec3<T> vec3;
    for (unsigned int i = 0; i < 3; i++)
      vec3[i] = components[i] / other;
    return vec3;
  }
  Vec3<T> operator+ (T other)
  {
    Vec3<T> vec3;
    for (unsigned int i = 0; i < 3; i++)
      vec3[i] = components[i] + other;
    return vec3;
  }
  void operator*= (T other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] *= other;
  }
  void operator/= (T other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] /= other;
  }
  void lerp(Vec3<T> target, float speed)
  {
    (*this) += speed * (target - (*this));
  }

  Vec3<T> normalize()
  {
    Vec3<T> normal;
    T length = sqrtf(components[0] * components[0] + components[1] * components[1] + components[2] * components[2]);
    normal[0] = components[0] / length;
    normal[1] = components[1] / length;
    normal[2] = components[2] / length;

    return normal;
  }
  T dot(Vec3<T> other)
  {
    T result = 0;
    for (unsigned int i = 0; i < 3; i++)
      result += components[i] * other[i];
    return result;
  }
  T cross(Vec3<T> other, Vec3<T> another)
  {
    return ((other[0] - components[0]) * (another[1] - components[1]) - (other[1] - components[1]) * (another[0] - components[0]));
  }
  friend Vec3<T> operator/ (T other, Vec3<T> otherVec)
  {
    return otherVec / other;
  }
  friend Vec3<T> operator- (T other, Vec3<T> otherVec)
  {
    return otherVec - other;
  }
  friend Vec3<T> operator+ (T other, Vec3<T> otherVec)
  {
    return otherVec + other;
  }
  friend Vec3<T> operator* (T other, Vec3<T> otherVec)
  {
    return otherVec * other;
  }

  ~Vec3 ()
  {

  };
};
#endif
