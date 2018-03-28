#define DLL_IMPLEMENT

#include "Vector.h"


Vector::Vector(HandPoint & ptStart, HandPoint & ptEnd)
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

Vector::Vector()
{
}


Vector::~Vector()
{
}
