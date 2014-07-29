/*
 ============================================================================
 Name		: ClientStarter.h
 Author	  : Oleg Ziakun
 Version	 : 1.0
 Copyright   : 
 Description : CClientStarter declaration
 ============================================================================
 */

#ifndef CLIENTSTARTER_H
#define CLIENTSTARTER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "CGetTimer.h"
#include "GetContent.h"

/**
 *  CClientStarter
 * 
 */
class CClientStarter : public CBase, public MTimerNotify, public MGetContentObserver
	{
public:
	
	~CClientStarter();

	static CClientStarter* NewL();
	static CClientStarter* NewLC();

public:

	virtual void TimerExpired(TAny* aTimer, TInt aError);

public:
	
	virtual void GetNextContent(const TDesC& aURL, const TDesC& aSavedFileName);	

private:

	CClientStarter();

	void ConstructL();
	
	void WriteValueToIniFileL(RFs& aFs, const TDesC& aFileName, const TDesC8& aBuffer);
	void ReadValueFromIniFileL(RFs& aFs, const TDesC& aFileName, TDes8& aBuffer);
	TBool IniFileExists(RFs& aFs, const TDesC& aFileName);

private:

	CGetTimer* iGetTimer;
	CGetContent* iGetContent;
	
	};

#endif // CLIENTSTARTER_H
