/**
 * 
 *
 * Class that represents a countdown timer on screen
 */

#pragma once
#include "Timer.h"
#include "Game.h"


/**
 * Class that represents a timer that counts down visually on screen
 */
class CDisplayTimer : public CTimer
{
public:
	/// Display timer constructor
	/// \param game Game this display timer is part of
	/// \param duration How long the timer lasts for
	CDisplayTimer(CGame* game, double duration);

	/// default constructor disabled
	CDisplayTimer() = delete;

	/// default copy constructor disabled
	CDisplayTimer(const CDisplayTimer&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics);

	virtual void Update(double elapsed);

	/// Accepts a GameObject visitor
	/// \param visitor The visitor that is visiting this DisplayTimer
	virtual void Accept(CGameObjectVisitor* visitor) override {}
};

