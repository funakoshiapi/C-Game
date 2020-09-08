/**
 * \file XMLReader.h
 *
 * Class that reads the XML data
 * for the UMLPieces at game start
 */

#pragma once
#include <memory>
#include "XmlNode.h"
#include <string>
#include <vector>
#include "UMLName.h"
#include "UMLAttribute.h"
#include "UMLOperation.h"
#include "UMLInheritance.h"

/**
 * Class that reads the UML's XML data
 */
class CXMLReader
{
public:
	void Load();

	
	///Getter for valid names
	///\returns Vector of valid names
	std::vector<std::shared_ptr<CUMLName>> GetNames() { return mNames; };

	///Getter for invalid names
	///\returns Vector of invalid names
	std::vector<std::shared_ptr<CUMLName>> GetBadNames() { return mBadNames; };

	///Getter for valid attributes
	///\returns Vector of valid attributes
	std::vector<std::shared_ptr<CUMLAttribute>> GetAttributes() { return mAttributes; };

	/// Getter for invalid attributes
	///\returns Vector of invalid attributes
	std::vector<std::shared_ptr<CUMLAttribute>> GetBadAttributes() { return mBadAttributes; };

	/// Getter for valid operations
	///\returns Vector of valid operations
	std::vector<std::shared_ptr<CUMLOperation>> GetOperations() { return mOperations; };

	/// Getter for invalid operations
	///\returns Vector of invalid operations
	std::vector<std::shared_ptr<CUMLOperation>> GetBadOperations() { return mBadOperations; };

	/// Getter for valid inherits
	///\returns Vector of valid inherits
	std::vector<std::shared_ptr<CUMLInheritance>> GetInherits() { return mInherits; };

	/// Getter for invalid inherits
	///\returns Vector of invalid inherits
	std::vector<std::shared_ptr<CUMLInheritance>> GetBadInherits() { return mBadInherits; };

private:
	void LoadClasses(const std::shared_ptr<xmlnode::CXmlNode>& parentNode);
	void LoadInheritance(const std::shared_ptr<xmlnode::CXmlNode>& parentNode);

	std::vector<std::shared_ptr<CUMLName>> mNames; ///< Vector containing valid class names
	std::vector<std::shared_ptr<CUMLName>> mBadNames; ///< Vector containing invalid class names with reasons

	std::vector<std::shared_ptr<CUMLAttribute>> mAttributes; ///< Vector containing valid class attributes
	std::vector<std::shared_ptr<CUMLAttribute>> mBadAttributes; ///< Vector containing invalid class attributes with reasons

	std::vector<std::shared_ptr<CUMLOperation>> mOperations; ///< Vector containing valid class operations
	std::vector<std::shared_ptr<CUMLOperation>> mBadOperations; ///< Vector containing invalid class operations with reasons

	std::vector<std::shared_ptr<CUMLInheritance>> mInherits; ///< Vector containing valid inherits
	std::vector<std::shared_ptr<CUMLInheritance>> mBadInherits; ///< Vector containing invalid inherits with reasons
};

