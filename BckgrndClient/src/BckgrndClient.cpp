/*
 ============================================================================
 Name		: BckgrndClient.cpp
 Author	  : Oleg Ziakun
 Copyright   : Oleg Ziakun
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "BckgrndClientApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CBckgrndClientApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

