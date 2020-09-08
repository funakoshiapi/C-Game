/**
 * \file GameObjectVisitor.h
 *
 *
 * Base Visitor class for GameObjects
 */


#pragma once

//forward reference game object types
class CPlayer;
class CRedPen;
class CUMLPiece;
class CScoreBoard;
class CCountDownTimer;

/**
 * Class implementing game object visitor
 */
class CGameObjectVisitor
{
	public:
		virtual ~CGameObjectVisitor(){}

		/// Visit Player object
		/// \param player The player being visited
		virtual void VisitPlayer(CPlayer* player){}

		/// Visit RedPen object
		/// \param pen The RedPen being visited
		virtual void VisitPen(CRedPen* pen) {}

		/// Visit UmlPiece object
		/// \param umlPiece The UMLPiece being visited
		virtual void VisitUMLPiece(CUMLPiece* umlPiece) {}

		/// Visit ScoreBoard object
		/// \param scoreBoard The Scoreboard being visited
		virtual void VisitScoreBoard(CScoreBoard* scoreBoard) {}
};

