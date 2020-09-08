/**
 * \file GameObject.h
 *
 *
 * Class that implements a GameObject
 *
 *
 */

#pragma once

#include "GameObjectVisitor.h"

class CGame;


/**
 * GameObject class to represent various game objects
 */

class CGameObject
{
public:

	/// Creates all objects in the game
	CGameObject(CGame* game);

	/// Default constructor (disabled)
	CGameObject() = delete;

	/// Copy constructor (disabled)
	CGameObject(const CGameObject&) = delete;

	/** The X location of the item
	 * \returns X location in pixels
	 */
	double GetX() const { return mX; }

	/** The Y location of the item
	 * \returns Y location in pixels
	 */
	double GetY() const { return mY; }

	/// Set the object location
	/// \param x X location
	/// \param y Y location
	virtual void SetLocation(double x, double y) { mX = x; mY = y; }

	/// Set the object dimensions
	/// \param wid Width of the game in virtual pixels
	/// \param hit Height of the game in virtual pixels
	virtual void SetDimensions(double wid, double hit) { mWidth = wid; mHeight = hit; }

	/** The Width of the item
	 * \returns double of Width
	 */
	double GetWidth() const { return mWidth; }

	/** The height of the item
	 * \return double of height
	 */
	double GetHeight() const { return mHeight; }

	virtual bool HitTest(int x, int y);

	/// Draw this GameObject on a graphics device
	/// \param graphics The graphics device this object is being drawn on
	virtual void Draw(Gdiplus::Graphics* graphics) {};

	/// Accepts a GameObjectVisitor
	/// \param visitor The visitor visiting this object
	virtual void Accept(CGameObjectVisitor* visitor) {};


	/// update time counter
	/// \param elapsed Time that has elapsed since Update was last called
	virtual void Update(double elapsed) {}

	/// Get the game this item is in
	/// \returns A pointer to the game this object is in
	CGame* GetGame() const { return mGame; }

	/// Gets if this object is marked for deletion
	/// \returns True if this object is currently marked for deletion
	virtual bool IsMarkedForDelete() { return mMarkedForDelete; }

	/// Setter marked for delete
	/// \param markDelete The new value for mMakedForDelete
	virtual void MarkForDelete(bool markDelete) { mMarkedForDelete = markDelete; }

private:

	//GameObject location and center of object
	double mX = 0; ///< X location of object
	double mY = 0; ///< Y location of object

	//GameObject dimensions
	double mWidth = 0; ///< Width of object
	double mHeight = 0; ///< Height of object

	/// The Game for this object
	CGame* mGame = nullptr;

	bool mHit = false; ///< Tracks if this object has been hit by a pen or not

	bool mMarkedForDelete = false; ///< Tracks if this object needs to be deleted
};

