/**
 * \file GameObject.cpp
 *
 */

#include "pch.h"
#include "GameObject.h"

 /** Constructor
  * \param game The game this item is a member of
  */
CGameObject::CGameObject(CGame* game)
{
	mGame = game;
}


/**
 *  Test to see if we hit this GameObject.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CGameObject::HitTest(int x, int y)
{
	// This function currently relies on object location being the center around
	// which it is drawn.
	double wid = GetWidth();
	double hit = GetHeight();

	// Make x and y relative to the top-left corner of the gameobject.
	// Subtracting the center makes x, y relative to the center of 
	// the gameobject. Adding half the size makes x, y relative to the top 
	// corner of the gameobject.
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the gameobject
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the gameobject
		return false;
	}
	else {
		return true;
	}
}