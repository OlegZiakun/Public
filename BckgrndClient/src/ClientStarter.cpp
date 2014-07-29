/*
 ============================================================================
 Name		 : ClientStarter.cpp
 Author	     : Oleg Ziakun
 Version	 : 1.0
 Copyright   : Oleg Ziakun
 Description : CClientStarter implementation
 ============================================================================
 */

#include "ClientStarter.h"
#include <Debug.h>
#include <Defs.h>

CClientStarter::CClientStarter()
	{
	}

CClientStarter::~CClientStarter()
	{
	delete iGetTimer;
	delete iGetContent;
	}

CClientStarter* CClientStarter::NewLC()
	{
	CClientStarter* self = new (ELeave) CClientStarter();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CClientStarter* CClientStarter::NewL()
	{
	CClientStarter* self = CClientStarter::NewLC();
	CleanupStack::Pop();
	return self;
	}

void CClientStarter::ConstructL()
	{
	iGetContent = CGetContent::NewL(*this);
	iGetTimer = CGetTimer::NewL(*this);

	const TInt valSize = 1;
	RFs fs;
	
	User::LeaveIfError(fs.Connect());
	
	TBuf8<valSize> buffer;
	TBuf <valSize> delayStr;
	TInt           delay;

	iGetContent->Download(KTxtFile, KTxtSavedFile);

	buffer.Copy(KDefaultDelay);

	if (!IniFileExists(fs, KIniFile))
		{
		WriteValueToIniFileL(fs, KIniFile, buffer);
		}

	ReadValueFromIniFileL(fs, KIniFile, buffer);
	delayStr.Copy(buffer);

	TLex lexValue(delayStr);
	User::LeaveIfError(lexValue.Val(delay));

	TTimeIntervalMicroSeconds32 updateInterval(delay * 60 * 1000000);
	
	iGetTimer->StartL(updateInterval);
	}

void CClientStarter::TimerExpired(TAny* aTimer, TInt aError)
	{
	/*To continue download of the content here should be the next (periodical) call of iGetContent->Download()
	 *with the next queue of files.	 
	 */
	}

void CClientStarter::GetNextContent(const TDesC& aURL,
		const TDesC& aSavedFileName)
	{
	DBG_PRINT_MSG(_L("[DEBUG INFO]:"),_L("CClientStarter::GetNextContent()"));
	iGetContent->Download(aURL, aSavedFileName);
	}

void CClientStarter::WriteValueToIniFileL(RFs& aFs, const TDesC& aFileName,
		const TDesC8& aBuffer)
	{
	RFile file;
	
	User::LeaveIfError(file.Replace(aFs, aFileName, EFileWrite));
	
	CleanupClosePushL(file);
	User::LeaveIfError(file.Write(aBuffer, aBuffer.Length()));
	CleanupStack::PopAndDestroy(&file);
	}

void CClientStarter::ReadValueFromIniFileL(RFs& aFs, const TDesC& aFileName,
		TDes8& aBuffer)
	{
	RFile file;
	
	User::LeaveIfError(file.Open(aFs, aFileName, EFileRead));
	
	CleanupClosePushL(file);
	file.Read(0, aBuffer);
	CleanupStack::PopAndDestroy(&file);
	}

TBool CClientStarter::IniFileExists(RFs& aFs, const TDesC& aFileName)
	{
	RFile file;
	TBool fileExists = ETrue;
	TInt err = file.Open(aFs, aFileName, EFileRead);

	if (err != KErrAlreadyExists)
		{
		fileExists = EFalse;
		}

	file.Close();	
	
	return fileExists;
	}

