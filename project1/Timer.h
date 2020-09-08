/**
 * \file Timer.h
 *
 *
 * Class for a general purpose timer
 */

#pragma once
#include "GameObject.h"
#include "Game.h"
#include <ctime>

/**
 * Class that represents a timer for an event
 */
class CTimer : public CGameObject
{
public:
	/// Timer constructor
	/// \param game The game this Timer belongs to
	/// \param duration The duration of this timer
	CTimer(CGame* game, double duration): CGameObject(game), mTimeTotal(duration), mTimeLeft(duration) {}

	/// default constructor disabled
	CTimer() = delete;

	/// default copy constructor disabled
	CTimer(const CTimer&) = delete;

	virtual void Update(double elapsed);

	/// Accepts a GameObject Visitor
	/// \param visitor A pointer to the visitor currently visiting this timer
	virtual void Accept(CGameObjectVisitor* visitor) override {}

	/// Draws this timer, empty as there is nothing to draw
	/// \param graphics Pointer to the graphics device that would be drawn on
	virtual void Draw(Gdiplus::Graphics* graphics) {};

	/// Prepares the timer before it begins
	/// \param time How long the timer should run for
	virtual void SetUp(double time)
	{
		mTimeLeft = time;
		mTimeTotal = time;
	}

	/// Get remaining time
	/// \returns The amount of time left for the timer in seconds
	virtual double GetRemainingTime() { return mTimeLeft; }

	/// Checks if the timer has ended
	/// \returns True if the timer has ended
	virtual bool IsTimeUp() { return mTimeLeft == 0.0; }

	/// Starts the timer
	virtual void Start()
	{
		mIsStart = true;
		mStart = clock();
	}

private:
	double mTimeTotal = 0; ///< Total time that has elapsed
	double mTimeLeft = 0; ///< Time left before timer runs out
	bool mIsStart = false; ///< Indicates if timer has started or not
	clock_t mStart = clock(); ///< Clock used for tracking elapsed time
};
