/**
 * \file UmlVisitor.h
 *
 *
 * Visits UMLPiece GameObjects
 */


#pragma once
#include "GameObjectVisitor.h"
#include <string>

class CUMLPiece;

 /**
  * class implementing uml visitor visitor
  */
class CUmlVisitor : public CGameObjectVisitor
{
public:

	/// visit UML object
	/// \param piece
	void CUmlVisitor::VisitUMLPiece(CUMLPiece* piece);

	/// Resets the visitor after a uml piece was hit
	void Reset() { mIsUml = false; mPiece = nullptr;}

	/// Reports whether Uml was hit
	/// \return bool 
	bool IsUML() { return mIsUml; }

	/// Report if UML was bad
	/// \return bool
	bool IsBad() { return mBad; }

	bool TryHit(int x, int y);

private:
	bool mIsUml = false; ///< Bool for if target is UMLPiece
	bool mBad = false; ///< Bool for if the piece was bad
	CUMLPiece* mPiece = nullptr; ///< Pointer to the piece this visitor has visited, if any
};

