#pragma once

#include <fstream>
#include <string>

#include "../DEFS.h"

class Deserializer
{
private:
	//The input filestream
	std::ifstream m_InStream;

public:
	Deserializer(std::string& path);

	//Returns true if the deserializer is valid (file exists)
	bool Valid();

	//Writes a point to the stream
	Point ReadPoint();

	//Writes a color to the stream
	color ReadColor();

	//Closes the file stream
	void Close();

	//Writes a custom object to the filestream
	template<typename T>
	T Read()
	{
		T t;
		m_InStream >> t;
		return t;
	}
};
