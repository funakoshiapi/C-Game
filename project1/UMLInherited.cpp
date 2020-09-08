/**
 * \file UMLInherited.cpp
 *
 */

#include "pch.h"
#include "UMLInherited.h"

using Gdiplus::PointF;

/// Number of pixels between base and derived class in Y direction
const double Y_OFFSET = 50;

/// How many pixels away from tip/tail arrow ends are in Y direction
const double ARROW_Y_OFFSET = 15;

/// How many pixels away from tip/tail arrow ends are in X direction
const double ARROW_X_OFFSET = 20;

/// How many pixels to left or right of arrow a hit can be for hit detection
const double X_BUFFER = 5;

/// String indicating that the inherited UML's arrow points up
const std::wstring UP = L"up";

/**
 * CUMLInherited Constructor
 *
 * Calls CUMLPiece Constructor
 *
 * \param game The game this object is part of
 * \param x X Direction
 * \param y Y Direction
 * \param speed Speed that this object moves
 */
CUMLInherited::CUMLInherited(CGame* game, double x, double y, int speed) : CUMLPiece(game, x, y, speed)
{
}

/**
 * Draws this object by drawing the UMLDisplays associated with this object and an arrow
 * \param graphics The graphics device being drawn on
 */
void CUMLInherited::Draw(Gdiplus::Graphics* graphics)
{
	// Set the dimensions of both UMLDisplays, as they will be needed to correctly display the final result
	if (mFirstDraw)
	{
		mBaseDisplay->SetDimensions(graphics);
		mDerivedDisplay->SetDimensions(graphics);
		mFirstDraw = false;
	}
	
	double derivedY = GetY() + mBaseDisplay->GetHeight() + Y_OFFSET;
	double derivedX = GetX() + (mBaseDisplay->GetWidth() - mDerivedDisplay->GetWidth()) / 2;

	// Center and Space Base and Derived
	mBaseDisplay->Draw(graphics,GetX(),GetY()); // Draw Base
	mDerivedDisplay->Draw(graphics,derivedX,derivedY); // Draw Derived

	// Pen used to draw arrow
	Gdiplus::Pen blackPen(Gdiplus::Color::Black);

	// Pen used to clean up leftover arrow
	Gdiplus::Pen eraser(Gdiplus::Color::White);

	// Draw shaft of arrow
	PointF topPoint((Gdiplus::REAL)(derivedX + (mDerivedDisplay->GetWidth() / 2)), (Gdiplus::REAL)(derivedY - Y_OFFSET) );
	PointF tailPoint((Gdiplus::REAL)(derivedX + (mDerivedDisplay->GetWidth() / 2)), (Gdiplus::REAL)(derivedY));
	graphics->DrawLine(&blackPen, topPoint, tailPoint);

	// Draw up arrow tip
	if (mArrowDirection == UP)
	{
		// Points needed to draw up arrow
		PointF leftTop((Gdiplus::REAL)(topPoint.X - ARROW_X_OFFSET), (Gdiplus::REAL)(topPoint.Y + ARROW_Y_OFFSET));
		PointF rightTop((Gdiplus::REAL)(topPoint.X + ARROW_X_OFFSET), (Gdiplus::REAL)(topPoint.Y + ARROW_Y_OFFSET));
		PointF topBase((Gdiplus::REAL)topPoint.X, (Gdiplus::REAL)(topPoint.Y + ARROW_Y_OFFSET) );

		// Draws up arrow
		graphics->DrawLine(&blackPen, topPoint, leftTop);
		graphics->DrawLine(&blackPen, topPoint, rightTop);
		graphics->DrawLine(&blackPen, leftTop, rightTop);
		graphics->DrawLine(&eraser, topPoint, topBase);
	}

	// Draw down arrow tip
	else
	{
		// Points needed to draw down arrow
		PointF leftBottom((Gdiplus::REAL)(tailPoint.X - ARROW_X_OFFSET), (Gdiplus::REAL)(tailPoint.Y - ARROW_Y_OFFSET));
		PointF rightBottom((Gdiplus::REAL)(tailPoint.X + ARROW_X_OFFSET), (Gdiplus::REAL)(tailPoint.Y - ARROW_Y_OFFSET));
		PointF bottomBase((Gdiplus::REAL)tailPoint.X, (Gdiplus::REAL)(tailPoint.Y - ARROW_Y_OFFSET));

		// Draws down arrow
		graphics->DrawLine(&blackPen, tailPoint, leftBottom);
		graphics->DrawLine(&blackPen, tailPoint, rightBottom);
		graphics->DrawLine(&blackPen, leftBottom, rightBottom);
		graphics->DrawLine(&eraser, tailPoint, bottomBase);
	}

	// Draw hit message if hit
	if (GetWasHit())
	{
		double x = GetX() + mBaseDisplay->GetWidth() / 2;
		double y = GetY() + mBaseDisplay->GetHeight() + Y_OFFSET;

		DisplayHitMessage(graphics,x,y);
	}
}

/**
 * Setter for mBaseDisplay
 * \param display New value of mBaseDisplay
 */
void CUMLInherited::SetBaseDisplay(std::shared_ptr<CUMLDisplay> display)
{
	mBaseDisplay = display;
}

/**
 * Setter for mDerivedDisplay
 * \param display New value of mDerivedDisplay
 */
void CUMLInherited::SetDerivedDisplay(std::shared_ptr<CUMLDisplay> display)
{
	mDerivedDisplay = display;
}

/**
 * Setter for mArrowDirection
 * \param direction The direction the arrow should be pointing when drawn
 */
void CUMLInherited::SetArrowDirection(std::wstring direction)
{
	mArrowDirection = direction;
}

/**
 * Determines if a set of coordinates have hit this object
 *
 * Used mainly for Pen collision detection
 * \param x X location of hit
 * \param y Y location of hit
 * \returns True if the given arguments result in a hit
 */
bool CUMLInherited::HitTest(int x, int y)
{
	// Get dimensions of 1st CUMLDisplay member
	double height = mBaseDisplay->GetHeight();
	double width = mBaseDisplay->GetWidth();

	// Determine acceptable X values
	double minX = GetX();
	double maxX = minX + width;

	// Determine acceptable Y values
	double minY = GetY();
	double maxY = minY + height;

	// Determine if given x and y are valid
	bool validX = (x >= minX) && (x <= maxX);
	bool validY = (y >= minY) && (y <= maxY);

	// Determine if arguments hit base class
	bool baseHit = (validX && validY);

	// Get dimensions of 2nd CUMLDisplay member
	height = mDerivedDisplay->GetHeight();
	width = mDerivedDisplay->GetWidth();

	// Determine acceptable X values
	minX = GetX() + (mBaseDisplay->GetWidth() - width) / 2;
	maxX = minX + width;

	// Determine acceptable Y values
	minY = GetY() + mBaseDisplay->GetHeight() + Y_OFFSET;
	maxY = minY + height;

	// Determine if given x and y are valid
	validX = (x >= minX) && (x <= maxX);
	validY = (y >= minY) && (y <= maxY);

	// Determine if arguments hit derived class
	bool derivedHit = (validX && validY);

	minX = ((GetX() + (mBaseDisplay->GetWidth() - mDerivedDisplay->GetWidth()) / 2) + (mDerivedDisplay->GetWidth() / 2)) - X_BUFFER;
	maxX = minX + 2 * X_BUFFER;
	minY = GetY() + mBaseDisplay->GetHeight();
	maxY = minY + Y_OFFSET;

	// Determine if given x and y are valid
	validX = (x >= minX) && (x <= maxX);
	validY = (y >= minY) && (y <= maxY);

	// Determine if arguments hit arrow
	bool arrowHit = (validX && validY);

	// Returns tru if either base class, derived class, or arrow were hit
	return (arrowHit || baseHit || derivedHit);
}

