#include "pch.h"
#include "CppUnitTest.h"
#include <GameObject.h>
#include <Game.h>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CGameObjectTest)
	{
	public:
		
		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}

		TEST_METHOD(TestPositioning)
		{
			CGame game;
			//Test positioning of a GameObject

			shared_ptr <CGameObject> obj = make_shared<CGameObject>(&game);

			Assert::IsTrue(obj->GetX() == 0 && obj->GetY() == 0,
				L"Testing default positioning");

			obj->SetLocation(1, 2);

			Assert::IsTrue(obj->GetX() == 1 && obj->GetY() == 2,
				L"Testing changed positioning");
		}

		//
		TEST_METHOD(TestCGameHitTest)
		{
			CGame game;

			Assert::IsTrue(game.HitTest(100, 200) == nullptr,
				L"Testing empty game");

			shared_ptr<CGameObject> obj1 = make_shared<CGameObject>(&game);
			obj1->SetLocation(100, 200);
			obj1->SetDimensions(100, 100);
			game.Add(obj1);

			Assert::IsTrue(game.HitTest(100, 200) == obj1,
				L"Testing obj at 100, 200");

			shared_ptr<CGameObject> obj2 = make_shared<CGameObject>(&game);
			obj2->SetLocation(100, 200);
			obj2->SetDimensions(100, 100);
			game.Add(obj2);

			Assert::IsTrue(game.HitTest(100, 200) == obj2,
				L"Testing obj stacking");

			Assert::IsTrue(game.HitTest(100, 2010) == nullptr,
				L"Testing no obj at 100, 2010");
		}
	};
}