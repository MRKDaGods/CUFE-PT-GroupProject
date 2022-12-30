#pragma once

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point m_P1;
	Point m_P2;
	Point m_P3;

public:
	CTriangle(Point p1, Point p2, Point p3, GfxInfo gfxInfo);

	//somehow close to a default constructor
	//for deserialization purposes
	CTriangle(GfxInfo gfxInfo);

	virtual void Draw(Output* output) const override;
	virtual bool HitTest(Point hit) override;
	virtual void PrintInfo(const UIFrontend* frontend) const override;
	virtual void Translate(int dx, int dy) override;
	virtual Point GetPosition() override;
	virtual void Save(Serializer* serializer) override;
	virtual void Load(Deserializer* deserializer) override;
};