/**
 * \file UMLInheritance.h
 *
 *
 * This class represents an inheritance component of a UMLPiece 
 */

#pragma once
#include "UMLComponent.h"

/**
 * Class that represents an inheritance relationship of a UMLPiece
 */
class CUMLInheritance :	public CUMLComponent
{
public:
	/// Setter for mBase
	/// \param base The new value of mBase
	void SetBase(std::wstring base) { mBase = base; }

	/// Getter for mBase
	/// \returns The base class of this object
	std::wstring GetBase() { return mBase; }

	/// Setter for mDerived
	/// \param derived The new value of mDerived
	void SetDerived(std::wstring derived) { mDerived = derived; }

	/// Getter for mDerived
	/// \returns The derived class of this object
	std::wstring GetDerived() { return mDerived; }

	/// Setter for mDirection
	/// \param direction The new value of mDirection
	void SetDirection(std::wstring direction) { mDirection = direction; }

	/// Getter for mDirection
	/// \returns The direction of this object
	std::wstring GetDirection() { return mDirection; }

private:
	std::wstring mBase; ///< The UML base class component
	std::wstring mDerived; ///< The UML derived class component
	std::wstring mDirection; ///< The UML inheritance direction component
};
