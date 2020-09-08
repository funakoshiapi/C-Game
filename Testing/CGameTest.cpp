#include "pch.h"
#include "CppUnitTest.h"
#include <memory>
#include "Game.h"
#include "RedPen.h"
#include "Player.h"
#include "UMLPieceEmitter.h"
#include "EndScreen.h"
#include "ScoreBoard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Gdiplus;

namespace Testing
{
	TEST_CLASS(CGameTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCGameConstructor)
		{
			shared_ptr<CGame> game = make_shared<CGame>();
		}

		TEST_METHOD(TestCGameAddPen)
		{
			shared_ptr<CGame> game = make_shared<CGame>();
			shared_ptr<CRedPen> pen = make_shared<CRedPen>(game.get(), 100, 200);
			game->Add(pen);
		}

		TEST_METHOD(TestCGameAddPlayer)
		{
			shared_ptr<CGame> game = make_shared<CGame>();
			shared_ptr<CPlayer> player = make_shared<CPlayer>(game.get());
			game->Add(player);
		}

		TEST_METHOD(TestCGameAddEmittedUMLPiece)
		{
			shared_ptr<CGame> game = make_shared<CGame>();
			shared_ptr<CUMLPieceEmitter> emitter = make_shared<CUMLPieceEmitter>(game.get());
			shared_ptr<CUMLPiece> piece = emitter->EmitPiece();
			game->Add(piece);
		}

		TEST_METHOD(TestCGameAddScoreboard)
		{
			shared_ptr<CGame> game = make_shared<CGame>();
			shared_ptr<CScoreBoard> scoreboard = make_shared<CScoreBoard>(game.get());
			game->Add(scoreboard);
		}

		TEST_METHOD(TestCGameAddEndScreen)
		{
			shared_ptr<CGame> game = make_shared<CGame>();
			shared_ptr<CEndScreen> endscreen = make_shared<CEndScreen>(game.get());
			game->Add(endscreen);
		}
	};
}