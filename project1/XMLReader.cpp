/**
 * \file XMLReader.cpp
 *
 */

#include "pch.h"
#include "XMLReader.h"

using namespace std;
using namespace xmlnode;

/// Name of file containing UML information
const wstring FILENAME = L"images/data/uml.xml";

/**
 * Loads the UML Data from the XML file
 */
void CXMLReader::Load()
{
	try
	{
		// Open the document to read
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(FILENAME);

		// Once we know it is open, read data

		//
		// Traverse the children of the root
		// node of the XML document in memory!!!!
		//
		for (auto node : root->GetChildren())
		{
			// Loads the class data
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"class")
			{
				LoadClasses(node);
			}

			// Loads the inheritance data
			else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"inheritance")
			{
				LoadInheritance(node);
			}

		}

	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}

/**
 * Loads UML class information from XML file
 * \param parentNode The "class" node in the XML file
 */
void CXMLReader::LoadClasses(const shared_ptr<CXmlNode>& parentNode)
{
	for (auto node : parentNode->GetChildren())
	{
		// Get the info on if name is bad
		wstring bad = node->GetAttributeValue(L"bad", L"");

		// Loads names
		if (node->GetType() == NODE_ELEMENT && node->GetName() == L"name")
		{
			// Create new CUMLName instance and set bad value
			shared_ptr<CUMLName> new_name = make_shared<CUMLName>();
			new_name->SetBad(bad);

			// Name is good
			if (bad == L"")
			{
				new_name->SetName(node->GetChild(0)->GetValue());
				mNames.push_back(new_name);
			}

			// Name is bad
			else
			{			

				// General case
				if (node->GetNumChildren() == 1)
				{
					new_name->SetName(node->GetChild(0)->GetValue());
				}

				// Edge case of missing name
				else
				{
					new_name->SetName(L"");
				}

				// Pushback bad name to vector
				mBadNames.push_back(new_name);
			}

			continue;
		}

		// Loads attributes
		if (node->GetType() == NODE_ELEMENT && node->GetName() == L"attribute")
		{
			// Create new CUMLAttribute instance and set values
			shared_ptr<CUMLAttribute> new_attribute = make_shared<CUMLAttribute>();
			new_attribute->SetBad(bad);
			new_attribute->SetAttribute(node->GetChild(0)->GetValue());

			// Attribute is good
			if (bad == L"")
			{
				mAttributes.push_back(new_attribute);
			}

			// Attribute is bad
			else
			{
				mBadAttributes.push_back(new_attribute);
			}

			continue;
		}

		// Loads operations
		if (node->GetType() == NODE_ELEMENT && node->GetName() == L"operation")
		{
			// Create new CUMLOperation instance and set values
			shared_ptr<CUMLOperation> new_operation = make_shared<CUMLOperation>();
			new_operation->SetBad(bad);
			new_operation->SetOperation(node->GetChild(0)->GetValue());

			// Operation is good
			if (bad == L"")
			{
				mOperations.push_back(new_operation);
			}

			// Operation is bad
			else
			{
				mBadOperations.push_back(new_operation);
			}

			continue;
		}
	}
}

/**
 * Loads UML inheritance information from XML file
 * \param parentNode The "inheritance" node in the XML file
 */
void CXMLReader::LoadInheritance(const shared_ptr<CXmlNode>& parentNode)
{
	for (auto node : parentNode->GetChildren())
	{
		// Get the info on if name is bad
		wstring bad = node->GetAttributeValue(L"bad", L"");

		// Loads inherits
		if (node->GetType() == NODE_ELEMENT && node->GetName() == L"inherit")
		{
			// Create new CUMLInheritance instance and set values
			shared_ptr<CUMLInheritance> new_inherit = make_shared<CUMLInheritance>();
			new_inherit->SetBad(bad);
			new_inherit->SetBase(node->GetAttributeValue(L"base", L""));
			new_inherit->SetDerived(node->GetAttributeValue(L"derived", L""));
			new_inherit->SetDirection(node->GetAttributeValue(L"direction", L"up"));

			// Operation is good
			if (bad == L"")
			{
				// Pushback valid inherit
				mInherits.push_back(new_inherit);
			}

			// Operation is bad
			else
			{
				// Pushback invalid inherit
				mBadInherits.push_back(new_inherit);
			}

			continue;
		}
	}
}
