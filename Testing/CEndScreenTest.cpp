#include "pch.h"
#include "CppUnitTest.h"
#include <memory>
#include "EndScreen.h"
#include "Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CEndScreenTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCEndSceenConstructor)
		{
			shared_ptr<CGame> testGame = make_shared<CGame>();
			shared_ptr<CEndScreen> endscreen = make_shared<CEndScreen>(testGame.get());
		}

		TEST_METHOD(TestCEndSceenFinalScore)
		{
			shared_ptr<CGame> testGame = make_shared<CGame>();;
			shared_ptr<CEndScreen> endscreen = make_shared<CEndScreen>(testGame.get());

			endscreen->SetFinalScore(6,3,2);
			Assert::IsTrue(5 == endscreen->GetFinalScore());

			endscreen->SetFinalScore(10,8,5);
			Assert::IsTrue(2 == endscreen->GetFinalScore());

			endscreen->SetFinalScore(12,3,2);
			Assert::IsTrue(17 == endscreen->GetFinalScore());
		}

		TEST_METHOD(TestCEndSceenMinimumScore)
		{
			shared_ptr<CGame> testGame = make_shared<CGame>();
			shared_ptr<CEndScreen> endscreen = make_shared<CEndScreen>(testGame.get());

			// Positive score outweighed by missed
			endscreen->SetFinalScore(6, 14, 0);
			Assert::IsTrue(0 == endscreen->GetFinalScore());

			// Positive score outweighed by unfair
			endscreen->SetFinalScore(6, 0, 7);
			Assert::IsTrue(0 == endscreen->GetFinalScore());

			// Positive score outweighed by combination
			endscreen->SetFinalScore(6, 3, 5);
			Assert::IsTrue(0 == endscreen->GetFinalScore());
		}
	};
}