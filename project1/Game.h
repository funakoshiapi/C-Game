/**
 * \file Game.h
 *
 * Class that implements a Game
 */

#pragma once
#include <vector>
#include <memory>

class CGameObject;
class CGameObjectVisitor;
class CUMLPieceEmitter;
class CUmlHitDetector;
class CScoreBoard;
class CPlayer;

/// Width of the screen in virtual pixels
const int WIDTH = 1250;

/// Height of the screen in virtual pixels
const int HEIGHT = 1000;

/**
 * Class that represents the game being played
 */
class CGame
{
public:
	/// Game constructor
	CGame();
	/// Destructor
	virtual ~CGame();

	/**
	 * Draw the game area
	 * \param graphics The GDI+ graphics context to draw on
	 * \param width Width of the client window
	 * \param height Height of the client window
	 */
	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);
	/// Allows adding CGameObjects
	void Add(std::shared_ptr<CGameObject> gob);

	/// update time counter
	/// \param elapsed time
	void Update(double elapsed);

	void HitUml(CGameObject* pen);

	std::shared_ptr<CGameObject> CGame::HitTest(int x, int y);

	/// Populates game on launch
	void OnLaunch();

	/// Getter for Width
	/// \return Width of the game
	static int GetWidth() { return Width; }

	/// Getter for Height
	/// \return Height of the game
	static int GetHeight() { return Height; }

	/// Handles mouse movement event
	/// \param x X location of mouse
	/// \param y Y location of mouse
	void OnMouseMove(int x, int y);

	/// Left CLick event handler
	/// \param x X location of mouse click
	/// \param y Y location of mouse click
	void OnLeftClick(int x, int y);

	/// Accepts visitor
	/// \param visitor The visitor visiting the game
	void Accept(CGameObjectVisitor* visitor);

	void CheckGameOver();

	/// Setter for mGameOver
	/// \param gameover New value of mGameOver
	void SetGameOver(bool gameover) { mGameOver = gameover; }

	/// Getter for mGameOver
	/// \returns True if game is over
	bool IsGameOver() { return mGameOver; }

	/// Getter for mPenImage
	/// \returns The image of the pen
	std::shared_ptr<Gdiplus::Bitmap> GetPenImage() { return mPenImage; }

	/// Increments missed counter when bad UML leaves screen
	void UMLMissed();

	void PrepareDeleteQueue();

private:

	/// All of the gameobjects to populate our game
	std::vector<std::shared_ptr<CGameObject> > mGameObjects;

	std::shared_ptr<CScoreBoard> mScoreBoard = nullptr; ///< Pointer to Scoreboard GameObject

	std::shared_ptr<CPlayer> mPlayer = nullptr; ///< Pointer to player GameObject

	std::shared_ptr<Gdiplus::Bitmap> mPenImage = nullptr; ///< Pointer to the Pen Image bitmap

	/// Game area in virtual pixels
	const static int Width = WIDTH;

	/// Game area height in virtual pixels
	const static int Height = HEIGHT;

	/// value to scale screen size by
	double mScale = 1.0;

	/// x offset to indicate the origin
	double mXOffset = 0.0;

	/// y offset to indicate the origin
	double mYOffset = 0.0;

	/// Emitter for UMLPieces
	std::shared_ptr<CUMLPieceEmitter> mEmitter = nullptr;

	/// Time until emitter emits next piece
	double mEmitterTime = 0;

	/// Total elapsed time
	double mTimePassed = 0;

	/// game over check
	bool mGameOver = false;

	/// Queue of objects to be deleted from the game
	std::vector<std::shared_ptr<CGameObject>> mDeleteQueue;

	void ClearQueue();

	/// Indicates if the end screen is already being displayed.
	bool mEndScreenDisplayed = false;
};

