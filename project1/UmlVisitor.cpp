/**
 * \file UmlVisitor.cpp
 *
 */

#include "pch.h"
#include "UmlVisitor.h"
#include "UMLPiece.h"

using namespace std;


/**
 * Attempts to hit UML at a specific point
 * \param x X location of the desired point in virtual pixels
 * \param y Y location of the desired point in virtual pixels
 * \returns True if UML was hit at the point described by the arguments
 */
bool CUmlVisitor::TryHit(int x, int y)
{
	if (mPiece->HitTest(x, y) && !mPiece->GetWasHit())
	{
		mPiece->MarkHit(true);
		return true;
	}
	return false;
}

void CUmlVisitor::VisitUMLPiece(CUMLPiece* piece)
{
	mIsUml = true;
	mPiece = piece;
	mBad = (L"" != mPiece->GetBad());
}
