/*
 ============================================================================
 Name		 : CGetTimer.cpp
 Author	     : Oleg Ziakun
 Version	 :
 Copyright   : Oleg Ziakun
 Description : CCGetTimer implementation
 ============================================================================
 */

#include "CGetTimer.h"
#include <Debug.h>

CGetTimer::CGetTimer(MTimerNotify& aNotify) :
	CActive(EPriorityStandard), iNotify(aNotify)
	{
	}

CGetTimer* CGetTimer::NewLC(MTimerNotify& aNotify)
	{
	CGetTimer* self = new (ELeave) CGetTimer(aNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CGetTimer* CGetTimer::NewL(MTimerNotify& aNotify)
	{
	CGetTimer* self = CGetTimer::NewLC(aNotify);
	CleanupStack::Pop(); // self;
	return self;
	}

void CGetTimer::ConstructL()
	{
	User::LeaveIfError(iTimer.CreateLocal()); // Initialize timer
	CActiveScheduler::Add(this); // Add to scheduler
	}

CGetTimer::~CGetTimer()
	{
	Cancel(); // Cancel any request, if outstanding
	iTimer.Close(); // Destroy the RTimer object
	}

void CGetTimer::DoCancel()
	{
	iTimer.Cancel();
	}

void CGetTimer::StartL(TTimeIntervalMicroSeconds32 aDelay)
	{	
	iDelay = aDelay;
	
	Cancel(); // Cancel any request, just to be sure
	iState = EUninitialized;
	iTimer.After(iStatus, iDelay); // Set for later
	SetActive(); // Tell scheduler a request is active
	}

void CGetTimer::RunL()
	{
	if (iState == EUninitialized)
		{
		// Do something the first time RunL() is called
		iState = EInitialized;
		}
	else if (iState != EError)
		{
		// Do something
		}

	iNotify.TimerExpired(this, iStatus.Int());
		
    iTimer.After(iStatus, iDelay);
		
	SetActive();
	}

TInt CGetTimer::RunError(TInt aError)
	{
	return aError;
	}
