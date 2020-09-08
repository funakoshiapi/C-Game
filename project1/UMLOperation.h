/**
 * \file UMLOperation.h
 *
 *
 * This class represents an operation component of a UMLPiece
 */


#pragma once
#include "UMLComponent.h"

/**
 * Class that represents an operation of a UMLPiece
 */
class CUMLOperation : public CUMLComponent
{
public:
	/// Setter for mOperation
	/// \param operation The new value of mOperation
	void SetOperation(std::wstring operation) { mOperation = operation; }

	/// Getter for mOperation
	/// \returns The operation of this object
	std::wstring GetOperation() { return mOperation; }

private:
	std::wstring mOperation; ///< The UML operation component
};

