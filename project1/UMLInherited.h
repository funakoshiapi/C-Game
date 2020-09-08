/**
 * \file UMLInherited.h
 *
 *
 * Class that describes a UMLPiece with an inheritance relationship
 */


#pragma once
#include "UMLPiece.h"
#include "UMLDisplay.h"

/**
 * Class that describes a UMLPiece that has inheritance
 */
class CUMLInherited : public CUMLPiece
{
public:
	CUMLInherited(CGame* game, double x, double y, int speed);
	
	void Draw(Gdiplus::Graphics* graphics) override;
	
	void SetBaseDisplay(std::shared_ptr<CUMLDisplay> display);
	void SetDerivedDisplay(std::shared_ptr<CUMLDisplay> display);
	void SetArrowDirection(std::wstring direction);
	virtual bool HitTest(int x, int y) override;

private:
	std::shared_ptr<CUMLDisplay> mBaseDisplay = nullptr; ///< The CUMLDisplay object that displays the base class
	std::shared_ptr<CUMLDisplay> mDerivedDisplay = nullptr; ///< The CUMLDisplay object that displays the derived class
	std::wstring mArrowDirection;	///< The direction of the arrow
	bool mFirstDraw = true; ///< Indicates if it is the first time the piece has been drawn

};

