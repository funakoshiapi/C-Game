/**
 * \file Player.h
 *
 *
 */


#include "pch.h"
#include "Player.h"
#include "RedPen.h"
#include "Game.h"
#include <string>


using namespace Gdiplus;
using namespace std;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/// constant pen reload duration
const double ReloadDuration = 1.0;

/// Filepath to image of Harold
const WCHAR* HAROLD_FILENAME = L"images/images/harold.png";

const WCHAR* HAROLD_ERROR = L"Failed to open images/harold.png";

CPlayer::CPlayer(CGame* game) : CGameObject(game)
{
	mPlayerImage = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(HAROLD_FILENAME));
	if (mPlayerImage->GetLastStatus() != Ok)
	{
		AfxMessageBox(HAROLD_ERROR);
	}
	else
	{
		SetLocation(0, double(double(CGame::GetHeight()) - mPlayerImage->GetHeight() / 2.0f));
		MakeAPen();
	}
}

void CPlayer::OnMouseMove(double mouseX, double mouseY)
{
	if (mouseY < GetY())
	{
		/// Did mouseX - GetX() instead of the other way around is to
		/// make the player rotate to the direction of mouse movement
		mAngle = atan2(GetY() - mouseY, mouseX - GetX()) - PI / 2;

		if (mAngle > PI / 2)
			mAngle = PI / 2;
		else if (mAngle < -PI / 2)
			mAngle = -PI / 2;
		mPenOnHand->OnMouseMove(mAngle);
	}
}

void CPlayer::OnLeftClick(double mouseX, double mouseY)
{
	mPenOnHand->FirePen(mouseX, mouseY);
	if (mIsPenOnHand)
	{
		mPenTimer->Start();
	}
	mIsPenOnHand = false;
}

void CPlayer::Draw(Gdiplus::Graphics* graphics)
{
	float wid = (float)mPlayerImage->GetWidth();
	float hit = (float)mPlayerImage->GetHeight();

	auto state = graphics->Save();
	graphics->TranslateTransform((float)GetX(), (float)GetY());
	graphics->RotateTransform((float)(-mAngle * RtoD));
	graphics->DrawImage(mPlayerImage.get(), -wid / 2, -hit / 2, wid, hit);
	graphics->Restore(state);
}

/**
 * Creates a new RedPen GameObject
 */
void CPlayer::MakeAPen()
{
	auto game = GetGame();
	mPenOnHand = make_shared<CRedPen>(game, GetX(), GetY());
	game->Add(mPenOnHand);
	mPenOnHand->OnMouseMove(mAngle);
	mIsPenOnHand = true;

	mPenTimer = make_shared<CTimer>(game, ReloadDuration);
	game->Add(mPenTimer);
}

/**
 * Marks a pen for destruction
 */
void CPlayer::DestroyPen()
{
	mPenOnHand->MarkForDelete(true);
}


