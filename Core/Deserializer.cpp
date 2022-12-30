#include "Deserializer.h"
#include "../Utils/Color.h"

Deserializer::Deserializer(std::string& path)
{
	m_InStream.open(path, ios::in);
}

bool Deserializer::Valid()
{
	return m_InStream.good();
}

Point Deserializer::ReadPoint()
{
	//Read point as 2 integers
	int x, y;
	m_InStream >> x >> y;
	return Point{ x, y };
}

color Deserializer::ReadColor()
{
	//read as int then cast to enum
	int col;
	m_InStream >> col;

	return FrontendToNativeColor((DWColors)col);
}

void Deserializer::Close()
{
	m_InStream.close();
}
