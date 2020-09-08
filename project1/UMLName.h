/**
 * \file UMLName.h
 *

 *
 * This class represents a name component of a UMLPiece
 */

#pragma once
#include "UMLComponent.h"

/**
 * Class that represents a name of a UMLPiece
 */
class CUMLName : public CUMLComponent
{
public:
	/// Setter for mName
	/// \param name The new value of mName
	void SetName(std::wstring name) { mName = name; }

	/// Getter for mName
	/// \returns The name of this object
	std::wstring GetName() { return mName; }

private:
	std::wstring mName; ///< The UML name component
};

