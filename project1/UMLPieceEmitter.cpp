/**
 * \file UMLPieceEmitter.cpp
 *
 */

#include "pch.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "UMLPieceEmitter.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

/// Maximum value for x direction
const double MAX_X = 5;

/// Minimum vlaue for x direction
const double MIN_X = 1;

/// Maximum value for y direction
const double MAX_Y = 15;

/// Minimum value for y direction
const double MIN_Y = 8;

/// First threshold to decrease handicap
const int HANDICAP_THRESHOLD_ONE = 3;

/// Second threshold to decrease handicap
const int HANDICAP_THRESHOLD_TWO = 6;

/// Third threshold to decrease handicap
const int HANDICAP_THRESHOLD_THREE = 9;

/// Fourth threshold to decrease handicap
const int HANDICAP_THRESHOLD_FOUR = 12;

/// Fifth threshold to decrease handicap
const int HANDICAP_THRESHOLD_FIVE = 15;

/// Height that UMLPieces are spawned in on
const double Y_SPAWN_LEVEL = 0;

/// Minimum X value a new UMLPiece can spawn at
const double MIN_X_SPAWN = -300;

/// Variance that X spawn location can have
const double X_SPAWN_FACTOR = 600;

/// The value that needs to be passed to make good UML or UML with inheritance
const int THRESHOLD = 4;

/// The number of bad elements that a single class UMLPiece can have
const int BAD_ELEMENT_TYPES = 3;

/// Maximum number of attributes a UMLPiece can have
const int MAX_NUM_ATTRIBUTES = 4;

/// Maximum number of operatons a UMLPiece can have
const int MAX_NUM_OPERATIONS = 4;

/// One above maximum number that can be tested against THRESHOLD
const int THRESHOLD_RAND_MAX = 10;

/**
 * CUMLPieceEmitter Constructor
 * \param game The game this emitter is part of
 */
CUMLPieceEmitter::CUMLPieceEmitter(CGame* game)
{
	// Set mGame based on argument
	mGame = game;

	// Create a XMLReader object and have it load in the UML data
	CXMLReader reader;
	reader.Load();

	// Set member variables based on results of reader's load
	mNames = reader.GetNames();
	mBadNames = reader.GetBadNames();
	mAttributes = reader.GetAttributes();
	mBadAttributes = reader.GetBadAttributes();
	mOperations = reader.GetOperations();
	mBadOperations = reader.GetBadOperations();
	mInherits = reader.GetInherits();
	mBadInherits = reader.GetBadInherits();
}

/**
 * Emits a new CUMLClass object
 * \returns A smart pointer to the newly created CUMLPiece object
 */
shared_ptr<CUMLPiece> CUMLPieceEmitter::EmitPiece()
{
	// Chance to create inherited instead of class starts at 0%
	// And moves up to 50% over time given current values of constants
	if (((rand() % THRESHOLD_RAND_MAX) + mHandicap) < THRESHOLD)
	{
		// Make inherited
		return EmitInherited();
	}
	
	// Prepare direction values
	double x = ((rand() / (double)RAND_MAX) * MAX_X + (MAX_X - MIN_X)) * (rand() % 2 == 0) ? 1 : -1; //Ternary at the end determines sign value
	double y = (rand() / (double)RAND_MAX) * MAX_Y + (MAX_Y - MIN_Y);
	double vectorLength = sqrt((x*x + y*y));
	x = x / vectorLength;
	y = y / vectorLength;

	// Create new CUMLClass object
	shared_ptr<CUMLClass> newPiece = make_shared<CUMLClass>(mGame,x,y,mPieceSpeed);

	// Create UMLDisplay for Class object
	shared_ptr<CUMLDisplay> newDisplay = make_shared<CUMLDisplay>();

	int numAttributes; // Number of attributes to add to display
	int numOperations; // Number of operations to add to display

	// Decide if new UML object is bad or not, starts at 100% bad, goes to 50% as time progresses
	// Increases probability in 10% increments given current values of constants
	if (((rand() % THRESHOLD_RAND_MAX) + mHandicap) > THRESHOLD)
	{
		// Make bad UML
		int badValue = rand() % BAD_ELEMENT_TYPES;
		int badIndex = 0;

		// Decide which element will be bad
		switch (badValue)
		{
			case 0: // Bad Name
				badIndex = rand() % (mBadNames.size());

				// Set bad name and bad
				newDisplay->SetName(mBadNames[badIndex]->GetName());
				newPiece->SetBad(mBadNames[badIndex]->GetBad());

				// Decide number of attributes and operations to add
				numAttributes = rand() % MAX_NUM_ATTRIBUTES;
				numOperations = rand() % MAX_NUM_OPERATIONS;
				
				// Finish creating display
				CreateDisplay(newDisplay,false,numAttributes,numOperations);

				break;

			case 1: // Bad Attribute
				badIndex = rand() % (mBadAttributes.size());

				// Set bad attribute and bad
				newDisplay->AddAttribute(mBadAttributes[badIndex]->GetAttribute());
				newPiece->SetBad(mBadAttributes[badIndex]->GetBad());

				// Decide number of additional attributes and operations to add
				numAttributes = rand() % (MAX_NUM_ATTRIBUTES - 1);
				numOperations = rand() % MAX_NUM_OPERATIONS;

				// Finish creating display
				CreateDisplay(newDisplay, true, numAttributes, numOperations);

				break;

			case 2: // Bad Operation
				badIndex = rand() % (mBadOperations.size());

				// Set bad operation and bad
				newDisplay->AddOperation(mBadOperations[badIndex]->GetOperation());
				newPiece->SetBad(mBadOperations[badIndex]->GetBad());

				// Decide number of attributes and additional operations to add
				numAttributes = rand() % MAX_NUM_ATTRIBUTES;
				numOperations = rand() % (MAX_NUM_OPERATIONS - 1);

				// Finish creating display
				CreateDisplay(newDisplay, true, numAttributes, numOperations);

				break;
		}
	}

	else
	{
		numAttributes = rand() % MAX_NUM_ATTRIBUTES;
		numOperations = rand() % MAX_NUM_OPERATIONS;

		CreateDisplay(newDisplay, true, numAttributes, numOperations);
	}

	// Set CUMLClass object's display value to new CUMLDisplay object
	newPiece->SetDisplay(newDisplay);

	// Set initial location
	newPiece->SetLocation((rand() / (double)RAND_MAX)* X_SPAWN_FACTOR + MIN_X_SPAWN, Y_SPAWN_LEVEL);

	// Increment the counter for total UMLPieces emitted
	IncrementEmitted();

	return newPiece;
}

/**
 * Creates the contents of a CUMLDisplay object
 * \param display The CUMLDisplay object being finished
 * \param name True if name needs to be set
 * \param attributes Number of attributes to add
 * \param operations Number of Operations to add
 */
void CUMLPieceEmitter::CreateDisplay(shared_ptr<CUMLDisplay> display, bool name, int attributes, int operations)
{
	// Set name if needed
	if (name)
	{
		display->SetName(mNames[rand() % mNames.size()]->GetName());
	}

	// Set attributes if needed
	if (attributes > 0)
	{
		// Shuffle Attributes
		random_shuffle(mAttributes.begin(), mAttributes.end());

		// Add attributes
		for (int i = 0; i < attributes; i++)
		{
			display->AddAttribute(mAttributes[i]->GetAttribute());
		}
	}

	//Set operations if needed
	if (operations > 0)
	{
		// Shuffle Operations
		random_shuffle(mOperations.begin(), mOperations.end());

		// Add attributes
		for (int i = 0; i < operations; i++)
		{
			display->AddOperation(mOperations[i]->GetOperation());
		}
	}
}

/**
 * Increment Emitted counter and update handicap if needed
 */
void CUMLPieceEmitter::IncrementEmitted()
{
	// Increment total emitted counter
	mTotalEmitted++;

	// Increase object speed
	mPieceSpeed++;

	// Decrease handicap at various point thresholds
	switch (mTotalEmitted)
	{
		case HANDICAP_THRESHOLD_ONE:
			mHandicap--;
			break;
		
		case HANDICAP_THRESHOLD_TWO:
			mHandicap--;
			break;
		
		case HANDICAP_THRESHOLD_THREE:
			mHandicap--;
			break;
		
		case HANDICAP_THRESHOLD_FOUR:
			mHandicap--;
			break;
		
		case HANDICAP_THRESHOLD_FIVE:
			mHandicap--;
			break;
	}
}

/**
 * Create a CUMLPiece object that has an inheritance relationship
 * \returns A smart pointer to the newly created CUMLInherited Object
 */
shared_ptr<CUMLPiece> CUMLPieceEmitter::EmitInherited()
{

	// Prepare direction values
	double x = ((rand() / (double)RAND_MAX) * MAX_X + (MAX_X - MIN_X)) * (rand() % 2 == 0) ? 1 : -1; //Ternary at the end determines sign value
	double y = (rand() / (double)RAND_MAX) * MAX_Y + (MAX_Y - MIN_Y);
	double vectorLength = sqrt((x * x + y * y));
	x = x / vectorLength;
	y = y / vectorLength;

	// Create new CUMLInherited object
	shared_ptr<CUMLInherited> newPiece = make_shared<CUMLInherited>(mGame, x, y, mPieceSpeed);

	// Create UMLDisplay for Base
	shared_ptr<CUMLDisplay> newBase = make_shared<CUMLDisplay>();

	// Create UMLDisplay for Derived
	shared_ptr<CUMLDisplay> newDerived = make_shared<CUMLDisplay>();


	// Decide if new UML object is bad or not, starts at 100% bad, goes to 50% as time progresses
	// Increases probability in 10% increments given current values of constants
	if (((rand() % THRESHOLD_RAND_MAX) + mHandicap) > THRESHOLD) // Make bad UML
	{
		// Select bad Inherit
		int badIndex = rand() % (mBadInherits.size());

		// Set appropriate values
		newPiece->SetBad(mBadInherits[badIndex]->GetBad());
		newPiece->SetArrowDirection(mBadInherits[badIndex]->GetBad());
		newBase->SetName(mBadInherits[badIndex]->GetBase());
		newDerived->SetName(mBadInherits[badIndex]->GetDerived());
	}

	else // Make good UML
	{
		// Select good Inherit
		int goodIndex = rand() % (mInherits.size());

		// Set appropriate values
		newPiece->SetArrowDirection(mInherits[goodIndex]->GetDirection());
		newBase->SetName(mInherits[goodIndex]->GetBase());
		newDerived->SetName(mInherits[goodIndex]->GetDerived());
	}

	// Create Base Display
	int numAttributes = rand() % MAX_NUM_ATTRIBUTES; // Number of attributes to add to display
	int numOperations = rand() % MAX_NUM_OPERATIONS; // Number of operations to add to display
	CreateDisplay(newBase, false, numAttributes, numOperations);

	// Create Derived Display 
	numAttributes = rand() % MAX_NUM_ATTRIBUTES;
	numOperations = rand() % MAX_NUM_OPERATIONS;
	CreateDisplay(newDerived, false, numAttributes, numOperations);

	// Set displays for new piece
	newPiece->SetBaseDisplay(newBase);
	newPiece->SetDerivedDisplay(newDerived);

	// Set initial location
	newPiece->SetLocation((rand() / (double)RAND_MAX) * X_SPAWN_FACTOR + MIN_X_SPAWN, Y_SPAWN_LEVEL);

	// Increment the total count of pieces emitted
	IncrementEmitted();

	return newPiece;
}
