#ifndef VEC4__
#define VEC4__
template<class T>
struct Vec4
{
private:
  T components[4];
public:
  Vec4 (T x, T y, T z,T w)
  {
    components[0] = x;
    components[1] = y;
    components[2] = z;
    components[3] = w;
  }
  Vec4 ()
  {
    for (int i = 0; i < 4; i ++)
      components[i] = 0;
  };
  T& operator[] (int i)
  {
    return components[i];
  }
  Vec4<T>& operator*(Vec4<T> other)
  {
    Vec4<T> vec4;
    for (int i = 0; i < 4; i++)
      vec4[i] = components[i] * other[i];
    return vec4;
  }
  Vec4<T>& operator+(Vec4<T> other)
  {
    Vec4<T> vec4;
    for (int i = 0; i < 4; i++)
      vec4[i] = components[i] + other[i];
    return vec4;
  }
  Vec4<T>& operator-(Vec4<T> other)
  {
    Vec4<T> vec4;
    for (int i = 0; i < 4; i++)
      vec4[i] = components[i] - other[i];
    return vec4;
  }
  Vec4<T>& operator/(Vec4<T> other)
  {
    Vec4<T> vec4;
    for (int i = 0; i < 4; i++)
      vec4[i] = components[i] / other[i];
    return vec4;
  }
  ~Vec4 ()
  {

  };
};
#endif
