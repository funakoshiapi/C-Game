

#include "pch.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "DisplayTimer.h"

using namespace Gdiplus;
using namespace std;

/// Name of font going to be used, static to avoid linking error
static const WCHAR* FONT_NAME = L"Arial";

/// String to display in front of timer value
const wstring TIMER_TEXT = L"Time Left: ";

/// Size of text being written on screen, static to avoid link errors
static const int FONT_SIZE = 20;

/// The point where the display timer is drawn from
const PointF TIMER_LOCATION(-600, 10);

CDisplayTimer::CDisplayTimer(CGame* game, double duration) : CTimer(game, duration)
{
	Start();
}


/**
 * Draws this timer
 * \param graphics The graphics device being drawn on
 */
void CDisplayTimer::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(FONT_NAME);
	Gdiplus::Font font(&fontFamily, FONT_SIZE);
	SolidBrush blackPen(Color::Black);

	wostringstream oss;
	oss << fixed << setprecision(2) << GetRemainingTime() << endl;
	wstring remainingTime =  TIMER_TEXT + oss.str();
	graphics->DrawString(remainingTime.c_str(), -1, &font, TIMER_LOCATION, &blackPen);
}

/**
 * Updates the timer
 * \param elapsed The time that has passed since update was last called
 */
void CDisplayTimer::Update(double elapsed)
{
	CTimer::Update(elapsed);
	if (IsTimeUp())
	{
		GetGame()->SetGameOver(true);
	}
}



