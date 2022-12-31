#pragma once

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point m_P1;
	Point m_P2;
	Point m_P3;

	//Resizing nodes
	FigureNode m_Nodes[3];

protected:
	virtual void GetNodes(FigureNode*** nodes, int* sz) override;

public:
	CTriangle(int figID, Point p1, Point p2, Point p3, GfxInfo gfxInfo);

	//somehow close to a default constructor
	//for deserialization purposes
	CTriangle(GfxInfo gfxInfo);

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