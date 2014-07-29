/*
 ============================================================================
 Name		 : GetContent.cpp
 Author	     : Oleg Ziakun
 Version	 : 1.0
 Copyright   : Oleg Ziakun
 Description : CClientStarter implementation
 ============================================================================
 */

#include "GetContent.h"
#include <Debug.h>

CGetContent::CGetContent(MGetContentObserver& aObserver) : iObserver(aObserver)
	{
	}

CGetContent::~CGetContent()
	{
	delete iEngine;
	}

CGetContent* CGetContent::NewL(MGetContentObserver& aObserver)
	{
	CGetContent* self = new (ELeave) CGetContent(aObserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

void CGetContent::ConstructL()
	{
	iEngine = CHTTPEngine::NewL(*this);
	}

void CGetContent::Download(const TDesC& aURL, const TDesC& aSavedFileName)
	{
	iEngine->CancelTransaction();

	iURI.Zero();
	iURI8.Zero();

	iURI.Copy(aURL);

	// Insert prefix to uri (it must begin with "http://" or "https://")
	if (iURI.Find(KHttpPrefix) == KErrNotFound && iURI.Find(KHttpsPrefix) == KErrNotFound)
		{
		// If the uri does not contain http or https,
		// use the default, "http://"
		iURI8.Append(KHttpPrefix8);
		iURI8.Append(iURI);
		}
	else
		{
		iURI8.Copy(iURI);
		}
		
	TRAPD(err,iEngine->IssueHTTPGetL(iURI8,aSavedFileName));

	if (err != KErrNone)
		{
		// handle error here
		}
	}

void CGetContent::OnHTTPEvent(const TDesC & aEventDescription)
	{	
	DBG_PRINT_MSG(_L("[DEBUG INFO]:"),aEventDescription);
	
	static TBool stopDownload = EFalse;
	
	/* In real application for files needed to download "files queue" must be arranged here.
	 * For example it can be class that using RArray to add and to handle "files queue".
	 * To simplify implementation of the test task here using stopDownload variable just for
	 * testing purposes.
	 */
	
	if(!aEventDescription.Compare(KSucceeded) && !stopDownload)
		{
		iObserver.GetNextContent(KImgFile,KImgSavedFile);
		stopDownload = ETrue;
		}	
	}

