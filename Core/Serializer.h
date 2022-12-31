#pragma once

#include <fstream>
#include <string>

#include "../DEFS.h"

class Serializer
{
private:
	//The output filestream
	std::ofstream m_OutStream;

	//Appends a delimiter (space)
	void Seperate();

public:
	Serializer(std::string path);

	//Writes a point to the stream
	void WritePoint(const Point& p);

	//Writes a color to the stream
	void WriteColor(const color& c);

	//Closes the file stream
	void Close();

	//Writes a custom object to the filestream
	template<typename T>
	void Write(T obj)
	{
		m_OutStream << obj;
		Seperate();
	}
};
