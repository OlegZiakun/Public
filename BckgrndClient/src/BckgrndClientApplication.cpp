/*
 ============================================================================
 Name		: BckgrndClientApplication.cpp
 Author	  : Oleg Ziakun
 Copyright   : Oleg Ziakun
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "BckgrndClient.hrh"
#include "BckgrndClientDocument.h"
#include "BckgrndClientApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBckgrndClientApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CBckgrndClientApplication::CreateDocumentL()
	{
	// Create an BckgrndClient document, and return a pointer to it
	return CBckgrndClientDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CBckgrndClientApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CBckgrndClientApplication::AppDllUid() const
	{
	// Return the UID for the BckgrndClient application
	return KUidBckgrndClientApp;
	}

// End of File
