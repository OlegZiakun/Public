/*
 ============================================================================
 Name		: BckgrndClientDocument.h
 Author	  : Oleg Ziakun
 Copyright   : 
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __BCKGRNDCLIENTDOCUMENT_h__
#define __BCKGRNDCLIENTDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CBckgrndClientAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CBckgrndClientDocument application class.
 * An instance of class CBckgrndClientDocument is the Document part of the
 * AVKON application framework for the BckgrndClient example application.
 */
class CBckgrndClientDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CBckgrndClientDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CBckgrndClientDocument.
	 */
	static CBckgrndClientDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CBckgrndClientDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CBckgrndClientDocument.
	 */
	static CBckgrndClientDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CBckgrndClientDocument
	 * Virtual Destructor.
	 */
	virtual ~CBckgrndClientDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CBckgrndClientAppUi object and return a pointer to it.
	 * The object returned is owned by the Uikon framework.
	 * @return Pointer to created instance of AppUi.
	 */
	CEikAppUi* CreateAppUiL();

private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CBckgrndClientDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CBckgrndClientDocument(CEikApplication& aApp);

	};

#endif // __BCKGRNDCLIENTDOCUMENT_h__
// End of File
