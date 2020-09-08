/**
 * \file RedPen.h
 *
 *
 * Class that represents a pen
 */


#pragma once
#include "GameObject.h"
#include "Game.h"
#include <memory>

/// Mathematical value of pi rounded to nine places
const double PI = 3.141592653;

/// X offset in virtual pixels
static const double X_OFFSET = 29.0;

/// Y offset in virtual pixels
static const double Y_OFFSET = 54.0;

/// Speed that pen moves in virutal pixels/second
static const double SPEED = 1000.0;

 /**
  * Class that implements a RedPen GameObject
  */
class CRedPen : public CGameObject
{
public:
	CRedPen(CGame* game, double xLocation, double yLocation);

	/// Default constructor (disabled)
	CRedPen() = delete;

	/// default copy constructor disabled
	CRedPen(const CRedPen&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics) override;

	/// Set the angle of the pen
	/// \param angle The angle between the pen and the mouse
	void SetAngle(double angle) { mAngleOfMovement = angle; mAngleOfRotation = angle - mAngleOffset; }

	void FirePen(double xDirection, double yDirection);

	virtual void Update(double elapsed) override;
	
	/// Follow the player's hand as it moves and rotates
	void TrackHand();
	
	void OnMouseMove(double angle);

	/// set location of the red pen
	/// \param x Desired X location of pen in virtual pixels
	/// \param y Desired Y location of pen in virtual pixels
	void SetLocation(double x, double y) override;

	/// Accepts a visitor
	/// \param visitor The visitor currently visiting this object
	virtual void Accept(CGameObjectVisitor* visitor) override {}

private:
	/// pen image
	std::shared_ptr<Gdiplus::Bitmap> mPenImage = nullptr;

	/// angle of rotation
	double mAngleOfRotation = -PI / 2;

	///angle offset
	double mAngleOffset = PI/2;

	/// angle of movement
	double mAngleOfMovement = 0.0;

	/// angle of pen after being fired
	double mAngleOnAir = 0.0;

	/// bool to dictate rotation
	bool mOnHand = true;

	/// initial load x location
	double mLoadX = 0.0;

	/// initial load y location
	double mLoadY = 0.0;

	/// the x center of the player to be used as origin for pen
	double mXOrigin = 0.0;

	/// the y center of the player to be used as origin for pen
	double mYOrigin = 0.0;

	/// offset x from player image center
	const double mXOffset = X_OFFSET;

	/// offset y from player image center
	const double mYOffset = Y_OFFSET;

	/// x direction
	double mXDirection = 0.0;

	/// y direction
	double mYDirection = 0.0;

	/// speed
	double mSpeed = SPEED;
};
















