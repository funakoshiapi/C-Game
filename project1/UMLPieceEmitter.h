/**
 * \file UMLPieceEmitter.h
 *
 *
 * Class that creates and emits new UMLPieces into the game area
 */

#pragma once
#include "XMLReader.h"
#include "UMLClass.h"
#include "UMLInherited.h"
#include "Game.h"

/**
 * Class that emits UMLPieces
 */
class CUMLPieceEmitter
{
public:
	CUMLPieceEmitter(CGame* game);

	std::shared_ptr<CUMLPiece> EmitPiece();

	/// Sends the time difference based on number emitted
	/// \return int value to change the emit interval by
	int SpeedChange() { return (mTotalEmitted / 5); }

private:
	void CreateDisplay(std::shared_ptr<CUMLDisplay> display, bool name, int attributes, int operations);

	void IncrementEmitted();

	std::shared_ptr<CUMLPiece> EmitInherited();

	std::vector<std::shared_ptr<CUMLName>> mNames; ///< Vector containing valid class names
	std::vector<std::shared_ptr<CUMLName>> mBadNames; ///< Vector containing invalid class names with reasons

	std::vector<std::shared_ptr<CUMLAttribute>> mAttributes; ///< Vector containing valid class attributes
	std::vector<std::shared_ptr<CUMLAttribute>> mBadAttributes; ///< Vector containing invalid class attributes with reasons

	std::vector<std::shared_ptr<CUMLOperation>> mOperations; ///< Vector containing valid class operations
	std::vector<std::shared_ptr<CUMLOperation>> mBadOperations; ///< Vector containing invalid class operations with reasons

	std::vector<std::shared_ptr<CUMLInheritance>> mInherits; ///< Vector containing valid inherits
	std::vector<std::shared_ptr<CUMLInheritance>> mBadInherits; ///< Vector containing invalid inherits with reasons

	CGame* mGame = nullptr; ///< The game this emitter is part of

	int mHandicap = 5; ///< Higher value makes game easier (less good UML and inheritance)
	int mTotalEmitted = 0; ///< The total number of UMLPieces that have been emitted this game
	int mPieceSpeed = 50; ///< Speed that pieces will move after being emitted
};

