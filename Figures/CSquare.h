#pragma once

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point m_Center;

	//The screenspace rectangle
	Rect m_Rect;

	//Resizing nodes
	FigureNode m_Nodes[4];

	//Updates the local screenspace rectangle
	void UpdateScreenSpaceRect();

protected:
	virtual void GetNodes(FigureNode*** nodes, int* sz) override;

public:
	CSquare(int figID, Point center, GfxInfo gfxInfo);

	//somehow close to a default constructor
	//for deserialization purposes
	CSquare(GfxInfo gfxInfo);

	virtual void Draw(Output* output) override;
	virtual bool HitTest(Point hit) override;
	virtual void PrintInfo(const UIFrontend* frontend) const override;
	virtual void Translate(int dx, int dy) override;
	virtual void Resize(FigureNode* targetNode) override;
	virtual Point GetPosition() override;
	virtual DWShape GetShape() override;
	virtual void Save(Serializer* serializer) override;
	virtual void Load(Deserializer* deserializer) override;
};