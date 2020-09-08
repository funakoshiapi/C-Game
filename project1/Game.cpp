/**
 * \file Game.cpp
 *
 */

#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "RedPen.h"
#include "ScoreBoard.h"
#include "ScoreBoard.h"
#include "DisplayTimer.h"
#include "EndScreen.h"
#include "UMLPieceEmitter.h"
#include <cstdlib>
#include "UmlVisitor.h"
#include <vector>
#include <algorithm>

using namespace std;
using namespace Gdiplus;

/// Time between UMLPiece emissions
const double EMITTER_INTERVAL = 5;

/// game duration
const double GameDuration = 60.0;

/// Path to pen's image file
const WCHAR* PEN_FILENAME = L"images/images/redpen.png";

/// Error for if pen file did not open correctly
const WCHAR* PEN_ERROR = L"Failed to open images/images/redpen.png";

/**
 * Game constructor
 */
CGame::CGame()
{
	//can be refactored-for testing purposes
	OnLaunch();
}

CGame::~CGame()
{
}

void CGame::OnLaunch()
{
	// Seed random for the game using time
	srand(unsigned(time(NULL)));

	// Load pen image
	mPenImage = std::shared_ptr<Bitmap>(Bitmap::FromFile(PEN_FILENAME));
	if (mPenImage->GetLastStatus() != Ok)
	{
		AfxMessageBox(PEN_ERROR);
	}

	// Create the scoreboard
	mScoreBoard = make_shared<CScoreBoard>(this);
	//Add(scoreBoard);

	// Create the player
	mPlayer = make_shared<CPlayer>(this);
	//Add(mPlayer);

	// Create the countdown timer
	auto DisplayTimer = make_shared<CDisplayTimer>(this, GameDuration);
	Add(DisplayTimer);

	// Create emitter
	mEmitter = make_shared<CUMLPieceEmitter>(this);

}

/**
 * Draw the game area
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of the client window
 * \param height Height of the client window
 */
void CGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXOffset = width / 2.0f;
	mYOffset = 0;
	if (height > Height * mScale) {
		mYOffset = (float)((height - Height * mScale) / 2);
	}

	graphics->TranslateTransform((Gdiplus::REAL)mXOffset, (Gdiplus::REAL)mYOffset);
	graphics->ScaleTransform((Gdiplus::REAL)mScale, (Gdiplus::REAL)mScale);

	// Draw all gameobjects
	for (auto gameObjects : mGameObjects)
	{
		gameObjects->Draw(graphics);
	}

	// Draw player and scoreboard last if the game has not yet been won
	if (!mGameOver)
	{
		mPlayer->Draw(graphics);
		mScoreBoard->Draw(graphics);
	}
}

/**
 * Add a game object to the game
 * \param gob New game object to add
 */
void CGame::Add(std::shared_ptr<CGameObject> gob)
{
	// Pushback as normal if empty
	if (mGameObjects.empty())
	{
		mGameObjects.push_back(gob);
	}

	// Else move scoreboard so it is always drawn last.
	else
	{
		auto lastObject = mGameObjects.back();
		mGameObjects.pop_back();
		mGameObjects.push_back(gob);
		mGameObjects.push_back(lastObject);
	}

}

void CGame::OnMouseMove(int x, int y)
{
	double mouseX = (x - mXOffset) / mScale;
	double mouseY = (y - mYOffset) / mScale;

	mPlayer->OnMouseMove(mouseX, mouseY);
}

void CGame::OnLeftClick(int x, int y)
{
	double mouseX = (x - mXOffset) / mScale;
	double mouseY = (y - mYOffset) / mScale;

	mPlayer->OnLeftClick(mouseX, mouseY);
}

void CGame::Accept(CGameObjectVisitor* visitor)
{
	for (auto gameObject : mGameObjects)
	{
		gameObject->Accept(visitor);
	}
}

/**
 * Check if the game has ended
 */
void CGame::CheckGameOver()
{
	if (mGameOver && !mEndScreenDisplayed)
	{
		mEndScreenDisplayed = true;

		auto theEnd = make_shared<CEndScreen>(this);

		theEnd->SetFinalScore(mScoreBoard->GetCorrect(), mScoreBoard->GetMissed(), mScoreBoard->GetUnfair());

		mGameObjects.clear();

		Add(theEnd);
	}
}

void CGame::UMLMissed()
{
	mScoreBoard->IncrementMissedScore();
}

/**
 * Adds a GameObject to the list of GameObjects to be destroyed at the end of the next update call.
 */
void CGame::PrepareDeleteQueue()
{
	// this solves the problem by basically copying a shared pointer
	// to the queue. The two shared ptrs know each other 
	for (auto gameobject : mGameObjects)
	{
		if (gameobject->IsMarkedForDelete())
		{
			mDeleteQueue.push_back(gameobject);
		}
	}

}


/**
 * Deletes all GameObjects that needed to be destroyed during the most recent Update call
 */
void CGame::ClearQueue()
{
	// Loops for every object that needs to be deleted
	for (unsigned i = 0; i < mDeleteQueue.size(); i++)
	{
		auto inGameObjects = std::find(mGameObjects.begin(), mGameObjects.end(), mDeleteQueue[i]);
		if (inGameObjects != mGameObjects.end())
		{
			mGameObjects.erase(inGameObjects);
		}
	}
	mDeleteQueue.clear();
}


/** Test an x,y click location to see if it clicked
* on some GameObject.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CGameObject> CGame::HitTest(int x, int y)
{
	for (auto i = mGameObjects.rbegin(); i != mGameObjects.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}
	return  nullptr;
}

void CGame::Update(double elapsed)
{
	if (!mGameOver)
	{
		mEmitterTime -= elapsed;


		// Emits a new UMLPiece if the emit time interval is over
		if (mEmitterTime <= 0)
		{
			Add(mEmitter->EmitPiece());

			int reduce = mEmitter->SpeedChange();
			mEmitterTime += EMITTER_INTERVAL - reduce;
			if (mEmitterTime < 1)
			{
				mEmitterTime = 1;
			}
		}

		if (mPlayer->ReloadPen()) {
			mPlayer->MakeAPen();
		}
	}

	// Do not do ADD or DELETE during looping, will cause crashing
	for (auto gameObjects : mGameObjects)
	{
		gameObjects->Update(elapsed);
	}

	PrepareDeleteQueue();
	ClearQueue();
}


/**
 * Detects whether a pen at a given position has hit a UML piece
 * \param pen A pointer to the pen may or may not have hit a UMLPiece
 */
void CGame::HitUml(CGameObject* pen)
{
	// Create an appropriate visitor
	CUmlVisitor umlVisitor;
	std::vector<std::shared_ptr<CGameObject> > hitUml;

	// Get pen coordinates
	double penX = pen->GetX();
	double penY = pen->GetY();

	// Loop  for every gameobject
	for (auto object : mGameObjects)
	{
		object->Accept(&umlVisitor);
		if (umlVisitor.IsUML())
		{
			// Check if pen hit UML
			if (umlVisitor.TryHit((int)penX, (int)penY))
			{
				// If pen hit UML, mark this pen and the UML for deletion
				pen->MarkForDelete(true);
				if (std::find(hitUml.begin(), hitUml.end(), object) ==
					hitUml.end())
				{
					hitUml.push_back(object);

					// Increment the appropriate score on the scoreboard
					if (umlVisitor.IsBad())
					{
						mScoreBoard->IncrementCorrectScore();
					}

					else
					{
						mScoreBoard->IncrementUnfairScore();
					}
				}
			}
			// Reset the visitor for the next visit
			umlVisitor.Reset();
		}
	}
}
