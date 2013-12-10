/**
* Quaternion Class by Alex Nowak
*
* Quaternions are used to represent rotations in 3D space. They have the advantage of being easier to interpolate
* and do not suffer from gimbal lock.
* This class contains functions to make quaternions convenient to use.
*/
#pragma once
#include <vector>
#include <glm/glm.hpp>
class Quaternion
{
private:
	float w;
	float x;
	float y;
	float z;

public:
	Quaternion(void);
	~Quaternion(void);
	Quaternion(float _w, float _x, float _y, float _z);
	Quaternion(float rotAngle, std::vector<float> rotAxis);

	Quaternion operator*(Quaternion &second);
	float operator%(Quaternion &second);
	Quaternion operator-(Quaternion &second);

	static Quaternion normalize(Quaternion &quat);
	static float magnitude(Quaternion &quat);
	static Quaternion conjugate (Quaternion &quat);
	static Quaternion inverse(Quaternion &quat);
	static Quaternion slerp(Quaternion &q1, Quaternion &q2, double t); 
	char* toString();
	Quaternion matrixToQuaternion(float matrix[16]);
	static glm::mat4 quaternionToMatrix(Quaternion &quat);

	//Getters
	double getW();
	double getX();
	double getY();
	double getZ();
};

