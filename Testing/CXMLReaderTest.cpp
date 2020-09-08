#include "pch.h"
#include "CppUnitTest.h"
#include "XMLReader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CXMLReaderTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCXMLReaderConstructor)
		{
			CXMLReader reader;
		}

		TEST_METHOD(TestCXMLReaderLoadAll)
		{
			CXMLReader reader;
			reader.Load();

			TestNames(reader);
			TestAttributes(reader);
			TestOperations(reader);
			TestInherits(reader);

		}

		TEST_METHOD(TestCXMLReaderLoadNames)
		{
			CXMLReader reader;
			reader.Load();

			TestNames(reader);
		}

		TEST_METHOD(TestCXMLReaderLoadAttributes)
		{
			CXMLReader reader;
			reader.Load();

			TestAttributes(reader);
		}

		TEST_METHOD(TestCXMLReaderLoadOperations)
		{
			CXMLReader reader;
			reader.Load();

			TestOperations(reader);
		}

		TEST_METHOD(TestCXMLReaderLoadInherits)
		{
			CXMLReader reader;
			reader.Load();

			TestInherits(reader);
		}

		void TestNames(CXMLReader reader)
		{
			// Get good and bad names, with reasons
			auto goodNames = reader.GetNames();
			auto badNames = reader.GetBadNames();

			// Test to make sure all names were added to appropriate vectors
			Assert::IsTrue(goodNames.size() == 4);
			Assert::IsTrue(badNames.size() == 4);

			// Check for specific good and bad names
			// Good was arbitrary
			// Bad was chosen as it is a special case
			Assert::IsTrue(goodNames.at(2)->GetName() == L"Picture");
			Assert::IsTrue(goodNames.at(2)->GetBad() == L"");
			Assert::IsTrue(badNames.at(1)->GetName() == L"");
			Assert::IsTrue(badNames.at(1)->GetBad() == L"Missing class name");
		}

		void TestAttributes(CXMLReader reader)
		{
			// Get good and bad attributes, with reasons
			auto goodAttributes = reader.GetAttributes();
			auto badAttributes = reader.GetBadAttributes();

			// Test to make sure all attributes were added to appropriate vectors
			Assert::IsTrue(goodAttributes.size() == 6);
			Assert::IsTrue(badAttributes.size() == 10);

			// Check for specific good and bad attributes
			// Good was arbitrary
			// Bad was chosen because of use of <> characters
			Assert::IsTrue(goodAttributes.at(2)->GetAttribute() == L"description: string");
			Assert::IsTrue(goodAttributes.at(2)->GetBad() == L"");
			Assert::IsTrue(badAttributes.at(5)->GetAttribute() == L"v: vector<double>");
			Assert::IsTrue(badAttributes.at(5)->GetBad() == L"Language artifact");
		}

		void TestOperations(CXMLReader reader)
		{
			// Get good and bad operations, with reasons
			auto goodOperations = reader.GetOperations();
			auto badOperations = reader.GetBadOperations();

			// Test to make sure all operations were added to appropriate vectors
			Assert::IsTrue(goodOperations.size() == 7);
			Assert::IsTrue(badOperations.size() == 3);

			// Check for specific good and bad operations
			// Good was arbitrary
			// Bad was chosen because of use of <> characters
			Assert::IsTrue(goodOperations.at(2)->GetOperation() == L"Save(image: Image, filename: string)");
			Assert::IsTrue(goodOperations.at(2)->GetBad() == L"");
			Assert::IsTrue(badOperations.at(0)->GetOperation() == L"GetActors(): vector<Actor>");
			Assert::IsTrue(badOperations.at(0)->GetBad() == L"Language artifact");
		}

		void TestInherits(CXMLReader reader)
		{
			// Get good and bad inherits, with reasons
			auto goodInherits = reader.GetInherits();
			auto badInherits = reader.GetBadInherits();

			// Test to make sure all inherits were added to appropriate vectors
			Assert::IsTrue(goodInherits.size() == 3);
			Assert::IsTrue(badInherits.size() == 4);

			// Check for specific good and bad inherits
			// Good was arbitrary
			// Bad was chosen because of use of "up" direction value
			Assert::IsTrue(goodInherits.at(2)->GetBase() == L"Fish");
			Assert::IsTrue(goodInherits.at(2)->GetDerived() == L"StinkyFish");
			Assert::IsTrue(goodInherits.at(2)->GetDirection() == L"up");
			Assert::IsTrue(badInherits.at(3)->GetBase() == L"Insect");
			Assert::IsTrue(badInherits.at(3)->GetDerived() == L"Fly");
			Assert::IsTrue(badInherits.at(3)->GetDirection() == L"down");
			Assert::IsTrue(badInherits.at(3)->GetBad() == L"Upside down");
		}
	};
}