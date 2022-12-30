#pragma once

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point m_Center;
	Point m_RadiusPoint;
	int m_Radius;

public:
	CCircle(Point center, Point radiusPoint, GfxInfo gfxInfo);
	
	//somehow close to a default constructor
	//for deserialization purposes
	CCircle(GfxInfo gfxInfo);

	virtual void Draw(Output* output) const override;
	virtual bool HitTest(Point hit) override;
	virtual void PrintInfo(const UIFrontend* frontend) const override;
	virtual void Translate(int dx, int dy) override;
	virtual Point GetPosition() override;
	virtual void Save(Serializer* serializer) override;
	virtual void Load(Deserializer* deserializer) override;
};