#pragma once

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point m_Center;

	//The screenspace rectangle
	Rect m_Rect;

	//Updates the local screenspace rectangle
	void UpdateScreenSpaceRect();

public:
	CSquare(Point center, GfxInfo gfxInfo);

	//somehow close to a default constructor
	//for deserialization purposes
	CSquare(GfxInfo gfxInfo);

	virtual void Draw(Output* output) const override;
	virtual bool HitTest(Point hit) override;
	virtual void PrintInfo(const UIFrontend* frontend) const override;
	virtual void Translate(int dx, int dy) override;
	virtual Point GetPosition() override;
	virtual void Save(Serializer* serializer) override;
	virtual void Load(Deserializer* deserializer) override;
};