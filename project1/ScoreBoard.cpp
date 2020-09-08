/**
 * \file ScoreBoard.cpp
 *
 */

#include "pch.h"
#include <string>
#include "ScoreBoard.h"


using namespace Gdiplus;
using namespace std;

/// Font to be used while drawing the scoreboard, static to avoid link errors
static const WCHAR* FONT_NAME = L"Arial";

/// Size of the font used to draw the numbers on the scoreboard
const int NUMBER_FONT_SIZE = 60;

/// Size of the font used to draw the text on the scoreboard
const int LABEL_FONT_SIZE = 30;

/// Point to draw the number of correctly hit UMLPieces
const PointF CORRECT_POINT = PointF(-312.5 - 30, 20);

/// Point to draw the number of unfairly hit UMLPieces
const PointF UNFAIR_POINT = PointF(312.5 - 30, 20);

/// Point to draw the number of missed bad UMLPieces
const PointF MISSED_POINT = PointF(-30, 20);

/// How far offset the text is from the numbers in virtual pixels
const int LABEL_Y_OFFSET = 90;

/// 'Correct' label value for scoreboard
const wstring CORRECT = L"Correct";

/// 'Missed' label value for scoreboard
const wstring MISSED = L"Missed";

/// 'Unfair' label value for scoreboard
const wstring UNFAIR = L"Unfair";

CScoreBoard::CScoreBoard(CGame* game) : CGameObject(game)
{
}

/**
 * Draws the scoreboard
 * \param graphics Graphics device this object is being drawn on
 */
void CScoreBoard::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily font(FONT_NAME);
	Gdiplus::Font fontNumber(&font, NUMBER_FONT_SIZE, FontStyleBold);
	Gdiplus::Font fontLabel(&font, LABEL_FONT_SIZE, FontStyleBold);
	SolidBrush tealBrush(Color::Teal);
	
	// Used in size calculations
	PointF origin(0.0f, 0.0f);
	RectF sizeNumber;
	RectF sizeLabel;

	// Draw score values
	graphics->DrawString(to_wstring(mCorrect).c_str(), -1, &fontNumber, CORRECT_POINT, &tealBrush);
	graphics->DrawString(to_wstring(mMissed).c_str(), -1, &fontNumber, MISSED_POINT, &tealBrush);
	graphics->DrawString(to_wstring(mUnfair).c_str(), -1, &fontNumber, UNFAIR_POINT, &tealBrush);
	
	///
	/// Draw labels
	///

	/// Draw Correct Label
	graphics->MeasureString(to_wstring(mCorrect).c_str(), -1, &fontLabel, origin, &sizeNumber);
	graphics->MeasureString(CORRECT.c_str(), -1, &fontLabel, origin, &sizeLabel);
	graphics->DrawString(CORRECT.c_str(), -1, &fontLabel, PointF(CORRECT_POINT.X + (sizeNumber.Width) - (sizeLabel.Width / 2),
		CORRECT_POINT.Y + LABEL_Y_OFFSET), &tealBrush);

	/// Draw Missed Label
	graphics->MeasureString(to_wstring(mMissed).c_str(), -1, &fontLabel, origin, &sizeNumber);
	graphics->MeasureString(MISSED.c_str(), -1, &fontLabel, origin, &sizeLabel);
	graphics->DrawString(MISSED.c_str(), -1, &fontLabel, PointF(MISSED_POINT.X + (sizeNumber.Width) - (sizeLabel.Width / 2),
		MISSED_POINT.Y + LABEL_Y_OFFSET), &tealBrush);

	/// Draw Unfair Label
	graphics->MeasureString(to_wstring(mUnfair).c_str(), -1, &fontLabel, origin, &sizeNumber);
	graphics->MeasureString(UNFAIR.c_str(), -1, &fontLabel, origin, &sizeLabel);
	graphics->DrawString(UNFAIR.c_str(), -1, &fontLabel, PointF(UNFAIR_POINT.X + (sizeNumber.Width) - (sizeLabel.Width / 2),
		UNFAIR_POINT.Y + LABEL_Y_OFFSET), &tealBrush);
}


