/*
 ============================================================================
 Name		: CGetTimer.h
 Author	  : Oleg Ziakun
 Version	 : 1.0
 Copyright   : 
 Description : CCGetTimer declaration
 ============================================================================
 */

#ifndef CGETTIMER_H
#define CGETTIMER_H

#include <e32base.h>	
#include <e32std.h>	

class MTimerNotify
	{
public:
	
	virtual void TimerExpired(TAny* aTimer, TInt aError) = 0;
	
	};

class CGetTimer : public CActive
	{
public:
	
	~CGetTimer();

	static CGetTimer* NewL(MTimerNotify& aNotify);
	static CGetTimer* NewLC(MTimerNotify& aNotify);

public:
	
	// New functions
	// Function for making the initial request
	void StartL(TTimeIntervalMicroSeconds32 aDelay);

private:

	CGetTimer(MTimerNotify& aNotify);

	void ConstructL();

private:
	
	// From CActive
	// Handle completion
	void RunL();

	// How to cancel me
	void DoCancel();

	// Override to handle leaves from RunL(). Default implementation causes
	// the active scheduler to panic.
	TInt RunError(TInt aError);

private:
	
	enum TCGetTimerState
		{
		EUninitialized, // Uninitialized
		EInitialized, // Initalized
		EError
		// Error condition
		};

private:
	
	TInt iState; // State of the active object
	RTimer iTimer; // Provides async timing service
	MTimerNotify& iNotify;
	TTimeIntervalMicroSeconds32 iDelay;
	
	};

#endif // CGETTIMER_H
