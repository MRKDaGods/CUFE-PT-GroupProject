#include "Serializer.h"
#include "../Utils/Color.h"

#include <iostream>

Serializer::Serializer(std::string path)
{
	m_OutStream.open(path, ios::out);
}

void Serializer::WritePoint(const Point& p)
{
	m_OutStream << p.x << ' ' << p.y;

	Seperate();
}

void Serializer::WriteColor(const color& c)
{
	m_OutStream << NativeToFrontendColor(c) << ' ';

	Seperate();
}

void Serializer::Close()
{
	m_OutStream.close();
}

void Serializer::Seperate()
{
	m_OutStream << ' ';
}