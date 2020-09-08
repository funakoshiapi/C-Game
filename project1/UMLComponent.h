/**
 * \file UMLComponent.h
 *
 * This parent class describes a single part of a UMLPiece
 */


#pragma once
#include <string>

/**
 * Class that describes one component of a CUMLPiece object
 */
class CUMLComponent
{
public:
	/// Setter for mBad
	/// \param bad The new value of mBad
	void SetBad(std::wstring bad) { mBad = bad; }

	/// Getter for mBad
	/// \returns The reason, if any exists, why this object is bad
	std::wstring GetBad() { return mBad; }

private:
	std::wstring mBad; ///< The reason, if any exists, of why the name is bad
};

