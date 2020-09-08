/**
 * \file EndScreen.h
 *
 *
 * Class that describes the end screen of the game
 */

#pragma once
#include "GameObject.h"
#include <string>

/**
 * Class that displays results of game
 */
class CEndScreen : public CGameObject
{
public:
	CEndScreen(CGame* game);

	void SetFinalScore(int correct, int missed, int unfair);
	
	/// Getter for mFinalScore
	/// \returns The final score value of the game
	int GetFinalScore() { return mFinalScore; }

	/// Draws this GameObject
	/// \param graphics The graphics device this object is being drawn on
	virtual void Draw(Gdiplus::Graphics* graphics);

	/// Accepts a GameObject visitor
	/// \param visitor A pointer to the visitor currently visiting this object
	virtual void Accept(CGameObjectVisitor* visitor) override {}

	/// Updates this EndScreen object
	/// \param elapsed The amount of time that has passed since Update was last called on this object
	virtual void Update(double elapsed) {}


private:
	void DisplayRank();
	int mFinalScore = 0; ///< The calculated final score achieved in the game, defaults to 0
	std::wstring mRankText = L""; ///< The ranking text to be displayed on the screen
	std::wstring mDescription = L""; ///< Description of ranking text to be displayed on the screen
};

