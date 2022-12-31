#pragma once

#include "CFigure.h"

struct Rect;

class CRectangle : public CFigure
{
private:
	Point m_P1;
	Point m_P2;
	
	//The screenspace rectangle (On the screen coordinates)
	Rect m_Rect;

	//Resizing nodes
	FigureNode m_Nodes[4];

	//Updates the local screenspace rectangle
	void UpdateScreenSpaceRect();

protected:
	virtual void GetNodes(FigureNode*** nodes, int* sz) override;

public:
	CRectangle(int figID, Point p1, Point p2, GfxInfo gfxInfo);

	//somehow close to a default constructor
	//for deserialization purposes
	CRectangle(GfxInfo gfxInfo);

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