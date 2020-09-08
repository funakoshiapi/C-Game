#include "pch.h"
#include "CppUnitTest.h"
#include <memory>
#include "UMLPieceEmitter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

// Random seed for testing
const unsigned RANDOM_SEED = 8675309;

// Number of pieces to emit in TestCUMLPieceEmitterEmitGoodUML 
const int NUM_PIECES = 13;

// Number of bad pieces to emit
const int BAD_PIECES = 3;

namespace Testing
{
	TEST_CLASS(CUMLPieceEmitterTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCUMLPieceEmitterConstructor)
		{
			shared_ptr<CGame> testGame = make_shared<CGame>();
			shared_ptr<CUMLPieceEmitter> emitter = make_shared<CUMLPieceEmitter>(testGame.get());
		}

		TEST_METHOD(TestCUMLPieceEmitterEmitBadOnLaunch)
		{
			// Construct Emitter
			shared_ptr<CGame> testGame = make_shared<CGame>();
			shared_ptr<CUMLPieceEmitter> emitter = make_shared<CUMLPieceEmitter>(testGame.get());

			// Seed random based on current time
			srand((unsigned)time);

			// Create 3 pieces and ensure that piece is false
			// This is done because the game should always start by emitting
			// only bad UML
			for (int i = 0; i < BAD_PIECES; i++)
			{
				shared_ptr<CUMLPiece> piece = emitter->EmitPiece();
				Assert::IsFalse(piece->GetBad() == L"");
			}
			
		}

		TEST_METHOD(TestCUMLPieceEmitterEmitGoodUML)
		{
			// Construct Emitter
			shared_ptr<CGame> testGame = make_shared<CGame>();
			shared_ptr<CUMLPieceEmitter> emitter = make_shared<CUMLPieceEmitter>(testGame.get());

			// Seed random using constant
			srand(RANDOM_SEED);

			shared_ptr<CUMLPiece> piece;

			for (int i = 0; i < NUM_PIECES; i++)
			{
				piece = emitter->EmitPiece();
			}

			// Assert that piece is good
			Assert::IsTrue(piece->GetBad() == L"");

			// Assert that next piece also happens to be good
			piece = emitter->EmitPiece();
			Assert::IsTrue(piece->GetBad() == L"");
		}

	};
}