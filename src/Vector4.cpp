#define HACHIT_MATH_EXPORTS

#include "HachitMath/Vector4.h"
#include "HachitMath/Vector3.h"

using namespace Hachit;
using namespace Math;

/*
	Constructors
*/

Vector4::Vector4()
{
	this->vector[0] = 0;
	this->vector[1] = 0;
	this->vector[2] = 0;
	this->vector[3] = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;
	this->vector[3] = w;
}

Vector4::Vector4(Vector3 v, float w)
{
	this->vector[0] = v[0];
	this->vector[1] = v[1];
	this->vector[2] = v[2];
	this->vector[3] = w;
}

Vector4::Vector4(const Vector4 & other)
{
	this->vector[0] = other.vector[0];
	this->vector[1] = other.vector[1];
	this->vector[2] = other.vector[2];
	this->vector[3] = other.vector[3];
}

/*
	Destructor
*/

Vector4::~Vector4()
{

}

/*
	Accessors and Mutators
*/

float Vector4::getX(){ return vector[0]; }
float Vector4::getY(){ return vector[1]; }
float Vector4::getZ(){ return vector[2]; }
float Vector4::getW(){ return vector[3]; }

float Vector4::getMagnitude(){ return sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]) + (vector[3] + vector[3])); }
float* Vector4::getAsArray(){ return vector; }

void Vector4::setX(float x){ this->vector[0] = x; }
void Vector4::setY(float y){ this->vector[1] = y; }
void Vector4::setZ(float z){ this->vector[2] = z; }
void Vector4::setW(float w){ this->vector[3] = w; }

/*
	Operators
*/

float& Vector4::operator[](int i)
{
	return vector[i];
}

//Typecasting Operators

Vector4::operator Vector3()
{
	return Vector3((*this));
}

//Extraction
std::ostream& Hachit::Math::operator<<(std::ostream& output, Vector4& v4)
{
	output << v4.getX() << std::endl << v4.getY() << std::endl << v4.getZ() << std::endl << v4.getW() << std::endl;
	return output;
}

//Insertion
std::istream& Hachit::Math::operator>> (std::istream& input, Vector4& v4)
{
	float x, y, z, w;
	input >> x >> y >> z >> w;

	v4.setX(x);
	v4.setY(y);
	v4.setZ(z);
	v4.setW(w);

	return input;
}
