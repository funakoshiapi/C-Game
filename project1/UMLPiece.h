/**
 * \file UMLPiece.h
 *
 *
 * Class that describes a single class of UML
 */

#pragma once
#include "GameObject.h"
#include "UmlVisitor.h"
#include <vector>
#include <string>
#include <memory>
#include "Timer.h"


/**
 * Class that descibes a single UML object on screen
 */
class CUMLPiece : public CGameObject
{
public:

	CUMLPiece(CGame* game, double x, double y, int speed);

	/// Setter for mBad
	/// \param bad The new value for mBad
	void SetBad(std::wstring bad) { mBad = bad; }

	/// Getter for mBad
	/// \returns The current value of mBad
	std::wstring GetBad() { return mBad; }

	/// Getter for HitStatus
	/// \returns the value of mWasHit
	bool GetWasHit() { return mWasHit; }

	void MarkHit(bool status);

	/// Draw this UMLPiece, empty as each derived class has its own implementation
	/// \param graphics The graphics device this object is being drawn on
	virtual void Draw(Gdiplus::Graphics* graphics) {}

	virtual void Update(double elapsed);

	/// Accepts a GameObject visitor
	/// \param visitor Pointer to the visitor currently visiting this object
	virtual void Accept(CGameObjectVisitor* visitor) override { visitor->VisitUMLPiece(this); }

	bool LeaveScreenCheck();

	/// Hit Test override for UMLPiece
	/// Since each derived class has its own way of handling hit detection, it's pure virtual
	/// \param x X position of hit
	/// \param y Y position of hit
	/// \returns True if the object was hit at the point described by the function arguments
	bool HitTest(int x, int y) = 0;

private:
	std::wstring mBad = L""; ///< The reason, if any, why this UMLPiece is bad
	double mXDirection; ///< The X direction this UMLPiece is moving
	double mYDirection; ///< The Y direction this UMLPiece is moving
	int mSpeed; ///< The speed at which this UMLPiece is moving
	bool mWasHit = false; ///< Indicates if this UMLPiece object was hit or not
	std::shared_ptr<CTimer> mHitUMLTimer = nullptr; ///< Timer that counts down after this UMLPiece object has been hit

protected:
	virtual void DisplayHitMessage(Gdiplus::Graphics* graphics, double& x, double& y);
};

