/*
 ============================================================================
 Name		: BckgrndClientApplication.h
 Author	  : Oleg Ziakun
 Copyright   : 
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __BCKGRNDCLIENTAPPLICATION_H__
#define __BCKGRNDCLIENTAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "BckgrndClient.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidBckgrndClientApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CBckgrndClientApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CBckgrndClientApplication is the application part of the
 * AVKON application framework for the BckgrndClient example application.
 */
class CBckgrndClientApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidBckgrndClientApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CBckgrndClientDocument document object. The returned
	 * pointer in not owned by the CBckgrndClientApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __BCKGRNDCLIENTAPPLICATION_H__
// End of File
