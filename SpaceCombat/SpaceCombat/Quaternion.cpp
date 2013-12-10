#include "Quaternion.h"
#include <math.h>
#include <iostream>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

Quaternion::Quaternion(void)
{
}


Quaternion::~Quaternion(void)
{
}

//Standard constructor that takes a scalar and vector components
Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	w = _w;
	x = _x;
	y = _y;
	z = _z;
}

//Constructor that makes a quaternion based on a rotation angle and a vector that represents the rotation axis
Quaternion::Quaternion(float rotAngle, vector<float> rotAxis)
{
	w = cos(rotAngle / 2);
	float vecScalar = sin(rotAngle / 2);
	x = vecScalar * rotAxis[0];
	y = vecScalar * rotAxis[1];
	z = vecScalar * rotAxis[2];
}

//Cross product of two quaternions, returns a new Quaternion
Quaternion Quaternion::operator*(Quaternion &second)
{
	float _w = (w * second.w) - (x * second.x + y * second.y + z * second.z);
	float _x = (w * second.x) + (second.w * x) + (y * second.z - second.y * z); 
	float _y = (w * second.y) + (second.w * y) + (z * second.x - second.z * x);
	float _z = (w * second.z) + (second.w * z) + (x * second.y - second.x * y);
	return Quaternion(_w, _x, _y, _z);
}

//Dot product of two quaternions, dot products are scalars
float Quaternion::operator%(Quaternion &second)
{
	return w * second.w + x * second.x + y * second.y + z * second.z;
}

//Difference of two quaternions
Quaternion Quaternion::operator-(Quaternion &second)
{
	return Quaternion(w - second.w, x - second.x, y - second.y, z - second.z);
}

//Normalize a quaternion to be a unit quaternion, useful for other calculations
Quaternion Quaternion::normalize(Quaternion &quat)
{
	double mag = magnitude(quat);
	return Quaternion(quat.w / mag, quat.x / mag, quat.y / mag, quat.z / mag);
}

//The magnitude(size) of a quaternion
float Quaternion::magnitude(Quaternion &quat)
{
	return sqrtf(powf(quat.w, 2) + powf(quat.x, 2) + powf(quat.y, 2) + powf(quat.z, 2));
}

Quaternion Quaternion::conjugate(Quaternion &quat)
{
	return Quaternion(quat.w, -quat.x, -quat.y, -quat.z);
}

Quaternion Quaternion::inverse(Quaternion &quat)
{
	//The inverse of a quaternion is its conjugate divided by its magnitude
	Quaternion conj = conjugate(quat);
	float mag = magnitude(quat);
	return Quaternion(conj.w / mag, conj.x / mag, conj.y / mag, conj.z / mag);
}

Quaternion Quaternion::slerp(Quaternion &q1, Quaternion &q2, double t)
{
	//Normalize the quaternions
	Quaternion normQ1 = Quaternion::normalize(q1);
	Quaternion normQ2 = Quaternion::normalize(q2);
	//Use the formulas to get the cosine and sine in order to get omega 
	double cosine = normQ1.getW() * normQ2.getW() + normQ1.getX() * normQ2.getX() + normQ1.getY() * normQ2.getY() + normQ1.getZ() * normQ2.getZ();
	double sine = sqrt(1 - pow(cosine, 2));
	double omega = atan2(sine, cosine);
	//Get the scalars and apply them to the quaternions, then add the components 
	double scalar1 = (sin((1 - t) * omega) / sin(omega));
	double scalar2 = (sin(t * omega) / sin(omega));
	return Quaternion(scalar1 * normQ1.getW() + scalar2 * normQ2.getW(), 
					  scalar1 * normQ1.getX() + scalar2 * normQ2.getX(),
					  scalar1 * normQ1.getY() + scalar2 * normQ2.getY(),
					  scalar1 * normQ1.getZ() + scalar2 * normQ2.getZ());
}

char* Quaternion::toString()
{
	//need a dynamic array
	char* result = new char[100];

	//use sprintf_s to format the data into a printable form
	sprintf_s(result, sizeof(char) * 100, "[%3.2f (%3.2f %3.2f %3.2f)] \n", w, x, y, z);
	return result;
}

Quaternion Quaternion::matrixToQuaternion(float matrix[16])
{
	float newW = sqrtf(matrix[0] + matrix[4] + matrix[8] + 1) / 2;
	float newX = sqrtf(matrix[0] - matrix[4] - matrix[8]+ 1) / 2;
	float newY = sqrtf(matrix[4] - matrix[0] - matrix[8] + 1) / 2;
	float newZ = sqrtf(matrix[8] - matrix[0] - matrix[4] + 1) / 2;
	return Quaternion(newW, newX, newY, newZ);
}

glm::mat4 Quaternion::quaternionToMatrix(Quaternion &quat)
{
	float matrix[16];
	Quaternion norm = Quaternion::normalize(quat);
	//OpenGL uses column-major 4x4 matrices to represent its rotations
	matrix[0] = 1 - (2 * norm.y * norm.y) - (2 * norm.z * norm.z);
	matrix[3] = 2 * norm.x * norm.y - 2 * norm.z * norm.w;
	matrix[6] = 2 * norm.x * norm.z + 2 * norm.y * norm.w;

	matrix[1] = 2 * norm.x * norm.y + 2 * norm.z * norm.w;
	matrix[4] = 1 - (2 * norm.x * norm.x) - (2 * norm.z * norm.z);
	matrix[7] = 2 * norm.y * norm.z - 2 * norm.x * norm.w;

	matrix[2] = 2 * norm.x * norm.z - 2 * norm.y * norm.w;
	matrix[5] = 2 * norm.y * norm.z + 2 * norm.x * norm.w;
	matrix[8] = 1 - (2 * norm.x * norm.x) - (2 * norm.y * norm.y);

	//GLM provides the make_mat4 function 
	glm::mat4 matx = glm::make_mat4(matrix);
	return matx;
}

double Quaternion::getW()
{
	return w;
}

double Quaternion::getX()
{
	return x;
}

double Quaternion::getY()
{
	return y;
}

double Quaternion::getZ()
{
	return z;
}
