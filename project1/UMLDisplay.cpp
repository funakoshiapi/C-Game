/**
 * \file UMLDisplay.cpp
 *
 */

#include "pch.h"
#include "UMLDisplay.h"

using namespace Gdiplus;

/// The size of the font on the UML
const int FONT_SIZE = 13;

/// The name of the font to be used, static to avoid linking error
static const WCHAR* FONT_NAME = L"Arial";

/// Minimum height of a UMLPiece object
const double MIN_HEIGHT = 10.0f;

/// Minimum width of a UMLPiece object
const double MIN_WIDTH = 50.0f;

/**
 * Draws the UML on the screen
 * \param graphics The graphics device to be drawn on
 * \param x The x location at center of display
 * \param y The y location at center of display
 */
void CUMLDisplay::Draw(Gdiplus::Graphics* graphics, double x, double y)
{
	// Set dimensions if it is the first time being drawn
	if (mHeight == 0)
	{
		SetDimensions(graphics);
	}
	// Used in some size calculations
	Gdiplus::RectF size;
	Gdiplus::PointF origin(0.0f, 0.0f);
	double yOffset = y + mNameHeight;

	// Colors to be used
	SolidBrush yellowBrush(Color::Yellow);
	SolidBrush blackBrush(Color::Black);
	Pen blackPen(Color::Black);

	// Font to be used
	FontFamily fontFamily(FONT_NAME);
	Gdiplus::Font font(&fontFamily, FONT_SIZE);

	// Rectangle that contains UML
	Gdiplus::Rect rect(int(x), int(y), (int)mWidth, (int)mHeight);
	graphics->FillRectangle(&yellowBrush, rect);
	graphics->DrawRectangle(&blackPen, rect);

	// Draw name centered in UML
	graphics->DrawString(mName.c_str(), -1, &font, PointF((Gdiplus::REAL)(x + (mWidth - mNameWidth) / 2), (Gdiplus::REAL)y), &blackBrush);

	// Draw line between name and attributes
	graphics->DrawLine(&blackPen, PointF((Gdiplus::REAL)x, (Gdiplus::REAL)(y + mNameHeight)), 
		PointF((Gdiplus::REAL)(x + mWidth), (Gdiplus::REAL)(y + mNameHeight)));

	// Draw Attributes
	for (std::wstring att : mAttributes)
	{
		graphics->DrawString(att.c_str(), -1, &font, PointF((Gdiplus::REAL)x, (Gdiplus::REAL)yOffset), &blackBrush);
		graphics->MeasureString(att.c_str(), -1, &font, origin, &size);
		yOffset += (double)size.Height;

	}

	// Draw line between attributes and operations
	graphics->DrawLine(&blackPen, PointF((Gdiplus::REAL)x, (Gdiplus::REAL)yOffset), 
		PointF((Gdiplus::REAL)(x + mWidth), (Gdiplus::REAL)yOffset));

	// Draw operations
	for (std::wstring op : mOperations)
	{
		graphics->DrawString(op.c_str(), -1, &font, PointF((Gdiplus::REAL)x, (Gdiplus::REAL)yOffset), &blackBrush);
		graphics->MeasureString(op.c_str(), -1, &font, origin, &size);
		yOffset += (double)size.Height;

	}
	
}

/**
 * Sets the dimensions of the UMLDisplay
 * \param graphics The graphics device being drawn on
 */
void CUMLDisplay::SetDimensions(Gdiplus::Graphics* graphics)
{
	// Font to be used
	FontFamily fontFamily(FONT_NAME);
	Gdiplus::Font font(&fontFamily, FONT_SIZE);
	Gdiplus::RectF size;
	Gdiplus::PointF origin(0.0f, 0.0f);

	// Handle name
	graphics->MeasureString(mName.c_str(), -1, &font, origin, &size);
	mNameHeight = ((double)size.Height > 1.0f) ? (double)size.Height : 25.0f;
	mNameWidth = (double)size.Width;
	mHeight += mNameHeight;
	mWidth = (double)size.Width;

	// Handle attributes
	for (std::wstring att : mAttributes)
	{
		graphics->MeasureString(att.c_str(), -1, &font, origin, &size);
		mHeight += (double)size.Height;
		mAttributeHeight += (double)size.Height;
		
		if ((double)size.Width > mWidth)
		{
			mWidth = (double)size.Width;
		}
		
		if ((double)size.Width > mAttributeWidth)
		{
			mAttributeWidth = (double)size.Width;
		}
	}

	// Handle operations
	for (std::wstring op : mOperations)
	{
		graphics->MeasureString(op.c_str(), -1, &font, origin, &size);
		mHeight += (double)size.Height;
		mOperationHeight += (double)size.Height;

		if ((double)size.Width > mWidth)
		{
			mWidth = (double)size.Width;
		}

		if ((double)size.Width > mOperationWidth)
		{
			mOperationWidth = (double)size.Width;
		}
	}

	// Minimum height
	if (mHeight == 0.0f)
	{
		mHeight = MIN_HEIGHT;
	}

	// Minimum width
	if (mWidth == mNameHeight)
	{
		mWidth += MIN_WIDTH;
	}
}


	