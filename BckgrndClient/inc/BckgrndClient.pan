/*
 ============================================================================
 Name		: BckgrndClient.pan
 Author	  : Oleg Ziakun
 Copyright   : 
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __BCKGRNDCLIENT_PAN__
#define __BCKGRNDCLIENT_PAN__

/** BckgrndClient application panic codes */
enum TBckgrndClientPanics
	{
	EBckgrndClientUi = 1
	// add further panics here
	};

inline void Panic(TBckgrndClientPanics aReason)
	{
	_LIT(applicationName, "BckgrndClient");
	User::Panic(applicationName, aReason);
	}

#endif // __BCKGRNDCLIENT_PAN__
