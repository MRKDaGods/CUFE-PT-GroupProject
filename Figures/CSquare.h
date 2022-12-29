#pragma once

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point m_Center;

public:
	CSquare(Point center, GfxInfo gfxInfo);
	virtual void Draw(Output* output) const;
};