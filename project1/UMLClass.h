/**
 * \file UMLClass.h
 *
 *
 * Class that describes a UMLPiece made up of a single class
 */


#pragma once
#include "UMLPiece.h"
#include "UMLDisplay.h"

/**
 * Class that describes a single class UMLPiece object
 */
class CUMLClass : public CUMLPiece
{
public:
	CUMLClass(CGame* game, double x, double y, int speed);
	void Draw(Gdiplus::Graphics* graphics) override;
	void SetDisplay(std::shared_ptr<CUMLDisplay> display);
	virtual bool HitTest(int x, int y) override;

private:
	std::shared_ptr<CUMLDisplay> mClassDisplay = nullptr; ///< The CUMLDisplay object that displays this class
};

