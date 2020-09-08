/**
 * \file UMLDisplay.h
 *
 *
 * Class that displays a single UML class
 */

#pragma once
#include <string>
#include <vector>

/**
 * Class that displays a UML object
 */
class CUMLDisplay
{
public:
	/// Setter for mName
	/// \param name The new value for mName
	void SetName(std::wstring name) { mName = name; }

	/// Getter for mName
	/// \returns The current vlaue of mName
	std::wstring GetName() { return mName; }

	/// Adds attribute to UMLPiece
	/// \param attribute The attribute being added
	void AddAttribute(std::wstring attribute) { mAttributes.push_back(attribute); }

	/// Adds operation to UMLPiece
	/// \param operation The operation being added
	void AddOperation(std::wstring operation) { mOperations.push_back(operation); }

	void Draw(Gdiplus::Graphics* graphics, double x, double y);

	void SetDimensions(Gdiplus::Graphics* graphics);

	/// Getter for mWidth
	/// \returns The width of the display
	double GetWidth() { return mWidth; }

	/// Getter for mHeight
	/// \returns The height of the display
	double GetHeight() { return mHeight; }

private:
	std::wstring mName; ///< The class name of this UMLPiece
	std::vector<std::wstring> mAttributes; ///< The attributes this UMLPiece has, if any
	std::vector<std::wstring> mOperations; ///< The operations this UMLPiece has, if any
	double mHeight = 0; ///< Total height of UML in virtual pixels
	double mWidth = 0; ///< Maximum width of UML in virtual pixels
	double mNameHeight; ///< Height of name in virtual pixels
	double mNameWidth; ///< Width of name in virtual pixels
	double mAttributeHeight; ///< Height of Attributes in virutal pixels
	double mAttributeWidth; ///< Width of Attributes in virtual pixels
	double mOperationHeight; ///< Height of Operations in virtual pixels
	double mOperationWidth; ///< Width of Operations in virtual pixels
};

