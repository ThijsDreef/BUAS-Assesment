#ifndef MATRIX__
#define MATRIX__
#include "Math/vec3.h"
#define _USE_MATH_DEFINES
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <math.h>
#include <vector>
enum axis
{
	X,Y,Z
};
template <class T>
struct Matrix
{
private:
	void resetMatrix();
public:
	T matrix[16];
	void translateMatrix(Vec3<T> vec);
	void perspectiveView(float fov, float aspect, float zNear, float zFar);
	void orthographicView(float width, float height, float zNear, float zFar);
	void setAxisrotation(T angle , int axis);
	void lookAt(Vec3<float> eye, Vec3<float> center, Vec3<float> up);
	Matrix<T> rotation(Vec3<T> rotation);
	void scaleMatrix(Vec3<T> vec);
	Matrix();
	~Matrix();
	Matrix<T> inverse();
	Matrix<T> multiplyByMatrix(Matrix<T> otherMatrix);
	Vec3<T> multiplyByVector(Vec3<T> vec);
	Vec3<T> translateVector(Vec3<T> vec);
	void lightBias();
};

template<class T>
inline void Matrix<T>::lookAt(Vec3<float> eye, Vec3<float> center, Vec3<float> up)
{
	T x0, x1, x2, y0, y1, y2, z0, z1, z2, len,
	eyex = eye[0],
	eyey = eye[1],
	eyez = eye[2],
	upx = up[0],
	upy = up[1],
	upz = up[2],
	centerx = center[0],
	centery = center[1],
	centerz = center[2];

    if (abs(eyex - centerx) < 0.000001 &&
        abs(eyey - centery) < 0.000001 &&
        abs(eyez - centerz) < 0.000001) {
        return;
    }

    z0 = eyex - centerx;
    z1 = eyey - centery;
    z2 = eyez - centerz;

    len = 1 / sqrt(z0 * z0 + z1 * z1 + z2 * z2);
    z0 *= len;
    z1 *= len;
    z2 *= len;

    x0 = upy * z2 - upz * z1;
    x1 = upz * z0 - upx * z2;
    x2 = upx * z1 - upy * z0;
    len = sqrt(x0 * x0 + x1 * x1 + x2 * x2);
    if (!len) {
        x0 = 0;
        x1 = 0;
        x2 = 0;
    } else {
        len = 1 / len;
        x0 *= len;
        x1 *= len;
        x2 *= len;
    }

    y0 = z1 * x2 - z2 * x1;
    y1 = z2 * x0 - z0 * x2;
    y2 = z0 * x1 - z1 * x0;

    len = sqrt(y0 * y0 + y1 * y1 + y2 * y2);
    if (!len) {
        y0 = 0;
        y1 = 0;
        y2 = 0;
    } else {
        len = 1 / len;
        y0 *= len;
        y1 *= len;
        y2 *= len;
    }

    matrix[0] = x0;
    matrix[1] = y0;
    matrix[2] = z0;
    matrix[3] = 0;
    matrix[4] = x1;
    matrix[5] = y1;
    matrix[6] = z1;
    matrix[7] = 0;
    matrix[8] = x2;
    matrix[9] = y2;
    matrix[10] = z2;
    matrix[11] = 0;
    matrix[12] = -(x0 * eyex + x1 * eyey + x2 * eyez);
    matrix[13] = -(y0 * eyex + y1 * eyey + y2 * eyez);
    matrix[14] = -(z0 * eyex + z1 * eyey + z2 * eyez);
    matrix[15] = 1;
}

template<class T>
inline Matrix<T> Matrix<T>::inverse()
{
	double det;
	Matrix<float> inv;
  	int i;

  	inv.matrix[0] = matrix[5]  * matrix[10] * matrix[15] - matrix[5]  * matrix[11] * matrix[14] - matrix[9]  * matrix[6]  * matrix[15] +
           matrix[9]  * matrix[7]  * matrix[14] +
           matrix[13] * matrix[6]  * matrix[11] -
           matrix[13] * matrix[7]  * matrix[10];

  inv.matrix[4] = -matrix[4]  * matrix[10] * matrix[15] +
            matrix[4]  * matrix[11] * matrix[14] +
            matrix[8]  * matrix[6]  * matrix[15] -
            matrix[8]  * matrix[7]  * matrix[14] -
            matrix[12] * matrix[6]  * matrix[11] +
            matrix[12] * matrix[7]  * matrix[10];

  inv.matrix[8] = matrix[4]  * matrix[9] * matrix[15] -
           matrix[4]  * matrix[11] * matrix[13] -
           matrix[8]  * matrix[5] * matrix[15] +
           matrix[8]  * matrix[7] * matrix[13] +
           matrix[12] * matrix[5] * matrix[11] -
           matrix[12] * matrix[7] * matrix[9];

  inv.matrix[12] = -matrix[4]  * matrix[9] * matrix[14] +
             matrix[4]  * matrix[10] * matrix[13] +
             matrix[8]  * matrix[5] * matrix[14] -
             matrix[8]  * matrix[6] * matrix[13] -
             matrix[12] * matrix[5] * matrix[10] +
             matrix[12] * matrix[6] * matrix[9];

  inv.matrix[1] = -matrix[1]  * matrix[10] * matrix[15] +
            matrix[1]  * matrix[11] * matrix[14] +
            matrix[9]  * matrix[2] * matrix[15] -
            matrix[9]  * matrix[3] * matrix[14] -
            matrix[13] * matrix[2] * matrix[11] +
            matrix[13] * matrix[3] * matrix[10];

  inv.matrix[5] = matrix[0]  * matrix[10] * matrix[15] -
           matrix[0]  * matrix[11] * matrix[14] -
           matrix[8]  * matrix[2] * matrix[15] +
           matrix[8]  * matrix[3] * matrix[14] +
           matrix[12] * matrix[2] * matrix[11] -
           matrix[12] * matrix[3] * matrix[10];

  inv.matrix[9] = -matrix[0]  * matrix[9] * matrix[15] +
            matrix[0]  * matrix[11] * matrix[13] +
            matrix[8]  * matrix[1] * matrix[15] -
            matrix[8]  * matrix[3] * matrix[13] -
            matrix[12] * matrix[1] * matrix[11] +
            matrix[12] * matrix[3] * matrix[9];

  inv.matrix[13] = matrix[0]  * matrix[9] * matrix[14] -
            matrix[0]  * matrix[10] * matrix[13] -
            matrix[8]  * matrix[1] * matrix[14] +
            matrix[8]  * matrix[2] * matrix[13] +
            matrix[12] * matrix[1] * matrix[10] -
            matrix[12] * matrix[2] * matrix[9];

  inv.matrix[2] = matrix[1]  * matrix[6] * matrix[15] -
           matrix[1]  * matrix[7] * matrix[14] -
           matrix[5]  * matrix[2] * matrix[15] +
           matrix[5]  * matrix[3] * matrix[14] +
           matrix[13] * matrix[2] * matrix[7] -
           matrix[13] * matrix[3] * matrix[6];

  inv.matrix[6] = -matrix[0]  * matrix[6] * matrix[15] +
            matrix[0]  * matrix[7] * matrix[14] +
            matrix[4]  * matrix[2] * matrix[15] -
            matrix[4]  * matrix[3] * matrix[14] -
            matrix[12] * matrix[2] * matrix[7] +
            matrix[12] * matrix[3] * matrix[6];

  inv.matrix[10] = matrix[0]  * matrix[5] * matrix[15] -
            matrix[0]  * matrix[7] * matrix[13] -
            matrix[4]  * matrix[1] * matrix[15] +
            matrix[4]  * matrix[3] * matrix[13] +
            matrix[12] * matrix[1] * matrix[7] -
            matrix[12] * matrix[3] * matrix[5];

  inv.matrix[14] = -matrix[0]  * matrix[5] * matrix[14] +
             matrix[0]  * matrix[6] * matrix[13] +
             matrix[4]  * matrix[1] * matrix[14] -
             matrix[4]  * matrix[2] * matrix[13] -
             matrix[12] * matrix[1] * matrix[6] +
             matrix[12] * matrix[2] * matrix[5];

  inv.matrix[3] = -matrix[1] * matrix[6] * matrix[11] +
            matrix[1] * matrix[7] * matrix[10] +
            matrix[5] * matrix[2] * matrix[11] -
            matrix[5] * matrix[3] * matrix[10] -
            matrix[9] * matrix[2] * matrix[7] +
            matrix[9] * matrix[3] * matrix[6];

  inv.matrix[7] = matrix[0] * matrix[6] * matrix[11] -
           matrix[0] * matrix[7] * matrix[10] -
           matrix[4] * matrix[2] * matrix[11] +
           matrix[4] * matrix[3] * matrix[10] +
           matrix[8] * matrix[2] * matrix[7] -
           matrix[8] * matrix[3] * matrix[6];

  inv.matrix[11] = -matrix[0] * matrix[5] * matrix[11] +
             matrix[0] * matrix[7] * matrix[9] +
             matrix[4] * matrix[1] * matrix[11] -
             matrix[4] * matrix[3] * matrix[9] -
             matrix[8] * matrix[1] * matrix[7] +
             matrix[8] * matrix[3] * matrix[5];

  inv.matrix[15] = matrix[0] * matrix[5] * matrix[10] -
            matrix[0] * matrix[6] * matrix[9] -
            matrix[4] * matrix[1] * matrix[10] +
            matrix[4] * matrix[2] * matrix[9] +
            matrix[8] * matrix[1] * matrix[6] -
            matrix[8] * matrix[2] * matrix[5];

  det = matrix[0] * inv.matrix[0] + matrix[1] * inv.matrix[4] + matrix[2] * inv.matrix[8] + matrix[3] * inv.matrix[12];

  if (det == 0) {
		inv.resetMatrix();
		return inv;
	}

  det = 1.0 / det;

  for (i = 0; i < 16; i++)
      inv.matrix[i] *= det;

	return inv;
}

template<class T>
inline void Matrix<T>::resetMatrix()
{
	for (int i = 0; i < 16; i++)
		matrix[i] = 0;
}

template<class T>
inline void Matrix<T>::translateMatrix(Vec3<T> vec)
{
	resetMatrix();
	matrix[0] = 1;
	matrix[5] = 1;
	matrix[10] = 1;
	matrix[12] = vec[0];
	matrix[13] = vec[1];
	matrix[14] = vec[2];
	matrix[15] = 1;
}

template<class T>
inline void Matrix<T>::perspectiveView(float fov, float aspect, float zNear, float zFar)
{
	resetMatrix();
	float fovY = fov * M_PI / 180.0f;
	float tangent = tanf(fovY / 2 ); // tangent of half fovY
	float height = zNear * tangent;         // half height of near plane
	float width = height * aspect;   // half width of near plane

	matrix[0] = 2 * zNear / (width - -width);
	matrix[5] = 2 * zNear / (height - -height);
	matrix[8] = (width + -width) / (width - -width);
	matrix[9] = (height + -height) / (height - -height);
	matrix[10] = -(zFar + zNear) / (zFar - zNear);
	matrix[11] = -1;
	matrix[14] = -(2 * zFar * zNear) / (zFar - zNear);
}

template<class T>
inline void Matrix<T>::orthographicView(float width, float height, float zNear, float zFar)
{
	resetMatrix();
	matrix[0] = 2 / (width - -width);
	matrix[5] = 2 / (height - -height);
	matrix[10] = -2 / (zFar - zNear);
	matrix[11] = - (zFar + zNear) / (zFar - zNear);
	matrix[7] = - (height + -height) / (height - -height);
	matrix[3] = - (width + -width) / (width - -width);
	matrix[15] = 1;
}

template<class T>
inline void Matrix<T>::lightBias()
{
	resetMatrix();
	matrix[0] = 0.5;
	matrix[5] = 0.5;
	matrix[10] = 0.5;
	matrix[12] = 0.5;
	matrix[13] = 0.5;
	matrix[14] = 0.5;
	matrix[15] = 1;
}

template<class T>
inline void Matrix<T>::setAxisrotation(T angle, int axis)
{
	resetMatrix();
	float radians = angle * M_PI / 180.0f;
	if (axis == X)
	{
		matrix[0] = 1;
		matrix[5] = cos(radians);
		matrix[6] = -sin(radians);
		matrix[9] = sin(radians);
		matrix[10] = cos(radians);
		matrix[15] = 1;
	}
	else if (axis == Y)
	{
		matrix[0] = cos(radians);
		matrix[2] = sin(radians);
		matrix[5] = 1;
		matrix[8] = -sin(radians);
		matrix[10] = cos(radians);
		matrix[15] = 1;
	}
	else if (axis == Z)
	{
		matrix[0] = cos(radians);
		matrix[1] = -sin(radians);
		matrix[4] = sin(radians);
		matrix[5] = cos(radians);
		matrix[10] = 1;
		matrix[15] = 1;
	}
}

template<class T>
inline Matrix<T> Matrix<T>::rotation(Vec3<T> rotation)
{
	//z y x rotation
	Matrix<T> result;
	Matrix<T> temp;
	result.setAxisrotation(rotation[1], Y);
	temp.setAxisrotation(rotation[0], X);
	result = result.multiplyByMatrix(temp);
	temp.setAxisrotation(rotation[2], Z);
	return result.multiplyByMatrix(temp);
}

template<class T>
inline void Matrix<T>::scaleMatrix(Vec3<T> vec)
{
	resetMatrix();
	matrix[0] = vec[0];
	matrix[5] = vec[1];
	matrix[10] = vec[2];
	matrix[15] = 1;
}

template<class T>
inline Matrix<T>::Matrix()
{
	matrix[0] = 1;
	matrix[6] = 1;
	matrix[11] = 1;
	matrix[15] = 1;
}

template<class T>
inline Matrix<T>::~Matrix()
{

}

template<class T>
inline Matrix<T> Matrix<T>::multiplyByMatrix(Matrix<T> otherMatrix)
{
	Matrix<T> temp;
	//need to be replaced with a nice for loop
	temp.matrix[0] = matrix[0] * otherMatrix.matrix[0] + matrix[4] * otherMatrix.matrix[1] + matrix[8] * otherMatrix.matrix[2] + matrix[12] * otherMatrix.matrix[3];
	temp.matrix[1] = matrix[1] * otherMatrix.matrix[0] + matrix[5] * otherMatrix.matrix[1] + matrix[9] * otherMatrix.matrix[2] + matrix[13] * otherMatrix.matrix[3];
	temp.matrix[2] = matrix[2] * otherMatrix.matrix[0] + matrix[6] * otherMatrix.matrix[1] + matrix[10] * otherMatrix.matrix[2] + matrix[14] * otherMatrix.matrix[3];
	temp.matrix[3] = matrix[3] * otherMatrix.matrix[0] + matrix[7] * otherMatrix.matrix[1] + matrix[11] * otherMatrix.matrix[2] + matrix[15] * otherMatrix.matrix[3];

	temp.matrix[4] = matrix[0] * otherMatrix.matrix[4] + matrix[4] * otherMatrix.matrix[5] + matrix[8] * otherMatrix.matrix[6] + matrix[12] * otherMatrix.matrix[7];
	temp.matrix[5] = matrix[1] * otherMatrix.matrix[4] + matrix[5] * otherMatrix.matrix[5] + matrix[9] * otherMatrix.matrix[6] + matrix[13] * otherMatrix.matrix[7];
	temp.matrix[6] = matrix[2] * otherMatrix.matrix[4] + matrix[6] * otherMatrix.matrix[5] + matrix[10] * otherMatrix.matrix[6] + matrix[14] * otherMatrix.matrix[7];
	temp.matrix[7] = matrix[3] * otherMatrix.matrix[4] + matrix[7] * otherMatrix.matrix[5] + matrix[11] * otherMatrix.matrix[6] + matrix[15] * otherMatrix.matrix[7];

	temp.matrix[8] = matrix[0] * otherMatrix.matrix[8] + matrix[4] * otherMatrix.matrix[9] + matrix[8] * otherMatrix.matrix[10] + matrix[12] * otherMatrix.matrix[11];
	temp.matrix[9] = matrix[1] * otherMatrix.matrix[8] + matrix[5] * otherMatrix.matrix[9] + matrix[9] * otherMatrix.matrix[10] + matrix[13] * otherMatrix.matrix[11];
	temp.matrix[10] = matrix[2] * otherMatrix.matrix[8] + matrix[6] * otherMatrix.matrix[9] + matrix[10] * otherMatrix.matrix[10] + matrix[14] * otherMatrix.matrix[11];
	temp.matrix[11] = matrix[3] * otherMatrix.matrix[8] + matrix[7] * otherMatrix.matrix[9] + matrix[11] * otherMatrix.matrix[10] + matrix[15] * otherMatrix.matrix[11];

	temp.matrix[12] = matrix[0] * otherMatrix.matrix[12] + matrix[4] * otherMatrix.matrix[13] + matrix[8] * otherMatrix.matrix[14] + matrix[12] * otherMatrix.matrix[15];
	temp.matrix[13] = matrix[1] * otherMatrix.matrix[12] + matrix[5] * otherMatrix.matrix[13] + matrix[9] * otherMatrix.matrix[14] + matrix[13] * otherMatrix.matrix[15];
	temp.matrix[14] = matrix[2] * otherMatrix.matrix[12] + matrix[6] * otherMatrix.matrix[13] + matrix[10] * otherMatrix.matrix[14] + matrix[14] * otherMatrix.matrix[15];
	temp.matrix[15] = matrix[3] * otherMatrix.matrix[12] + matrix[7] * otherMatrix.matrix[13] + matrix[11] * otherMatrix.matrix[14] + matrix[15] * otherMatrix.matrix[15];
	return temp;
}

template<class T>
inline Vec3<T> Matrix<T>::multiplyByVector(Vec3<T> vec)
{
	Vec3<T> temp;
	temp[0] = vec[0] * matrix[0] + vec[1] * matrix[4] + vec[2] * matrix[8];
	temp[1] = vec[0] * matrix[1] + vec[1] * matrix[5] + vec[2] * matrix[9];
	temp[2] = vec[0] * matrix[2] + vec[1] * matrix[6] + vec[2] * matrix[10];
	return temp;
}

template<class T>
inline Vec3<T> Matrix<T>::translateVector(Vec3<T> vec)
{
	Vec3<T> temp;
	temp[0] = vec[0] + matrix[12];
	temp[1] = vec[1] + matrix[13];
	temp[2] = vec[2] + matrix[14];
	return temp;
}
#endif
