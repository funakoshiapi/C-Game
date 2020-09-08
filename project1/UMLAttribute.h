/**
 * \file UMLAttribute.h
 *
 *
 * This class represents an attribute component of a UMLPiece
 */

#pragma once
#include "UMLComponent.h"

/**
 * Class that represents an attribute of a UMLPiece
 */
class CUMLAttribute : public CUMLComponent
{
public:
	/// Setter for mAttribute
	/// \param attribute The new value of mAttribute
	void SetAttribute(std::wstring attribute) { mAttribute = attribute; }

	/// Getter for mAttribute
	/// \returns The attribute of this object
	std::wstring GetAttribute() { return mAttribute; }

private:
	std::wstring mAttribute; ///< The UML attribute component
};

