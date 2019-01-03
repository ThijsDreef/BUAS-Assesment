#ifndef VEC2__
#define VEC2__
template<class T>
struct Vec2
{
private:
  T components[2];
public:
  Vec2 (T x, T y)
  {
    components[0] = x;
    components[1] = y;
  }
  Vec2 ()
  {
    for (int i = 0; i < 2; i ++)
      components[i] = 0;
  };
  T& operator[] (int i)
  {
    return components[i];
  }
  Vec2<T> operator*(Vec2<T> other)
  {
    Vec2<T> vec2;
    for (int i = 0; i < 2; i++)
      vec2[i] = components[i] * other[i];
    return vec2;
  }
  Vec2<T> operator+(Vec2<T> other)
  {
    Vec2<T> vec2;
    for (int i = 0; i < 2; i++)
      vec2[i] = components[i] + other[i];
    return vec2;
  }
  Vec2<T> operator-(Vec2<T> other)
  {
    Vec2<T> vec2;
    for (int i = 0; i < 2; i++)
      vec2[i] = components[i] - other[i];
    return vec2;
  }
  Vec2<T> operator/(Vec2<T> other)
  {
    Vec2<T> vec2;
    for (int i = 0; i < 2; i++)
      vec2[i] = components[i] / other[i];
    return vec2;
  }

  ~Vec2 ()
  {

  };
};
#endif
