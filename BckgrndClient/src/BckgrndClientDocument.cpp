/*
 ============================================================================
 Name		: BckgrndClientDocument.cpp
 Author	  : Oleg Ziakun
 Copyright   : Oleg Ziakun
 Description : CBckgrndClientDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "BckgrndClientAppUi.h"
#include "BckgrndClientDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBckgrndClientDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBckgrndClientDocument* CBckgrndClientDocument::NewL(CEikApplication& aApp)
	{
	CBckgrndClientDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CBckgrndClientDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBckgrndClientDocument* CBckgrndClientDocument::NewLC(CEikApplication& aApp)
	{
	CBckgrndClientDocument* self = new (ELeave) CBckgrndClientDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CBckgrndClientDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBckgrndClientDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CBckgrndClientDocument::CBckgrndClientDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBckgrndClientDocument::CBckgrndClientDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CBckgrndClientDocument::~CBckgrndClientDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBckgrndClientDocument::~CBckgrndClientDocument()
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CBckgrndClientDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBckgrndClientDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CBckgrndClientAppUi;
	}

// End of File
