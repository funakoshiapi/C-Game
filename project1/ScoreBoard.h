/**
 * \file ScoreBoard.h
 *
 * Class that represents a ScoreBoard object 
 */


#pragma once
#include "GameObject.h"

/**
 * A class implementing score board
 */
class CScoreBoard : public CGameObject
{
	public:
		/// scroreboard constructor
		/// \param game
		CScoreBoard(CGame* game);

		/// default constructor disabled
		CScoreBoard() = delete;

		/// default copy constructor disabled
		CScoreBoard(const CScoreBoard&) = delete;

		/// Accepts a Gameobject visitor
		/// \param visitor A pointer to the visitor currently visiting this object
		virtual void Accept(CGameObjectVisitor* visitor) override { visitor->VisitScoreBoard(this); }

		virtual void Draw(Gdiplus::Graphics* graphics);

		/// Updates the scoreboard
		/// \param elapsed The time that has passed since Update() was last called
		virtual void Update(double elapsed) {}


		/// increment correct score
		void IncrementCorrectScore() { mCorrect++; }

		/// increment unfair score
		void IncrementUnfairScore() { mUnfair++; }

		/// increment missed score
		void IncrementMissedScore() { mMissed++; }

		/// Getter for mCorrect
		/// \returns Number of correct UML hits
		int GetCorrect() { return mCorrect; }

		/// Getter for mUnfair
		/// \returns Number of unfair UML hits
		int GetUnfair() { return mUnfair; }

		/// Getter for mMissed
		/// \returns Number of bad UML missed
		int GetMissed() { return mMissed; }

	private:
		int mCorrect = 0; ///< Number of correct UML scored during the game
		int mUnfair = 0; ///< Number of unfair UML scored during the game
		int mMissed = 0; ///< Number of missed UML scored during the game
};

