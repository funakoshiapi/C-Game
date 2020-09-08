/**
 * \file Player.h
 *
 *
 * Class that represents the player, Harold
 */


#pragma once
#include <memory>
#include "GameObject.h"
#include "Timer.h"


class CRedPen;


 /**
  * Class that represents Harold, the player
  */
class CPlayer : public CGameObject
{
	public:
		/// CPlayer constructor
		/// \param game The game this object belongs to
		CPlayer(CGame* game);

		/// Default constructor disabled
		CPlayer() = delete;

		/// default copy constructor disabled
		CPlayer(const CPlayer&) = delete;

		/// Draws this gameobject
		/// \param graphics The graphics device this object is being drawn on
		virtual void Draw(Gdiplus::Graphics* graphics) override;

		void MakeAPen();

		void DestroyPen();

		/// Checks if the player should get a new pen
		/// \returns True if it is time to reload a pen
		bool ReloadPen() { return mPenTimer->IsTimeUp(); }

		/// Mouse movement event handler
		/// \param mouseX X location of the mouse in virtual pixels
		/// \param mouseY Y location of the mouse in virtual pixels
		void OnMouseMove(double mouseX, double mouseY);

		/// Left Click event handler, fires pen
		/// \param mouseX X location of mouse in virtual pixels
		/// \param mouseY Y location of mouse in vitual pixels
		void OnLeftClick(double mouseX, double mouseY);

		/// Accepts a GameObjectVisitor
		/// \param visitor The visitor visiting this object
		virtual void Accept(CGameObjectVisitor* visitor) { visitor->VisitPlayer(this); };

		/// Updates the Player
		/// \param elapsed The amount of time in seconds since the last call to Update
		virtual void Update(double elapsed) {};

	private:
		/// player image
		std::unique_ptr<Gdiplus::Bitmap> mPlayerImage = nullptr;
		
		/// pen handler
		std::shared_ptr<CRedPen> mPenOnHand = nullptr;
		
		/// Is pen on hand
		bool mIsPenOnHand;
		
		/// angle of rotation
		double mAngle = 0.0;
		
		/// pen timer
		std::shared_ptr<CTimer>	 mPenTimer = nullptr;

};
















