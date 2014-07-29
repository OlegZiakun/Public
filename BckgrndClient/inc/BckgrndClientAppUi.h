/*
 ============================================================================
 Name		: BckgrndClientAppUi.h
 Author	  : Oleg Ziakun
 Copyright   : 
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __BCKGRNDCLIENTAPPUI_h__
#define __BCKGRNDCLIENTAPPUI_h__

#include <aknappui.h>
#include "ClientStarter.h"

class CBckgrndClientAppView;

// CLASS DECLARATION
/**
 * CBckgrndClientAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CBckgrndClientAppUi : public CAknAppUi
	{
public:
	// Constructors and destructor

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CBckgrndClientAppUi.
	 * C++ default constructor. This needs to be public due to
	 * the way the framework constructs the AppUi
	 */
	CBckgrndClientAppUi();

	/**
	 * ~CBckgrndClientAppUi.
	 * Virtual Destructor.
	 */
	virtual ~CBckgrndClientAppUi();

private:
	// Functions from base classes

	/**
	 * From CEikAppUi, HandleCommandL.
	 * Takes care of command handling.
	 * @param aCommand Command to be handled.
	 */
	void HandleCommandL(TInt aCommand);

	/**
	 *  HandleStatusPaneSizeChange.
	 *  Called by the framework when the application status pane
	 *  size is changed.
	 */
	void HandleStatusPaneSizeChange();
	
	void RunDialog(const TDesC& aTitle,const TDesC& aMsg);
	
private:
	// Data

	/**
	 * The application view
	 * Owned by CBckgrndClientAppUi
	 */
	CBckgrndClientAppView* iAppView;
	CClientStarter* iClientStarter;

	};

#endif // __BCKGRNDCLIENTAPPUI_h__
// End of File
