/*
 * HTTPEngine.cpp
 *
 * Author: Oleg Ziakun
*/

#include <avkon.hrh>
#include <aknnotewrappers.h>
#include <aknlists.h> 
#include <uri8.h>
#include <http.h>
#include <stringloader.h>
#include <chttpformencoder.h>
#include <HttpStringConstants.h>
#include <COMMDB.H>   
#include <CDBPREFTABLE.H> 
#include <CommDbConnPref.h>
#include <es_enum.h> 
#include <Es_sock.h> 
#include <stringpool.h> 
#include <http\rhttpconnectioninfo.h>
#include "HTTP.hrh"
#include "HTTPEngine.h"
#include <Debug.h>

CHTTPEngine* CHTTPEngine::NewL(MHTTPObserver & aObserver)
	{
	CHTTPEngine* self = new (ELeave) CHTTPEngine(aObserver);
	return self;
	}

CHTTPEngine::CHTTPEngine(MHTTPObserver & aObserver) :
	iObserver(aObserver), iPostData(NULL), iRunning(EFalse),
			iConnectionSetupDone(EFalse), iPrevProfileId(-1)
	{
	}

CHTTPEngine::~CHTTPEngine()
	{
	if(iRepository) delete iRepository;
	iSession.Close();
	if(iPostData) delete iPostData;
	iFile.Close();
	iFs.Close();
	}

void CHTTPEngine::SetupConnectionL()
	{
	TInt bearerFilter = EApBearerTypeAllBearers;
	TInt currentProfileId;

	DBG_PRINT_MSG(_L("[DEBUG INFO]:"),_L("CHTTPEngine::SetupConnectionL starting..."));

	// Check whether we are offline or online
	iRepository->Get(KProEngActiveProfile, currentProfileId);

	DBG_PRINT_MSG_INT(_L("[DEBUG INFO] currentProfileId:"),currentProfileId);

	// Close the connection only if
	// a) this is not the first time and
	// b) the profile has changed and
	// c) either the previous or the current profile is Offline
	if (iPrevProfileId != -1 && iPrevProfileId != currentProfileId && (iPrevProfileId == OFFLINE || currentProfileId == OFFLINE))
		{ 
		// Close and uninitialize
		iConnectionSetupDone = EFalse;
		iSession.Close();
		iConnection.Close();
		iSocketServ.Close();
		}

	// In offline, only WLAN connections are available 
	if (currentProfileId == OFFLINE)
		{
		//do necessary actions here 
		}

	// Save current profile id
	iPrevProfileId = currentProfileId;

	// Try to find an existing connection. If connection has not been set up,
	// iConnection is not initialized and FindExistingConnection() fails.
	// Thus, in that case, finding must not be carried out.
	if (iConnectionSetupDone && !FindExistingConnection())
		{
		iConnectionSetupDone = EFalse;
		}

	if (iConnectionSetupDone)
		{
		// Connection setup is done
		return;
		}

	// Open RHTTPSession with default protocol ("HTTP/TCP")
	iSession.OpenL();

	// Install this class as the callback for authentication requests. When
	// page requires authentication the framework calls GetCredentialsL to get
	// user name and password.
	InstallAuthenticationL(iSession);

	// Show IAP selection dialog
	CActiveApDb* aDb = CActiveApDb::NewL();
	CleanupStack::PushL(aDb);

	CApSettingsHandler* settings = CApSettingsHandler::NewLC(*aDb, ETrue,EApSettingsSelListIsPopUp, EApSettingsSelMenuSelectNormal, KEApIspTypeAll, bearerFilter, KEApSortNameAscending, 0, EVpnFilterBoth, ETrue);

	TInt iapRet = settings->RunSettingsL(0, iSelectedIap);
	
	CleanupStack::PopAndDestroy(settings);
	CleanupStack::PopAndDestroy(aDb);
	
	if(iapRet != KApUiEventSelected)
		{
		// Exit no selection
		User::Leave(KErrNotReady);
		}
	else
		{
		// IAP Selected
		// Open socket server and start the connection
		User::LeaveIfError(iSocketServ.Connect());
		User::LeaveIfError(iConnection.Open(iSocketServ));
		// Now we have the iap Id. Use it to connect for the connection
		TCommDbConnPref connectPref;
		// Setup preferences 
		connectPref.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
		// Sets the CommDb ID of the IAP to use for this connection
		connectPref.SetIapId(iSelectedIap);
		// Start connection
		User::LeaveIfError(iConnection.Start(connectPref));
		// Set the sessions connection info...
		RStringPool strPool = iSession.StringPool();
		RHTTPConnectionInfo connInfo = iSession.ConnectionInfo();
		// ...to use our socket server and connection
		connInfo.SetPropertyL(strPool.StringF(HTTP::EHttpSocketServ, RHTTPSession::GetTable()), THTTPHdrVal(iSocketServ.Handle()));
		// ...to use our connection
		connInfo.SetPropertyL(strPool.StringF(HTTP::EHttpSocketConnection, RHTTPSession::GetTable()), THTTPHdrVal(REINTERPRET_CAST(TInt, &(iConnection))));

		iConnectionSetupDone = ETrue;
		}
	}

// ----------------------------------------------------------------------------
// Enumerates through existing connections and tries to find one that matches
// the selected IAP. If one is found, ETrue is returned; otherwise, EFalse.
// ----------------------------------------------------------------------------
TBool CHTTPEngine::FindExistingConnection(void)
	{
	TBool connected = EFalse;
	TConnectionInfoBuf connInfo;
	TUint count;
	
	if (iConnection.EnumerateConnections(count) == KErrNone)
		{
		for (TUint i = 1; i <= count; i++)
			{
			// Note: GetConnectionInfo expects 1-based index.
			if (iConnection.GetConnectionInfo(i, connInfo) == KErrNone)
				{
				if (connInfo().iIapId == iSelectedIap)
					{
					connected = ETrue;
					break;
					}
				}
			}
		}
	
	return connected;
	}

// ----------------------------------------------------------------------------
// Used to set header value to HTTP request
// ----------------------------------------------------------------------------
void CHTTPEngine::SetHeaderL(RHTTPHeaders aHeaders, TInt aHdrField,
		const TDesC8& aHdrValue)
	{
	RStringF valStr = iSession.StringPool().OpenFStringL(aHdrValue);
	
	CleanupClosePushL(valStr);
	
	THTTPHdrVal val(valStr);
	
	aHeaders.SetFieldL(iSession.StringPool().StringF(aHdrField,
			RHTTPSession::GetTable()), val);
	
	CleanupStack::PopAndDestroy(); // valStr
	}

void CHTTPEngine::IssueHTTPGetL(const TDesC8& aUri, const TDesC& aSavedFileName)
	{
	DBG_PRINT_MSG(_L("[DEBUG INFO]:"),_L("CHTTPEngine::IssueHTTPGetL starting..."));

	if (!iConnectionSetupDone)
		{
		iRepository = CRepository::NewL(KCRUidProfileEngine);
		User::LeaveIfError(iFs.Connect());
		DBG_PRINT_MSG(_L("[DEBUG INFO]:"),_L("CHTTPEngine::IssueHTTPGetL connect session OK"));
		}

	iCurrentFileName.Copy(aSavedFileName);

	DBG_PRINT_MSG(_L("[DEBUG INFO]: iCurrentFileName"),iCurrentFileName);

	iFile.Close();

	User::LeaveIfError(iFile.Replace(iFs, iCurrentFileName, EFileStream
			| EFileWrite));

	DBG_PRINT_MSG(_L("[DEBUG INFO]:"),_L("CHTTPEngine::IssueHTTPGetL create file OK"));

	// Parse string to URI (as defined in RFC2396)
	TUriParser8 uri;
	uri.Parse(aUri);
	
	// attach connection
	SetupConnectionL();

	// Get request method string for HTTP GET
	RStringF method = iSession.StringPool().StringF(HTTP::EGET, RHTTPSession::GetTable());

	// Open transaction with previous method and parsed uri. This class will
	// receive transaction events in MHFRunL and MHFRunError.
	iTransaction = iSession.OpenTransactionL(uri, *this, method);

	// Set headers for request; user agent and accepted content type
	RHTTPHeaders hdr = iTransaction.Request().GetHeaderCollection();
	SetHeaderL(hdr, HTTP::EUserAgent, KUserAgent);
	SetHeaderL(hdr, HTTP::EAccept, KAccept);
	
	DBG_PRINT_MSG(_L("[DEBUG INFO]: iTransaction.Request().URI().UriDes()"),iTransaction.Request().URI().UriDes());

	// Submit the transaction. After this the framework will give transaction
	// events via MHFRunL and MHFRunError.
	iTransaction.SubmitL();

	iRunning = ETrue;
	}

// ----------------------------------------------------------------------------
// Cancels currently running transaction and frees resources related to it.
// ----------------------------------------------------------------------------
void CHTTPEngine::CancelTransaction()
	{
	if (!iRunning)
		return;

	// Close() also cancels transaction (Cancel() can also be used but
	// resources allocated by transaction must be still freed with Close())
	iTransaction.Close();

	// Not running anymore
	iRunning = EFalse;
	}

// ----------------------------------------------------------------------------
// Inherited from MHTTPTransactionCallback
// Called by framework to pass transaction events.
// ----------------------------------------------------------------------------
void CHTTPEngine::MHFRunL(RHTTPTransaction aTransaction,
		const THTTPEvent& aEvent)
	{
	switch (aEvent.iStatus)
		{
		case THTTPEvent::EGotResponseHeaders:
			{
			// HTTP response headers have been received. Use
			// aTransaction.Response() to get the response. However, it's not
			// necessary to do anything with the response when this event occurs.

			RespHeader(aTransaction);
			}
			break;

		case THTTPEvent::EGotResponseBodyData:
			{
			// Part (or all) of response's body data received. Use
			// aTransaction.Response().Body()->GetNextDataPart() to get the actual
			// body data.

			RespBodyData(aTransaction);
			}
			break;

		case THTTPEvent::EResponseComplete:
			{
			DBG_PRINT_MSG(_L("[DEBUG INFO]:"),_L("THTTPEvent::EResponseComplete"));
			}
			break;

		case THTTPEvent::ESucceeded:
			{
			// Transaction can be closed now. It's not needed anymore.
			aTransaction.Close();
			iRunning = EFalse;

			iObserver.OnHTTPEvent(KSucceeded);
			}
			break;

		case THTTPEvent::EFailed:
			{
			aTransaction.Close();
			iRunning = EFalse;
			}
			break;

		default:
			// There are more events in THTTPEvent, but they are not usually
			// needed. However, event status smaller than zero should be handled
			// correctly since it's error.
			{
			if (aEvent.iStatus < 0)
				{
				aTransaction.Close();
				iRunning = EFalse;
				}
			else
				{
				// Other events are not errors (e.g. permanent and temporary
				// redirections)
				}
			}
			break;
		}
	}

void CHTTPEngine::RespHeader(RHTTPTransaction& aTransaction)
	{
	RHTTPResponse resp = aTransaction.Response();
	TInt status = resp.StatusCode();
	// Get status text (e.g. "OK")
	TBuf<KStatustextBufferSize> statusText;
	statusText.Copy(resp.StatusText().DesC());

	TBuf<KStatustextBufferSize> headerStr;
	
	headerStr.Copy(_L("Status: "));
	headerStr.Append(statusText);
	headerStr.Append(_L(" "));
	headerStr.AppendNum(status);

	iObserver.OnHTTPEvent(headerStr);
	}

void CHTTPEngine::RespBodyData(RHTTPTransaction& aTransaction)
	{
	// Get the body data supplier
	MHTTPDataSupplier* dataSupplier = aTransaction.Response().Body();
	TPtrC8 ptr;
	
	dataSupplier->GetNextDataPart(ptr);

	TInt pos = 0;
	iFile.Seek(ESeekCurrent, pos);
	iFile.Write(ptr); //save the file being downloaded

	HBufC* buf = HBufC::NewLC(ptr.Length());
	
	buf->Des().Copy(ptr);

	if (!iResponseBuffer)
		{
		iResponseBuffer = buf->AllocL();
		}
	else
		{
		iResponseBuffer = iResponseBuffer->ReAllocL(iResponseBuffer->Length()
				+ buf->Length());
		iResponseBuffer->Des().Copy(*buf);
		}

	iFullSize += buf->Length();

	TBuf<KDefaultBufferSize> ReceivedDataBuf;

	ReceivedDataBuf.Append(_L("Bytes: "));
	ReceivedDataBuf.AppendNum(iFullSize);

	iObserver.OnHTTPEvent(ReceivedDataBuf);

	// Release buf
	CleanupStack::PopAndDestroy(buf);
	// Release the body data
	dataSupplier->ReleaseData();
	}

// ----------------------------------------------------------------------------
// Inherited from MHTTPTransactionCallback
// Called by framework when *leave* occurs in handling of transaction event.
// These errors must be handled, or otherwise HTTP-CORE 6 panic is thrown.
// ----------------------------------------------------------------------------
TInt CHTTPEngine::MHFRunError(TInt aError, RHTTPTransaction /*aTransaction*/,
		const THTTPEvent& /*aEvent*/)
	{
	// Just notify about the error and return KErrNone.
	iObserver.OnHTTPEvent(_L("RunError"));

	return KErrNone;
	}

// ----------------------------------------------------------------------------
// Inherited from MHTTPDataSupplier
// Called by framework when next part of the body is needed. In this
// this provides data for HTTP post.
// ----------------------------------------------------------------------------
TBool CHTTPEngine::GetNextDataPart(TPtrC8& aDataPart)
	{
	if (iPostData)
		{
		// Provide pointer to next chunk of data (return ETrue, if last chunk)
		// Usually only one chunk is needed, but sending big file could require
		// loading the file in small parts.
		aDataPart.Set(iPostData->Des());
		}
	return ETrue;
	}

// ----------------------------------------------------------------------------
// Inherited from MHTTPDataSupplier
// Called by framework. Allows us to release resources needed for previous
// chunk. (e.g. free buffers)
// ----------------------------------------------------------------------------
void CHTTPEngine::ReleaseData()
	{
	// It's safe to delete iPostData now.
	delete iPostData;
	iPostData = NULL;
	}

// ----------------------------------------------------------------------------
// Inherited from MHTTPDataSupplier
// Called by framework to reset the data supplier. Indicates to the data
// supplier that it should return to the first part of the data.
// In practise an error has occured while sending data, and framework needs to
// resend data.
// ----------------------------------------------------------------------------
TInt CHTTPEngine::Reset()
	{
	// Nothing needed since iPostData still exists and contains all the data.
	// (If a file is used and read in small parts we should seek to beginning
	// of file and provide the first chunk again in GetNextDataPart() )
	return KErrNone;
	}

// ----------------------------------------------------------------------------
// Inherited from MHTTPDataSupplier
// Called by framework. We should return the expected size of data to be sent.
// If it's not know we can return KErrNotFound (it's allowed and does not cause
// problems, since HTTP protocol allows multipart bodys without exact content
// length in header).
// ----------------------------------------------------------------------------
TInt CHTTPEngine::OverallDataSize()
	{
	if (iPostData)
		return iPostData->Length();
	else
		return KErrNotFound;
	}

// ----------------------------------------------------------------------------
// Inherited from MHTTPAuthenticationCallback
// Called by framework when we requested authenticated page and framework
// needs to know username and password.
// ----------------------------------------------------------------------------
TBool CHTTPEngine::GetCredentialsL(const TUriC8& aURI, RString aRealm,
		RStringF aAuthenticationType, RString& aUsername, RString& aPassword)
	{
	// aURI, aReal and aAuthenticationType are informational only. We only need
	// to set aUsername and aPassword and return ETrue, if aUsername and
	// aPassword are provided by user.

	// Buffer for string parameters that may change order
	CDesCArrayFlat* strings = new CDesCArrayFlat(2);
	
	CleanupStack::PushL(strings);

	// Initialize parameter buffer

	// First parameter
	HBufC* uri16 = HBufC::NewLC(aURI.UriDes().Length());
	
	uri16->Des().Copy(aURI.UriDes());
	strings->AppendL(*uri16);
	
	CleanupStack::PopAndDestroy(uri16);

	// Second parameter
	HBufC* authType16 = HBufC::NewLC(aAuthenticationType.DesC().Length());
	
	authType16->Des().Copy(aAuthenticationType.DesC());
	strings->AppendL(*authType16);
	
	CleanupStack::PopAndDestroy(authType16);

	// Query user name and password
	TBuf<KDefaultBufferSize> userName;
	TBuf<KDefaultBufferSize> password;
	
	CAknMultiLineDataQueryDialog* dlg = CAknMultiLineDataQueryDialog::NewL(
			userName, password);

	// Set aUsername and aPassword
	TBuf8<KDefaultBufferSize> temp;
	
	temp.Copy(userName);
	
	TRAPD(err, aUsername = aRealm.Pool().OpenStringL(temp));
	
	if (!err)
		{
		temp.Copy(password);
		TRAP(err, aPassword = aRealm.Pool().OpenStringL(temp));
		if (!err)
			return ETrue;
		}

	// Return ETrue if user has given credentials (username and password),
	// otherwise EFlase
	return EFalse;
	}
