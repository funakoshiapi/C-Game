/**
 * \file UMLPiece.cpp
 *
 */

#include "pch.h"
#include <vector>
#include <memory>
#include "UMLPiece.h"
#include "Game.h"
#include <memory>

using namespace Gdiplus;
using namespace std;

/// The maximum Y value of the display
const double SCREEN_SIZE_Y = 1000;

/// How long the UMLPiece object persists after being struck by pen
const double StuckDuration = 1.0;

/// The size of the font on the UML hit message
const int FONT_SIZE = 25;

/// String used to indicate that a good UMLPiece was incorrectly hit
const wstring UNFAIR = L"Unfair";

/// String value of a good UMLPiece's mBad data member when been instantiated
const wstring EMPTY = L"";

/// Name of font to be used, static to avoid link error
static const WCHAR* FONT_NAME = L"Arial";

/**
 * CUMLPiece Constructor
 * \param game The game this CUMLPiece object is part of
 * \param x X direction of movement
 * \param y Y direction of movement
 * \param speed How fast the piece is moving
 */
CUMLPiece::CUMLPiece(CGame* game, double x, double y, int speed) : CGameObject(game)
{
	mXDirection = x;
	mYDirection = y;
	mSpeed = speed;
	mHitUMLTimer = make_shared<CTimer>(GetGame(), StuckDuration);
	GetGame()->Add(mHitUMLTimer);
}

/**
 * Moves UMLPiece object according to its velocity
 * \param elapsed The amount of time passed since last update
 */
void CUMLPiece::Update(double elapsed)
{
	double newX = elapsed * mSpeed * mXDirection + GetX();
	double newY = elapsed * mSpeed * mYDirection + GetY();
	if (!mWasHit)
	{
		CGameObject::SetLocation(newX, newY);
	}
	else
	{
		if (mHitUMLTimer->IsTimeUp() || GetGame()->IsGameOver())
		{
			MarkForDelete(true);
		}
	}
	// Checks if object has left screen
	if (LeaveScreenCheck())
	{
		// If piece was bad signal missed
		if (mBad != EMPTY)
		{
			GetGame()->UMLMissed();
		}

		// Queue object for deletion at end of update
		MarkForDelete(true);
	}
}

/**
 * Marks uml hit and starts timer
 * \param status hit status
 */
void CUMLPiece::MarkHit(bool status)
{
	mWasHit = status;
	mHitUMLTimer->Start();
}

/**
 * Checks if the UMLPiece has left the screen
 * \returns True if the UMLPiece object has left the screen
 */
bool CUMLPiece::LeaveScreenCheck()
{
	// Could be used to signal missed/correct and indicate that this object should be destroyed
	return GetY() > SCREEN_SIZE_Y;
}

/**
 * Displays the appropriate hit message for this UMLPiece object
 * \param graphics The graphics device to draw this message on
 * \param x X location to draw the message (in virtual pixels)
 * \param y Y location to draw the message (in virtual pixels)
 */
void CUMLPiece::DisplayHitMessage(Gdiplus::Graphics* graphics, double& x, double& y)
{
	SolidBrush messageBrush(Color(0, 0, 0)); // Pen to display message with, defaults to black

	// Good UML, Set color and update message
	if (mBad == EMPTY || mBad == UNFAIR)
	{
		mBad = UNFAIR;
		messageBrush.SetColor(Color::Red);
	}

	// Bad UML, set color
	else
	{
		messageBrush.SetColor(Color::DarkGreen);
	}

	// Used in size calculation
	Gdiplus::RectF size;
	Gdiplus::PointF origin(0.0f, 0.0f);

	// Font to be used
	Gdiplus::FontFamily fontFamily(FONT_NAME);
	Gdiplus::Font font(&fontFamily, FONT_SIZE);

	// Calculate size of message string
	graphics->MeasureString(GetBad().c_str(), -1, &font, origin, &size);

	double newX = x - (double)size.Width / 2;
	double newY = y - (double)size.Height / 2;

	// Draw UML Hit Message
	graphics->DrawString(mBad.c_str(), -1, &font, PointF((Gdiplus::REAL)newX, (Gdiplus::REAL)newY), &messageBrush);
}