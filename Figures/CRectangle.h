#pragma once

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point m_P1;
	Point m_P2;

public:
	CRectangle(Point p1, Point p2, GfxInfo gfxInfo);
	virtual void Draw(Output* output) const;
};